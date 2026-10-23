/*
Лабораторна робота №3, Завдання 1, Варіант 1
Станіслав Коваль
ШІ-12
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    const double a = 0.1, b = 1.0, eps = 1e-4;
    const int k = 10, n = 10;
    const double h = (b - a) / k, L = log(3.0);

    cout << "Обчислення функції\n\n" << fixed << setprecision(6);

    for (int i = 0; i <= k; ++i) {
        const double x = a + i * h, z = x * L;
        double SN = 0.0, SE = 0.0, an = 1.0;

        for (int j = 0; j <= n; ++j) {
            SN += an;
            an *= z / (j + 1);
        }

        an = 1.0;
        int j = 0;
        while (fabs(an) >= eps) {
            SE += an;
            ++j;
            an *= z / j;
        }

        cout << "X=" << x << " SN=" << SN << " SE=" << SE << " Y=" << pow(3.0, x) << '\n';
    }

    return 0;
}