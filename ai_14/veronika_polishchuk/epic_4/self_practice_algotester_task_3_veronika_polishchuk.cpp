/*
* Задача: Цікаве листування
* Поліщук Вероніка
* Група 14
*/
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    // Шукаємо сторону квадрата k
    int k = sqrt(n);

    // Створюємо звичайну матрицю k x k
    char grid[1000][1000]; 

    // Заповнюємо матрицю 
    int idx = 0;
    for (int r = 0; r < k; r++) {
        for (int c = 0; c < k; c++) {
            grid[r][c] = s[idx++];
        }
    }

    // Обходимо матрицю по діагоналях і відразу виводимо символи
    for (int d = 0; d < 2 * k - 1; d++) {
        for (int r = 0; r < k; r++) {
            int c = d - r;
            // Перевіряємо, чи стовпчик c знаходиться в межах квадрата
            if (c >= 0 && c < k) {
                cout << grid[r][c];
            }
        }
    }
    return 0;
}