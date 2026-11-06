// Лабораторна робота №5, варіант 3
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

// розмір константа, бо матриця йде у функцію
const int MAX_N = 10;

void fillRandom(int m[][MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = rand() % 21 - 10;
        }
    }
}

bool readMatrix(int m[][MAX_N], int n) {
    cout << "Введіть елементи матриці " << n << "x" << n << " по рядках:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (!(cin >> m[i][j])) {
                return false;
            }
        }
    }
    return true;
}

void printMatrix(const int m[][MAX_N], int n, const char *title) {
    cout << title << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << m[i][j];
        }
        cout << endl;
    }
}

// транспонування в окрему матрицю
void transpose(const int src[][MAX_N], int dst[][MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dst[j][i] = src[i][j];
        }
    }
}

// сума матриць
void sumMatrices(const int a[][MAX_N], const int b[][MAX_N],
                 int res[][MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = a[i][j] + b[i][j];
        }
    }
}

int main() {
    srand(time(0));

    int n;
    int mode;
    int a[MAX_N][MAX_N];
    int t[MAX_N][MAX_N];
    int c[MAX_N][MAX_N];

    cout << "Введіть розмір квадратної матриці (від 1 до " << MAX_N << "): ";
    cin >> n;
    if (n < 1 || n > MAX_N) {
        cout << "Некоректний розмір матриці." << endl;
        return 1;
    }

    cout << "Як заповнити матрицю? 1 - вручну, 2 - випадково: ";
    cin >> mode;

    if (mode == 1) {
        if (!readMatrix(a, n)) {
            cout << "Некоректне значення елемента." << endl;
            return 1;
        }
    } else if (mode == 2) {
        fillRandom(a, n);
    } else {
        cout << "Некоректний вибір." << endl;
        return 1;
    }

    transpose(a, t, n);
    sumMatrices(a, t, c, n);

    printMatrix(a, n, "Вихідна матриця A:");
    printMatrix(t, n, "Транспонована матриця A^T:");
    printMatrix(c, n, "Сума A + A^T:");

    return 0;
}