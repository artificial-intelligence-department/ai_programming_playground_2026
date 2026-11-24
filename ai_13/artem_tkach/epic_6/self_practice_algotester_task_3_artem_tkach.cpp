// Algotester, задача "Potato Shuffle"
// https://algotester.com/en/ArchiveProblem/DisplayWithEditor/40448
// Ткач Артем, ШІ-13
//
// Умова: у ряд лежать N мішків з A[i] картоплин. За один хід можна поміняти місцями два
// сусідні мішки, якщо сума їхніх картоплин не більша за K. Потрібно знайти кількість різних
// послідовностей, які можна отримати, за модулем 10^9 + 7.
//
// Ідея: мішок "великий", якщо 2 * A > K. Два великих мішки ніколи не міняються місцями,
// тому великі мішки утворюють ланцюжок із незмінним порядком. Малі мішки (2 * A <= K)
// міняються між собою вільно, а з великим мішком Y - лише якщо A + Y <= K. Отже, кожен
// малий мішок може стояти лише між двома найближчими "блокувальними" великими мішками
// (Y > K - A). Ці проміжки вкладені один в інший, тому малі мішки вставляємо в порядку
// спадання A: для кожного кількість місць = (кількість великих мішків у проміжку) +
// (кількість уже вставлених малих мішків у проміжку) + 1. Добуток цих чисел ділимо на
// c! для кожної групи однакових мішків з однаковим проміжком.

#include <iostream>

const long long MOD = 1000000007;

long long power(long long base, long long exponent) {
    long long result = 1;
    base = base % MOD;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = result * base % MOD;
        }
        base = base * base % MOD;
        exponent = exponent / 2;
    }
    return result;
}

// Дерево відрізків із максимумом по великих мішках.
long long *tree;

// Остання позиція <= position, де значення більше за limit (або -1).
int findLeft(int node, int low, int high, int position, long long limit) {
    if (low > position || tree[node] <= limit) {
        return -1;
    }
    if (low == high) {
        return low;
    }
    int middle = (low + high) / 2;
    int result = findLeft(node * 2 + 1, middle + 1, high, position, limit);
    if (result == -1) {
        result = findLeft(node * 2, low, middle, position, limit);
    }
    return result;
}

// Перша позиція >= position, де значення більше за limit (або -1).
int findRight(int node, int low, int high, int position, long long limit) {
    if (high < position || tree[node] <= limit) {
        return -1;
    }
    if (low == high) {
        return low;
    }
    int middle = (low + high) / 2;
    int result = findRight(node * 2, low, middle, position, limit);
    if (result == -1) {
        result = findRight(node * 2 + 1, middle + 1, high, position, limit);
    }
    return result;
}

void build(int node, int low, int high, const long long *heavy) {
    if (low == high) {
        tree[node] = heavy[low];
        return;
    }
    int middle = (low + high) / 2;
    build(node * 2, low, middle, heavy);
    build(node * 2 + 1, middle + 1, high, heavy);
    tree[node] = tree[node * 2];
    if (tree[node * 2 + 1] > tree[node]) {
        tree[node] = tree[node * 2 + 1];
    }
}

// Дерево Фенвіка: скільки малих мішків уже вставлено в кожен проміжок.
int fenwickSize;
int *fenwick;

void fenwickAdd(int position) {
    for (int i = position + 1; i <= fenwickSize; i += i & (-i)) {
        fenwick[i]++;
    }
}

int fenwickPrefix(int position) {
    int sum = 0;
    for (int i = position + 1; i > 0; i -= i & (-i)) {
        sum += fenwick[i];
    }
    return sum;
}

struct Small {
    long long value;
    int gap;    // скільки великих мішків стоїть лівіше
    int left;   // номер великого мішка, що блокує зліва (0, якщо немає)
    int right;  // номер великого мішка, що блокує справа (heavyCount + 1, якщо немає)
};

bool isBefore(const Small &first, const Small &second) {
    if (first.value != second.value) {
        return first.value > second.value;
    }
    if (first.left != second.left) {
        return first.left < second.left;
    }
    return first.gap < second.gap;
}

// Дописує items[from..to) у кінець merged.
void copyTail(Small *merged, int &k, const Small *items, int &from, int to) {
    while (from < to) {
        merged[k] = items[from];
        from++;
        k++;
    }
}

// Зливає відсортовані половини items[0..middle) та items[middle..count).
void mergeParts(Small *items, int middle, int count) {
    Small *merged = new Small[count];
    int a = 0;
    int b = middle;
    int k = 0;
    while (a < middle && b < count) {
        bool takeSecond = isBefore(items[b], items[a]);
        if (takeSecond) {
            merged[k] = items[b];
            b++;
        } else {
            merged[k] = items[a];
            a++;
        }
        k++;
    }
    copyTail(merged, k, items, a, middle);
    copyTail(merged, k, items, b, count);
    for (int i = 0; i < count; i++) {
        items[i] = merged[i];
    }
    delete[] merged;
}

