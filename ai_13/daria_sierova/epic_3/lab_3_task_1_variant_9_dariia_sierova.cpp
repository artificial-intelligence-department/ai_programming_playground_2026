#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    const double a = 0.1;
    const double b = 0.8;
    const int k = 10;
    const int n = 3;
    const double epsilon = 0.0001;

    const double step = (b - a) / k;

    cout << "=======================================================" << endl;
    cout << "                 Обчислення функції" << endl;
    cout << "=======================================================" << endl;
    cout << fixed << setprecision(5);

    for (int j = 0; j <= k; ++j) {
        const double x = a + j * step;

        const double a_0 = x;
        const double x4 = x * x * x * x;

        // 1. Обчислення SN (для n = 3)
        double SN = a_0;
        double a_i = a_0;
        for (int i = 1; i <= n; ++i) {
            a_i = a_i * x4 * (4.0 * i - 3.0) / (4.0 * i + 1.0);
            SN += a_i;
        }

        // 2. Обчислення SE (для точності epsilon)
        double SE = 0.0;
        a_i = a_0;
        int i = 1;
        while (fabs(a_i) >= epsilon) {
            SE += a_i; // Додаємо тільки якщо |a_i| >= epsilon
            a_i = a_i * x4 * (4.0 * i - 3.0) / (4.0 * i + 1.0);
            ++i;
        }

        // 3. Точне значення функції Y
        const double Y = 0.25 * log((1.0 + x) / (1.0 - x)) + 0.5 * atan(x);

        cout << "X=" << setw(8) << x
             << " SN=" << setw(9) << SN
             << " SE=" << setw(9) << SE
             << " Y=" << setw(9) << Y << endl;
    }

    cout << "=======================================================" << endl;
    return 0;
}