#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    const double a = 0.1, b = 1.0, eps = 0.0001;
    const int k = 10, N = 20;
    const double h = (b - a) / k;

    std::cout << "Обчислення функції" << std::endl << std::fixed << std::setprecision(6);

    for (int i = 0; i <= k; i++) {
        double x = a + i * h;

        // SN:
        double term = 1.0, sn = 1.0;
        for (int n = 1; n <= N; n++) {
            term *= 2 * x / n; // a_n = a_{n-1} * 2x / n
            sn += term;
        }

        // SE:
        term = 1.0;
        double se = 0.0;
        int n = 0;
        while (term >= eps) {
            se += term;
            n++;
            term *= 2 * x / n;
        }

        std::cout << "X=" << x << "  SN=" << sn << "  SE=" << se << "  Y=" << std::exp(2 * x) << "\n";
    }

    return 0;
}