// Сортування злиттям, щоб не використовувати STL.
void sortSmall(Small *items, int count) {
    if (count < 2) {
        return;
    }
    int middle = count / 2;
    sortSmall(items, middle);
    sortSmall(items + middle, count - middle);
    mergeParts(items, middle, count);
}

// true, якщо елемент index - останній у групі однакових мішків з однаковим проміжком.
bool isGroupEnd(const Small *items, int index, int count) {
    if (index == count - 1) {
        return true;
    }
    if (items[index + 1].value != items[index].value) {
        return true;
    }
    if (items[index + 1].left != items[index].left) {
        return true;
    }
    if (items[index + 1].right != items[index].right) {
        return true;
    }
    return false;
}

// Розділяє мішки на великі (heavy[1..heavyCount]) і малі; для малого запам'ятовує проміжок.
void splitBags(const long long *values, int n, long long k, long long *heavy, int &heavyCount, Small *smalls, int &smallCount) {
    heavyCount = 0;
    smallCount = 0;
    for (int i = 0; i < n; i++) {
        if (2 * values[i] > k) {
            heavyCount++;
            heavy[heavyCount] = values[i];
        } else {
            smalls[smallCount].value = values[i];
            smalls[smallCount].gap = heavyCount;
            smallCount++;
        }
    }
}

// Для кожного малого мішка знаходить найближчі блокувальні великі мішки зліва та справа.
void findBlockers(Small *smalls, int smallCount, int heavyCount, long long k) {
    for (int i = 0; i < smallCount; i++) {
        long long limit = k - smalls[i].value;
        int left = findLeft(1, 0, heavyCount + 1, smalls[i].gap, limit);
        int right = findRight(1, 0, heavyCount + 1, smalls[i].gap + 1, limit);
        smalls[i].left = 0;
        if (left != -1) {
            smalls[i].left = left;
        }
        smalls[i].right = heavyCount + 1;
        if (right != -1) {
            smalls[i].right = right;
        }
    }
}

// Створює порожнє дерево Фенвіка для heavyCount + 1 проміжків.
void initFenwick(int heavyCount) {
    fenwickSize = heavyCount + 1;
    fenwick = new int[fenwickSize + 1];
    for (int i = 0; i <= fenwickSize; i++) {
        fenwick[i] = 0;
    }
}

// Факторіали за модулем від 0 до n.
long long *buildFactorials(int n) {
    long long *factorial = new long long[n + 1];
    factorial[0] = 1;
    for (int i = 1; i <= n; i++) {
        factorial[i] = factorial[i - 1] * i % MOD;
    }
    return factorial;
}

// Кількість місць, куди можна вставити малий мішок.
long long countPlaces(const Small &item) {
    int inserted = fenwickPrefix(item.right - 1);
    if (item.left > 0) {
        inserted = inserted - fenwickPrefix(item.left - 1);
    }
    return (item.right - item.left) + inserted;
}

// Кількість різних послідовностей за модулем.
long long countWays(const Small *smalls, int smallCount, int heavyCount, int n) {
    initFenwick(heavyCount);
    long long *factorial = buildFactorials(n);

    long long answer = 1;
    int groupSize = 0;
    for (int i = 0; i < smallCount; i++) {
        const Small &item = smalls[i];
        long long places = countPlaces(item);
        answer = answer * (places % MOD) % MOD;
        fenwickAdd(item.gap);

        // Група: однакові значення з однаковим проміжком.
        groupSize++;
        bool lastInGroup = isGroupEnd(smalls, i, smallCount);
        if (lastInGroup) {
            answer = answer * power(factorial[groupSize], MOD - 2) % MOD;
            groupSize = 0;
        }
    }

    delete[] fenwick;
    delete[] factorial;
    return answer;
}

// Читає n чисел.
long long *readValues(int n) {
    long long *values = new long long[n];
    for (int i = 0; i < n; i++) {
        std::cin >> values[i];
    }
    return values;
}

// Будує дерево відрізків по великих мішках (із нулями на краях).
void buildHeavyTree(long long *heavy, int heavyCount) {
    heavy[0] = 0;
    heavy[heavyCount + 1] = 0;
    tree = new long long[4 * (heavyCount + 2)];
    build(1, 0, heavyCount + 1, heavy);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    long long k;
    std::cin >> n >> k;

    long long *values = readValues(n);
    long long *heavy = new long long[n + 2];
    Small *smalls = new Small[n];
    int heavyCount = 0;
    int smallCount = 0;
    splitBags(values, n, k, heavy, heavyCount, smalls, smallCount);

    buildHeavyTree(heavy, heavyCount);
    findBlockers(smalls, smallCount, heavyCount, k);
    sortSmall(smalls, smallCount);

    long long answer = countWays(smalls, smallCount, heavyCount, n);
    std::cout << answer << "\n";

    delete[] values;
    delete[] heavy;
    delete[] smalls;
    delete[] tree;
    return 0;
}
