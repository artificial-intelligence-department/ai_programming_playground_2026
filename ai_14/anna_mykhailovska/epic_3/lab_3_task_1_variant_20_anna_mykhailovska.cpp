/*
    Lab 3
    Михайловська Анна
    ШІ-14
*/
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    const double a = 0.1;
    const double b = 1.0;
    const int k = 10;
    const int n = 30;
    const double eps = 0.0001;
    const double h = (b - a) / k;

    cout << fixed << setprecision(8);

    for (int i = 0; i <= k; ++i) {
        const double x = a + i * h;
        // Сума ряду для заданого n.
        double SN = 1.0;
        double c = 1.0;

        for (int j = 1; j <= n; ++j) {
            c *= x / (2.0 * j);
            SN += (j * j + 1.0) * c;
        }
        // Сума ряду для заданої точності eps.
        double SE = 1.0;
        c = 1.0;
        double term;
        int j = 1;

        do {
            c *= x / (2.0 * j);
            term = (j * j + 1.0) * c;
            SE += term;
            ++j;
        } while (abs(term) >= eps);
        // Значення функції для порівняння.
        const double Y = (x * x / 4.0 + x / 2.0 + 1.0) * exp(x / 2.0);

        cout << "X=" << x << "  SN=" << SN << "  SE=" << SE << "  Y=" << Y << '\n';
    }
    return 0;
}