/*
    Lab 5
    Михайловська Анна
    ШІ-14
    Варіант 8
*/
#include <iostream>
using namespace std;

const int N = 100; //Максимальна кількість стовпців і рядків матриці

// Функція транспонування матриці a в матрицю b
void transponation(int a[][N], int b[][N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b[j][i] = a[i][j];
        }
    }
}

// Функція для визначення симетричності матриці
bool symmetric(int a[][N], int b[][N], int n){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(a[i][j] != b[i][j])
                return false;
        }
    }
    return true;
}

int main() {
    
    int n, a[N][N], b[N][N];

    cout << "Введіть кількість стовпців та рядків квадратної матриці: ";

    //Перевірка на коректність вводу кількості стовпців та рядків
    if (!(cin >> n) || n < 1 || n > N){
        cout << "Помилка: кількість стовпців та рядків має бути числом від 1 до 100";
        return 1;
    }
    cout << "Введіть елементи матриці:\n";

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            //Перевірка на коректність вводу елементів матриці
            if (!(cin >> a[i][j])) {
                cout << "Помилка: елементи матриці мають бути цілими числами.";
                return 1;
            }
        }
    }
    
    //Транспонування матриці
    transponation(a, b, n);

    cout << "Транспонована матриця:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << b[i][j] << " ";
        }
        cout << "\n";
    }

    //Перевірка чи матриця симетрична
    if (symmetric(a, b, n))
        cout << "Матриця симетрична";
    else
        cout << "Матриця не симетрична";

    return 0;
}
