/*
Лабораторна робота №3, Завдання №1, Варіант №13.
Цебуля Вадим
ШІ-12
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    const double a = 0.2;
    const double b = 1.0;
    const int K = 10;         // Кількість точок розбиття інтервалу
    const int n = 10;          // Кількість членів ряду для першого способу
    const double eps = 0.0001; // Задана точність для другого способу

    double step = (b - a) / K;

    cout << fixed << setprecision(6);

    for (int i = 0; i <= K; i++) {
        double x = a + i * step;
        double t = (x - 1) / (x + 1);

        // Обчислення суми ряду для фіксованої кількості членів (n)
        double term1 = t;
        double Sum1  = term1;

        for (int j = 0; j < n; j++) {
            term1 = term1 * t * t * (2.0 * j + 1) / (2.0 * j + 3);
            Sum1 += term1;
        }

        // Обчислення суми ряду з точністю eps (доки член ряду більший за eps)
        double term2 = t;
        double Sum2  = term2;
        int j = 0;

        do {
            term2 = term2 * t * t * (2.0 * j + 1) / (2.0 * j + 3);
            Sum2 += term2;
            j++;
        } while (fabs(term2) >= eps);

        // Виведення результатів: x, суми за методами та еталонне значення
        cout << setw(8)  << x
             << setw(14) << Sum1
             << setw(14) << Sum2
             << setw(14) << 0.5 * log(x) << endl;
    }
    return 0;
}

