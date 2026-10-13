#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    // Ввідні дані, тут a - це нижня межа, b - верхня межа, eps - точність, k - кількість кроків, n - кількість членів ряду
    const double a = 0.1, b = 1.0, eps = 0.0001;
    const int k = 10, n = 15;
    double h = (b - a) / k;

    cout << "Обчислення функції\n";
    for (int i = 0; i <= k; i++) {
        double x = a + i * h;
        double t = 2 * x;
        double t2 = t * t;

        // сума для заданого n
        double term = -t2 / 2;   // перший член
        double SN = term;
        for (int j = 1; j < n; j++) {
            term *= -t2 / ((2 * j + 1) * (2 * j + 2));
            SN += term;
        }

        // сума для заданої точності eps
        term = -t2 / 2;
        double SE = term;
        int j = 1;
        while (fabs(term) >= eps) {
            term *= -t2 / ((2 * j + 1) * (2 * j + 2));
            SE += term;
            j++;
        }

        // точне значення
        double Y = 2 * (cos(x) * cos(x) - 1);

        cout << fixed << setprecision(6)
             << "X=" << x << "  SN=" << SN
             << "  SE=" << SE << "  Y=" << Y << "\n";
    }
    return 0;
}