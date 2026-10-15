#include <iostream>
#include <cmath>
using namespace std;

/*
 * Задача: Лабораторна робота 3, завдання 1 (варіант 18)
 * Щербак Орислав
 * Група ШІ-11
 */

int main() {
    const double eps = 0.0001;
    const double pi = 3.14159265358979323846;
    const double h = (0.8 - 0.1) / 10;
    for (int i = 0; i <= 10; i++) {
        double x = 0.1 + i * h;
        double sum1 = 0;
        double a;
        for (int n = 1; n <= 50; n++) {
            a = cos(2.0 * n * x) / (4.0 * n * n - 1.0);
            sum1 += a;
        }
        int n = 1;
        double sum2 = 0;
        do {
            a = cos(2.0 * n * x) / (4.0 * n * n - 1.0);
            sum2 += a;
            n++;
        } while (fabs(a) >= eps);
        double exact = 0.5 - (pi / 4.0) * fabs(sin(x));
        cout << "X = " << x << endl;
        cout << "SN = " << sum1 << endl;
        cout << "SE = " << sum2 << endl;
        cout << "Y = " << exact << endl;
        cout << endl;
    }
    return 0;
}