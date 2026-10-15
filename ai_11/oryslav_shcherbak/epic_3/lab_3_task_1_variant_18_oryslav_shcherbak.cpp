#include <iostream>
#include <cmath>
using namespace std;

/*
 * Задача: Лабораторна робота 3, завдання 1 (варіант 18)
 * Щербак Орислав
 * Група ШІ-11
 */

int main() {
    const double eps = 0.0001; // точність обчислень
    const double pi = 3.14159265358979323846; // число пі
    const double h = (0.8 - 0.1) / 10; // крок між значеннями x
    // перебираємо 11 значень x від 0.1 до 0.8
    for (int i = 0; i <= 10; i++) {
        double x = 0.1 + i * h; // поточне значення x
        double sum1 = 0; // сума перших 50 членів ряду
        double a; // поточний член ряду
        // рахуємо суму за допомогою циклу for
        for (int n = 1; n <= 50; n++) {
            a = cos(2.0 * n * x) / (4.0 * n * n - 1.0);
            sum1 += a;
        }
        int n = 1;
        double sum2 = 0; // сума членів ряду з заданою точністю
        // рахуємо суму за допомогою циклу do while
        do {
            a = cos(2.0 * n * x) / (4.0 * n * n - 1.0);
            sum2 += a;
            n++;
        } while (fabs(a) >= eps); // продовжуємо, поки член ряду не стане меншим за точність
        double exact = 0.5 - (pi / 4.0) * fabs(sin(x)); // точне значення функції
        // виводимо результати
        cout << "X = " << x << endl;
        cout << "SN = " << sum1 << endl;
        cout << "SE = " << sum2 << endl;
        cout << "Y = " << exact << endl;
        cout << endl;
    }
    return 0;
}