/*
Lab 3 task 1, Артем Момоток, ШІ-13, Варіант 22
*/

// y(x) = (1 - x^2/2) * cos(x) - (x/2) * sin(x)
// S(x) = 1 - 3/2 * x^2 + ... + (-1)^n * (2n^2 + 1) / (2n)! * x^(2n)
// 0.1 <= x <= 1

// SN - сума ряду для заданого n (арифметичний цикл)
// SE - сума ряду для заданої точності EPS (ітераційний цикл)
// Y  - точне значення функції

#include <iostream>
#include <iomanip>
#include <cmath>

const double X_START = 0.1;     // початок проміжку
const double X_END = 1.0;       // кінець проміжку
const double X_STEP = 0.1;      // крок за x
const int N = 35;               // задане n для суми SN
const double EPS = 0.000001;    // задана точність для суми SE

// Точне значення функції
double functionY(double x) {
    return (1 - x * x / 2) * std::cos(x) - (x / 2) * std::sin(x);
}

int main() {
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Обчислення функції" << std::endl << std::endl;

    // Зовнішній цикл: зміна параметра x.
    for (double x = X_START; x <= X_END + X_STEP / 2; x += X_STEP) {

        // Внутрішній арифметичний цикл: сума N + 1 доданків
        double a = 1;
        double term = 1;
        double sn = term;
        for (int k = 1; k <= N; k++) {
            a = a * x * x / ((2 * k - 1) * (2 * k));
            term = (2 * k * k + 1) * a;
            if (k % 2 == 1) term = -term;
            sn += term;
        }

        // Внутрішній ітераційний цикл: додаємо доданки, поки |доданок| > EPS
        a = 1;
        term = 1;
        double se = term;
        int k = 0;
        while (std::abs(term) > EPS) {
            k++;
            a = a * x * x / ((2 * k - 1) * (2 * k));
            term = (2 * k * k + 1) * a;
            if (k % 2 == 1) term = -term;
            se += term;
        }

        // Виведення таблиці
        std::cout << "X=" << std::setprecision(2) << x << std::setprecision(6)
                  << "  SN=" << sn
                  << "  SE=" << se
                  << "  Y=" << functionY(x) << std::endl;
    }
    return 0;
}