/*
 * Лабораторна робота 5, варіант 18
 * Ткач Артем
 * ШІ-13
 *
 * Завдання: задано двовимірний масив N x N. Послідовно розглядаються
 * квадратні підмасиви, правий верхній елемент яких лежить на бічній
 * діагоналі. У кожному такому підмасиві є максимальний елемент. Шляхом
 * перестановок рядків і стовпців (повністю) його треба перемістити в правий
 * верхній кут підмасиву. Перевірити, чи вийшла на бічній діагоналі
 * спадаюча послідовність елементів.
*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MAX_N = 10;

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

// Читає розмір матриці та її елементи з перевіркою введених даних
bool readMatrix(int a[MAX_N][MAX_N], int &n) {
    cout << "Розмір матриці N (1-" << MAX_N << "): ";
    bool ok = readInt(n);
    if (!ok || n < 1 || n > MAX_N) {
        cout << "Помилка: N має бути цілим числом від 1 до " << MAX_N << "." << endl;
        return false;
    }
    cout << "Елементи матриці (" << n << " x " << n << "):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ok = readInt(a[i][j]);
            if (!ok) {
                cout << "Помилка: елемент має бути цілим числом." << endl;
                return false;
            }
        }
    }
    return true;
}

void printMatrix(int a[MAX_N][MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << a[i][j];
        }
        cout << endl;
    }
}

// Максимум підмасиву: рядки step..n-1, стовпці 0..n-1-step
void findMax(int a[MAX_N][MAX_N], int n, int step, int &maxRow, int &maxCol) {
    maxRow = step;
    maxCol = 0;
    for (int i = step; i < n; i++) {
        for (int j = 0; j <= n - 1 - step; j++) {
            if (a[i][j] > a[maxRow][maxCol]) {
                maxRow = i;
                maxCol = j;
            }
        }
    }
}

void swapRows(int a[MAX_N][MAX_N], int n, int r1, int r2) {
    for (int j = 0; j < n; j++) {
        int temp = a[r1][j];
        a[r1][j] = a[r2][j];
        a[r2][j] = temp;
    }
}

void swapColumns(int a[MAX_N][MAX_N], int n, int c1, int c2) {
    for (int i = 0; i < n; i++) {
        int temp = a[i][c1];
        a[i][c1] = a[i][c2];
        a[i][c2] = temp;
    }
}

// Чи спадає послідовність на бічній діагоналі (згори донизу)
bool isDiagonalDecreasing(int a[MAX_N][MAX_N], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i][n - 1 - i] <= a[i + 1][n - 2 - i]) {
            return false;
        }
    }
    return true;
}

// Для кожного підмасиву на бічній діагоналі переносить його максимум у правий верхній кут
void moveMaximums(int a[MAX_N][MAX_N], int n) {
    for (int step = 0; step < n; step++) {
        int maxRow, maxCol;
        findMax(a, n, step, maxRow, maxCol);
        swapRows(a, n, step, maxRow);
        swapColumns(a, n, maxCol, n - 1 - step);
    }
}

void printDiagonal(int a[MAX_N][MAX_N], int n) {
    cout << "Бічна діагональ:";
    for (int i = 0; i < n; i++) {
        cout << " " << a[i][n - 1 - i];
    }
    cout << endl;
}

int main() {
    int a[MAX_N][MAX_N];
    int n;

    bool ok = readMatrix(a, n);
    if (!ok) {
        return 0;
    }

    cout << "Початкова матриця:" << endl;
    printMatrix(a, n);

    moveMaximums(a, n);

    cout << "Матриця після перестановок:" << endl;
    printMatrix(a, n);
    printDiagonal(a, n);

    bool decreasing = isDiagonalDecreasing(a, n);
    if (decreasing) {
        cout << "Послідовність на бічній діагоналі спадаюча." << endl;
    } else {
        cout << "Послідовність на бічній діагоналі не є спадаючою." << endl;
    }
    return 0;
}
