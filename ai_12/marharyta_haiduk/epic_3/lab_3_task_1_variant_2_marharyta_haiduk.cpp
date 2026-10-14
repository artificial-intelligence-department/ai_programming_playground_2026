/*
    Задача: Лабораторна робота №3. Завдання №1. Варіант №2
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    const double PI = 3.1415926535;
    double a = PI / 5;      // початок проміжку
    double b = 9 * PI / 5;  // кінець проміжку
    int k = 10;               // кількість кроків
    int n = 40;               // задане n
    double eps = 0.0001;      // задана точність
    double h = (b - a) / k;   // крок зміни x
    cout << "Обчислення функції:" << endl << endl;
    for (int i = 0; i <= k; i++) {
        double x = a + i * h;

        // Сума для заданого n
        double SN = 0;
        for (int j = 1; j <= n; j++) {
            SN += cos(j * x) / j;
        }

        // Сума для заданої точності
        double SE = 0;
        int j = 1;
        double term = cos(x) / 1;
        while (fabs(term) >= eps) {
            SE += term;
            j++;
            term = cos(j * x) / j;
        }

        // Точне значення функції
        double Y = -log(fabs(2 * sin(x / 2)));

        cout << fixed << setprecision(6);
        cout << "X=" << x << "  SN=" << SN
             << "  SE=" << SE << "  Y=" << Y << endl;
    }

    return 0;
}