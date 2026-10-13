/*
* Задача: Лабораторна робота 3, варіант 22
* Поліщук Вероніка
* Група 14
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    // Ініціалізація області визначення та параметрів
    double a = 0.1;
    double b = 1.0;
    const int n = 35;         // Кількість доданків за варіантом
    const int k = 10;        // Кількість розбиттів
    const double step = (b - a) / k;
    const double E = 0.0001; // Точність eps

    cout << "Обчислення функції\n";

    // Зовнішній цикл змінення x
    for (int i = 0; i <= k; i++) {
        double x = a + i * step;

        // Обчислення суми SN (для заданого n = 35)
        double SN = 0.0;
        double a_n = 1.0; // Перший доданок (n = 0)
        SN += a_n;

        for (int j = 1; j <= n; j++) {
            // Рекурентний перерахунок за математичною моделлю
            double ratio = -x * x * (2.0 * j * j + 1.0) / ((2.0 * (j - 1) * (j - 1) + 1.0) * (2 * j - 1) * (2 * j));
            a_n *= ratio;
            SN += a_n;
        }

        // Обчислення суми SE (для заданої точності eps)
        a_n = 1.0;
        double SE = 0.0;
        SE += a_n;
        int m = 1;

        while (fabs(a_n) >= E) {
            double ratio = -x * x * (2.0 * m * m + 1.0) / ((2.0 * (m - 1) * (m - 1) + 1.0) * (2 * m - 1) * (2 * m));
            a_n *= ratio;
            SE += a_n;
            m++;
        }

        // Точне значення функції Y
        double y = (1.0 - (x * x) / 2.0) * cos(x) - (x / 2.0) * sin(x);

        // Виведення результатів
        cout << fixed << setprecision(5)
             << "X=" << setw(7) << x
             << "   SN=" << setw(9) << SN
             << "   SE=" << setw(9) << SE
             << "   Y=" << setw(9) << y << "\n";
    }

    return 0;
}