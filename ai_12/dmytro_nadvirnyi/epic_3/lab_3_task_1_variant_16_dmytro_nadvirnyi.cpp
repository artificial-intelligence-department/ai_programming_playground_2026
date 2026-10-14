#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    const double PI = acos(-1.0);
    const double a = PI / 5, b = PI;
    const int k = 10, N = 40;
    const double eps = 0.0001;
    double h = (b - a) / k;

    cout << "Обчислення функції\n";
    for (int i = 0; i <= k; i++) {
        double x = a + i * h;

        // а) для заданого n (арифметичний цикл)
        double SN = 0;
        for (int n = 1; n <= N; n++)
            SN += cos((2 * n - 1) * x) / pow(2 * n - 1, 2);

        // б) для заданої точності (ітераційний цикл)
        double SE = 0, term;
        int n = 1;
        do {
            term = cos((2 * n - 1) * x) / pow(2 * n - 1, 2);
            SE += term;
            n++;
        } while (fabs(term) >= eps);

        // точне значення
        double Y = PI * PI / 8 - PI / 4 * fabs(x);

        cout << fixed << setprecision(6)
             << "X=" << x << "  SN=" << SN
             << "  SE=" << SE << "  Y=" << Y << "\n";
    }
    return 0;
}