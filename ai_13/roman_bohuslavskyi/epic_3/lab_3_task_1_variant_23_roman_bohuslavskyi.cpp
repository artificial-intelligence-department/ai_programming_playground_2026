/*
Задача:  Лабораторна робота №3, Варіант №23
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    // Початкові значення
    double startX = 0.1;
    double endX = 1.0;
    int intervals = 10;
    int terms = 15;
    double eps = 0.0001;

    // Обчислення кроку
    double step = (endX - startX) / intervals;

    // Вивід заголовка
    cout << endl;
    cout << "                 Обчислення функції" << endl << endl;
    cout << fixed;

    // Перебір значень аргументу
    for (int i = 0; i <= intervals; i++) {
        double x = startX + i * step;
        // Обчислення значення функції
        double y = 2 * (cos(x) * cos(x) - 1);

        // Обчислення суми для заданої кількості доданків
        double sumN = 0;
        double current = -2 * x * x;

        for (int j = 1; j <= terms; j++) {
            sumN += current;
            current = current * (-4 * x * x) / ((2 * j + 1) * (2 * j + 2));
        }

        // Обчислення суми із заданою точністю
        double sumE = 0;
        current = -2 * x * x;
        int j = 1;

        while (fabs(current) >= eps) {
            sumE += current;
            current = current * (-4 * x * x) / ((2 * j + 1) * (2 * j + 2));
            j++;
        }

        // Вивід результатів
        cout << "X=" << setprecision(2) << x
             << "  SN=" << setprecision(6) << setw(10) << sumN
             << "  SE=" << setw(10) << sumE
             << "  Y=" << setw(10) << y << endl;
    }

    return 0;
}
