/*Епік 3. Лабораторна робота 3. Варіант 4
Автор: Матішак Михайло
Група: ШІ-11*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    const double A = 0.1, B = 0.8, EPS = 0.0001;
    const int K = 10, N = 10;
    const double H = (B - A) / K;

    cout << fixed << setprecision(6);

    for (int i = 0; i <= K; i++) {
        double x = A + i * H;
        double x2 = x * x;

        cout << "Крок " << i << endl;

        // Сума для заданого n
        double a = x2 / 2.0;
        double SN = 0.0;
        for (int k = 0; k < N; k++) {
            SN += a;
            cout << "a" << k << " = " << a << endl;
            a = -a * x2 * (2.0 * k + 1) * (2.0 * k + 2)
                / ((2.0 * k + 3) * (2.0 * k + 4));
        }
        cout << "Ряд дорівнює " << SN << endl;

        // Сума для заданої точності
        a = x2 / 2.0;
        double SE = 0.0;
        int k = 0;
        while (fabs(a) >= EPS) {
            SE += a;
            cout << "a" << k << " = " << a << endl;
            a = -a * x2 * (2.0 * k + 1) * (2.0 * k + 2)
                / ((2.0 * k + 3) * (2.0 * k + 4));
            k++;
        }
        cout << "Ряд дорівнює " << SE << endl;

        double Y = x * atan(x) - 0.5 * log(1.0 + x2);

        cout << "X=" << x << " SN=" << SN << " SE=" << SE << " Y=" << Y << endl << endl;
    }

    return 0;
}