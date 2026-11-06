/*
Назва:lab 5 task 1
Автор: Катерина Лисенко
Група: ШІ-12
*/
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
 
const int MAX = 20;            // максимальне N
const int MAXLEN = MAX * MAX;  // максимальна довжина рядка
 
// Точний цілий корінь: N, якщо len = N*N, інакше 0
int exactRoot(int len) {
    for (int n = 1; n * n <= len; n++) {
        if (n * n == len) return n;
    }
    return 0;
}
 
// Перевіряє, що рядок складається лише з цифр
bool onlyDigits(const char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}
 
// Вводить рядок цифр довжиною N*N (1 <= N <= MAX); повертає N
int readDigits(char s[]) {
    while (true) {
        cout << "Введіть рядок з N*N цифр (довжина 1, 4, 9, 16, ...): ";
        cin.getline(s, MAXLEN + 2);
        if (cin.fail() && !cin.eof()) { // рядок задовгий для буфера
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Помилка! Рядок задовгий (не більше " << MAXLEN << " цифр)." << endl;
            continue;
        }
        int len = (int)strlen(s);
        if (len > 0 && s[len - 1] == '\r') { // на випадок Windows-кінців рядка
            s[len - 1] = '\0';
            len--;
        }
        if (len == 0 && cin.eof()) {
            cout << "\nВведення завершено." << endl;
            exit(0);
        }
        if (len == 0 || !onlyDigits(s)) {
            cout << "Помилка! Рядок має складатися лише з цифр (без пробілів та інших символів)." << endl;
            continue;
        }
        if (len > MAXLEN) {
            cout << "Помилка! Рядок задовгий (не більше " << MAXLEN << " цифр)." << endl;
            continue;
        }
        int n = exactRoot(len);
        if (n == 0) {
            cout << "Помилка! Довжина рядка (" << len << ") не є повним квадратом N*N." << endl;
            continue;
        }
        return n;
    }
}
 
// Розбиває рядок на N підрядків довжиною N і записує їх у рядки масиву
void fillArray(const char s[], int n, int a[][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = s[i * n + j] - '0';
        }
    }
}
 
// Обмін двох рядків масиву
void swapRows(int a[][MAX], int n, int r1, int r2) {
    for (int j = 0; j < n; j++) {
        int t = a[r1][j];
        a[r1][j] = a[r2][j];
        a[r2][j] = t;
    }
}
 
// Впорядковує рядки за зростанням першого стовпця (вибором мінімуму)
void sortRowsByFirstColumn(int a[][MAX], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minRow = i;
        for (int k = i + 1; k < n; k++) {
            if (a[k][0] < a[minRow][0]) minRow = k;
        }
        if (minRow != i) swapRows(a, n, i, minRow);
    }
}
 
// Чи йдуть елементи першого стовпця строго в порядку зростання
bool firstColumnIncreasing(int a[][MAX], int n) {
    for (int i = 0; i + 1 < n; i++) {
        if (a[i][0] >= a[i + 1][0]) return false;
    }
    return true;
}
 
// Виводить масив N x N
void printArray(int a[][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}
 
// Виводить першу цифру кожного підрядка
void printFirstDigits(int a[][MAX], int n) {
    cout << "Перші цифри підрядків:";
    for (int i = 0; i < n; i++) {
        cout << " " << a[i][0];
    }
    cout << endl;
}
 
// Знаходить першу цифру першого стовпця, що повторюється; повертає її, або -1
int findRepeatedDigit(int a[][MAX], int n) {
    for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
            if (a[i][0] == a[k][0]) return a[i][0];
        }
    }
    return -1;
}
 
int main() {
    char s[MAXLEN + 2];
    int a[MAX][MAX];
    char again;
 
    do {
        int n = readDigits(s);
 
        cout << "\nN = " << n << ". Підрядки довжиною " << n << " записані в масив " << n << " x " << n << ":" << endl;
        fillArray(s, n, a);
        printArray(a, n);
        printFirstDigits(a, n);
 
        sortRowsByFirstColumn(a, n);
 
        if (firstColumnIncreasing(a, n)) {
            cout << "\nВідповідь: ТАК, можна. Рядки, впорядковані за зростанням першого стовпця:" << endl;
            printArray(a, n);
        } else {
            int d = findRepeatedDigit(a, n);
            if (d != -1) {
                cout << "\nВідповідь: НІ, не можна: цифра " << d
                     << " є першою в кількох підрядках, тож строгого зростання в першому стовпці не отримати." << endl;
            } else {
                cout << "\nВідповідь: НІ, не можна." << endl;
            }
        }
 
        again = 'n';
        cout << "\nПовторити з іншим рядком? (y/n): ";
        cin >> again;
        cin.ignore(100000, '\n');
        cout << endl;
    } while (again == 'y' || again == 'Y');
 
    return 0;
}