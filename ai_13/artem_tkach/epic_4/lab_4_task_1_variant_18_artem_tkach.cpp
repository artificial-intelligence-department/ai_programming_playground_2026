/*
 * Лабораторна робота 4, варіант 18
 * Ткач Артем
 * ШІ-13
 *
 * Завдання: реалізувати з використанням масиву однонаправлене кільце
 * (перегляд можливий зліва направо, від останнього елемента можна перейти
 * до першого). Роздрукувати масив, починаючи з K-го елемента і до (K-1)-го,
 * додати в кільце перший і останній елементи, знищити з кільця парні
 * елементи, знову роздрукувати масив від K-го елемента до (K-1)-го.
*/

#include <iostream>
#include <string>
using namespace std;

const int MAX_N = 100;

// Зчитує ціле число (можливо від'ємне) як рядок, щоб відсікти зайві символи
bool readInt(int &value) {
    string token;
    cin >> token;
    int len = token.length();
    if (len == 0 || len > 9) {
        return false;
    }
    int start = 0;
    if (token[0] == '-') {
        start = 1;
    }
    if (start == len) {
        return false;
    }
    for (int i = start; i < len; i++) {
        if (token[i] < '0' || token[i] > '9') {
            return false;
        }
    }
    value = stoi(token);
    return true;
}

// Читає розмір кільця, його елементи та номер K з перевіркою введених даних
bool readRing(int a[], int &n, int &k) {
    cout << "Кількість елементів кільця (1-" << MAX_N - 2 << "): ";
    bool ok = readInt(n);
    if (!ok || n < 1 || n > MAX_N - 2) {
        cout << "Помилка: потрібне ціле число від 1 до " << MAX_N - 2 << "." << endl;
        return false;
    }
    cout << "Елементи кільця: ";
    for (int i = 0; i < n; i++) {
        ok = readInt(a[i]);
        if (!ok) {
            cout << "Помилка: елемент має бути цілим числом." << endl;
            return false;
        }
    }
    cout << "Номер K початкового елемента (1-" << n << "): ";
    ok = readInt(k);
    if (!ok || k < 1 || k > n) {
        cout << "Помилка: K має бути цілим числом від 1 до " << n << "." << endl;
        return false;
    }
    return true;
}

// Друк кільця від K-го елемента по колу (зліва направо) до (K-1)-го
void printRing(const int a[], int n, int k) {
    if (n == 0) {
        cout << "Кільце порожнє." << endl;
        return;
    }
    int start = (k - 1) % n;
    for (int t = 0; t < n; t++) {
        cout << a[(start + t) % n] << " ";
    }
    cout << endl;
}

// Додає нові елементи на початок і в кінець масиву
void addFirstAndLast(int a[], int &n, int first, int last) {
    for (int i = n; i > 0; i--) {
        a[i] = a[i - 1];
    }
    a[0] = first;
    a[n + 1] = last;
    n = n + 2;
}

// Знищує парні елементи, решту щільно зсуває вліво
void removeEven(int a[], int &n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 != 0) {
            a[count] = a[i];
            count++;
        }
    }
    n = count;
}

int main() {
    int a[MAX_N];
    int n, k, first, last;

    bool ok = readRing(a, n, k);
    if (!ok) {
        return 0;
    }

    cout << "Кільце від K-го елемента: ";
    printRing(a, n, k);

    cout << "Новий перший та новий останній елементи: ";
    bool okFirst = readInt(first);
    bool okLast = readInt(last);
    if (!okFirst || !okLast) {
        cout << "Помилка: потрібні два цілих числа." << endl;
        return 0;
    }
    addFirstAndLast(a, n, first, last);
    cout << "Після додавання першого й останнього: ";
    printRing(a, n, k);

    removeEven(a, n);
    cout << "Після знищення парних елементів: ";
    printRing(a, n, k);

    return 0;
}
