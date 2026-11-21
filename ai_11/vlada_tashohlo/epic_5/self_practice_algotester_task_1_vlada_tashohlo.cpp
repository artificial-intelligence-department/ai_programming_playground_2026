
/* 
Епік 5. self practice: Algotester, задача "Найкраще привітання"
Авторка: Влада Ташогло
Група: ші-11
*/

#include <iostream>
using namespace std;

const int MAXN = 100005;

int n, k;

char s[MAXN];   // Початковий рядок
char t[MAXN];   // Повністю відсортований рядок (ідеальна цільова анаграма)
char ans[MAXN]; // Найкращий знайдений рядок

// where[c] зберігає індекси входження літери ('a' + c) у вихідному рядку s
int where[26][MAXN];
int whereCount[26];

// used[i] = 1, якщо символ на позиції i вирізається для перестановки
int used[MAXN];

// Копіювання вмісту масиву a в масив b
void copyText(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0') {
        b[i] = a[i];
        i++;
    }
    b[i] = '\0';
}

// Сортування літер за лінійний час підрахунком (Counting Sort)
void sortLetters(char a[], int len) {
    int cnt[26] = {};

    for (int i = 0; i < len; ++i) {
        cnt[a[i] - 'a']++;
    }

    int pos = 0;
    for (int i = 0; i < 26; ++i) {
        while (cnt[i] > 0) {
            a[pos] = 'a' + i;
            pos++;
            cnt[i]--;
        }
    }

    a[len] = '\0';
}

// Перевірка лексикографічного порядку (повертає true, якщо a < b)
bool isSmaller(char a[], char b[]) {
    for (int i = 0; a[i] != '\0'; ++i) {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    return false;
}

// Підрахунок загальної кількості позначених позицій
int countUsed() {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (used[i]) {
            cnt++;
        }
    }
    return cnt;
}

// Перевірка: скільки позицій треба змінити, щоб зібрати перші x символів рядка t
int solve(int x) {
    for (int i = 0; i < n; ++i) {
        used[i] = 0;
    }

    int cnt[26] = {};

    // Рахуємо кількість кожної літери, необхідної для префікса довжини x
    for (int i = 0; i < x; ++i) {
        cnt[t[i] - 'a']++;
    }

    int extra = 0;

    // Перевіряємо перші x символів вихідного рядка s
    for (int i = 0; i < x; ++i) {
        if (s[i] != t[i]) {
            used[i] = 1; // Ця позиція обов'язково має бути замінена
        }

        int c = s[i] - 'a';

        if (cnt[c] > 0) {
            cnt[c]--; // Ця літера вже є на префіксі
        }
        else {
            extra++;  // Зайва літера, яку потрібно замінити буквою з суфікса
        }
    }

    // Жадібно добираємо потрібні букви з кінця рядка (суфікса)
    for (int c = 0; c < 26; ++c) {
        int j = whereCount[c] - 1;

        while (extra > 0 && j >= 0 && where[c][j] >= x) {
            used[where[c][j]] = 1;
            extra--;
            j--;
        }
    }

    return countUsed();
}

// Оновлення найкращої відповіді ans поточним варіантом перестановки
void updateAns(char values[], int len) {
    char sortedValues[MAXN];
    char cur[MAXN];

    // Сортуємо вирізані букви, щоб вставити їх у мінімальному порядку
    copyText(values, sortedValues);
    sortLetters(sortedValues, len);

    copyText(s, cur);

    int j = 0;
    // Заповнюємо відмічені позиції відсортованими літерами
    for (int i = 0; i < n; ++i) {
        if (used[i]) {
            cur[i] = sortedValues[j];
            j++;
        }
    }

    // Якщо новий рядок менший за поточну відповідь — оновлюємо її
    if (isSmaller(cur, ans)) {
        copyText(cur, ans);
    }
}

int main() {
    cin >> n >> k >> s;

    copyText(s, t);
    copyText(s, ans);

    // Отримуємо відсортовану цільову копію
    sortLetters(t, n);

    // Запам'ятовуємо позиції входження кожної букви у вихідному рядку
    for (int i = 0; i < n; ++i) {
        int c = s[i] - 'a';

        where[c][whereCount[c]] = i;
        whereCount[c]++;
    }

    // Бінарний пошук максимальної довжини ідеального префікса при обмеженні k
    int left = 0;
    int right = n + 1;

    while (left + 1 < right) {
        int mid = (left + right) / 2;

        int amount = solve(mid);

        if (amount > k) {
            right = mid;
        }
        else {
            left = mid;
        }
    }

    // Застосовуємо знайдену оптимальну довжину префікса
    int selected = solve(left);

    // Збираємо вирізані букви для вставки
    char values[MAXN];
    int len = 0;

    for (int i = 0; i < n; ++i) {
        if (used[i]) {
            values[len] = s[i];
            len++;
        }
    }

    values[len] = '\0';

    updateAns(values, len);

    // Якщо ліміт k дозволяє змінити ще одну позицію — тестуємо можливих кандидатів
    if (selected < k) {
        sortLetters(values, len);

        int pos = 0;
        int p1 = -1;
        int p2 = -1;

        for (int i = 0; i < n; ++i) {
            if (used[i]) {
                pos++;
                continue;
            }

            // Кандидат 1: позиція, де поточна літера більша за ту, яку можна вставити
            if (pos < len && s[i] > values[pos] && p1 == -1) {
                p1 = i;
            }

            // Кандидат 2: вигідна літера на суфіксі
            if (pos > 0 && s[i] < values[pos - 1] &&
                (p2 == -1 || s[i] <= s[p2])) {
                p2 = i;
            }
        }

        int candidates[2] = {p1, p2};

        // Перевіряємо заміну для кожного кандидата
        for (int j = 0; j < 2; ++j) {
            int p = candidates[j];

            if (p != -1) {
                used[p] = 1;

                char newValues[MAXN];

                copyText(values, newValues);
                newValues[len] = s[p];
                newValues[len + 1] = '\0';

                updateAns(newValues, len + 1);

                used[p] = 0; // Скасовуємо вибір для наступного кандидата
            }
        }
    }

    // Виведення результату
    cout << ans << '\n';

    return 0;
}
