#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 100;   // максимальний розмір

// Заповнення матриці випадковими числами
void fillMatrix(int a[][N], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = rand() % 9 + 1;    // числа 1..9, щоб добуток не став нульовим
}

// Друк матриці
void printMatrix(int a[][N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << a[i][j] << "\t";
        cout << endl;
    }
}

// Чи перший елемент стовпця j більший за елементи цього стовпця,
// що лежать на головній і бічній діагоналях
bool isColumnSuitable(int a[][N], int n, int j) {
    for (int i = 1; i < n; i++) {                 // рядок 0 пропускаємо
        bool onMain = (i == j);
        bool onSide = (i == n - 1 - j);
        if ((onMain || onSide) && a[0][j] <= a[i][j])
            return false;
    }
    return true;
}

// Добуток елементів стовпця j
long long columnProduct(int a[][N], int n, int j) {
    long long p = 1;
    for (int i = 0; i < n; i++)
        p *= a[i][j];
    return p;
}

// Обробка матриці: виводить добутки підходящих стовпців,
// повертає загальний добуток (або 0, якщо підходящих немає)
long long processMatrix(int a[][N], int n, int &count) {
    long long total = 1;
    count = 0;
    for (int j = 0; j < n; j++) {
        if (isColumnSuitable(a, n, j)) {
            long long p = columnProduct(a, n, j);
            cout << "Стовпець " << j + 1 << ": добуток = " << p << endl;
            total *= p;
            count++;
        }
    }
    return count > 0 ? total : 0;
}

int main() {
    int a[N][N];
    int n;

    cout << "Введіть розмір матриці (1.." << N << "): ";
    cin >> n;
    if (n < 1 || n > N) {
        cout << "Некоректний розмір!" << endl;
        return 1;
    }

    srand((unsigned)time(0));
    fillMatrix(a, n);

    cout << "Матриця:" << endl;
    printMatrix(a, n);

    int count;
    long long total = processMatrix(a, n, count);

    if (count == 0)
        cout << "Підходящих стовпців немає." << endl;
    else
        cout << "Підходящих стовпців: " << count
             << ", загальний добуток = " << total << endl;

    return 0;
}