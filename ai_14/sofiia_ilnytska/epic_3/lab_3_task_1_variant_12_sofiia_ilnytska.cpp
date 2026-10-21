/*
    Задача: Лабораторна робота №3. Варіант №12
    Автор: Ільницька Софія
    Група: ШІ-14
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    // Задаємо початок і кінець проміжку для обчислення функції
    double a = 0.1;
    double b = 0.8;
    int k = 10; // Кількість частин, на які ділимо проміжок
    double h = (b - a) / k; // Обчислюємо крок зміни аргументу x
    int n = 35; // Кількість членів ряду для обчислення суми SN
    double accuracy = 0.0001; // Задаємо точність обчислення суми SE
    double pi = 3.14;

    cout << fixed << setprecision(6);
    cout << "Обчислення функції:" << endl;

    // Перебираємо значення x від a до b із кроком h
    for (double x = a; x <= b + h/2; x += h) {
        // Обчислюємо значення функції Y за заданою формулою
        double Y = -0.5 * log(1 - 2 * x * cos(pi / 3) + pow(x, 2));
        double SN = 0.0;
        // Обчислюємо суму перших n - 1 членів ряду
        for (int i = 1; i < n; i++) {
            double a = (pow(x, i) * cos(i * pi / 3)) / i; // Обчислюємо поточний член ряду
            SN += a;
        }
        double SE = 0.0;
        double a_current;
        int j = 1;
        // Додаємо члени ряду, поки модуль останнього члена не стане меншим за задану точність
        do {
            a_current = (pow(x, j) * cos(j * pi / 3.0)) / j; // Обчислюємо поточний член ряду
            SE += a_current;
            j++;
        } while (abs(a_current) >= accuracy);

        // Виводимо аргумент x, обидві суми ряду та значення функції Y
        cout << "X=" << x << "  SN=" << SN << "  SE=" << SE << "  Y=" << Y << endl;
    }
    return 0;
}