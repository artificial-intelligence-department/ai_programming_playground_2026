/*
  Назва задачі: Lab 3 Task 1
  Варіант: 15
  Автор: Діхтяр Юлія
  Група: ai-13
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    const double a = 0.1;
    const double b = 1.0;
    const double epsilon = 0.0001;
    const int k = 10;
    const int n = 30;

    double step = (b - a) / k;

    cout << fixed << setprecision(8);
    cout << "Обчислення функції" << endl;

    for (int i = 0; i <= k; i++) {
        double x = a + i * step;

        double SN = 0.0;
        double SE = 0.0;

        // Сума для заданого n.
        for (int j = 1; j <= n; j++) {
            double term = pow(-1.0, j + 1) * pow(x, 2 * j + 1) / (4.0 * j * j - 1);

            SN += term;
        }

        // Сума для заданої точності.
        int j = 1;
        double term = pow(-1.0, j + 1) * pow(x, 2 * j + 1) / (4.0 * j * j - 1);

        while (fabs(term) > epsilon) {
            SE += term;
            j++;

            term = pow(-1.0, j + 1) * pow(x, 2 * j + 1) / (4.0 * j * j - 1);
        }

        // Точне значення функції.
        double Y = ((1 + x * x) / 2.0) * atan(x) - x / 2.0;

        cout << "X=" << x
             << "  SN=" << SN
             << "  SE=" << SE
             << "  Y=" << Y << endl;
    }

    return 0;
}