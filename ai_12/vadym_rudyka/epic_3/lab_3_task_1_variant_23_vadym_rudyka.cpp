#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double a = 0.1;
    double b = 1;
    int k = 10;
    int n = 15;
    double eps = 0.0001;

    double h = (b - a) / k;

    cout << fixed << setprecision(6);

    cout << "x\t\tS(n)\t\tS(eps)\t\tTochne" << endl;

    for (int i = 0; i <= k; i++) {
        double x = a + i * h;

        // Сума для n = 15
        double sumN = 0;

        for (int j = 1; j <= n; j++) {
            double term = pow(-1, j) * pow(2 * x, 2 * j)
                          / tgamma(2 * j + 1);
            sumN += term;
        }

        // Сума з точністю eps
        double sumEps = 0;
        double term = -2 * x * x;
        int j = 1;

        while (abs(term) >= eps) {
            sumEps += term;

            j++;
            term = pow(-1, j) * pow(2 * x, 2 * j)
                   / tgamma(2 * j + 1);
        }

        // Точне значення
        double exact = 2 * (cos(x) * cos(x) - 1);

        cout << x << "\t"
             << sumN << "\t"
             << sumEps << "\t"
             << exact << endl;
    }

    return 0;
}