/*
Lab 3, Нагірний Назарій, ШІ-13, Варіант № 20
*/
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    const double a = 0.1;
    const double b = 1.0;
    const int k = 10;
    const int N = 30;
    const double eps = 0.0001;
    const double step = (b - a) / k;

    cout << "X\tSN (N=30)\tSE (eps)\tY (Exact)" << endl;
    cout << "--------------------------------------------------" << endl;

    for (int i = 0; i <= k; i++) {
        double x = a + i * step;

        double SN = 1.0;
        double termN = 1.0;
        for (int n = 1; n < N; n++) {
            termN *= x * (n * n + 1) / (2.0 * n * (n * n - 2 * n + 2));
            SN += termN;
        }

        double SE = 1.0;
        double termE = 1.0;
        int n = 1;
        while (true) {
            termE *= x * (n * n + 1) / (2.0 * n * (n * n - 2 * n + 2));
            if (abs(termE) < eps) break;
            SE += termE;
            n++;
        }

        double Y = (x * x / 4.0 + x / 2.0 + 1.0) * exp(x / 2.0);

        cout << fixed << setprecision(4) << x << "\t"
             << setprecision(6) << SN << "\t"
             << SE << "\t"
             << Y << endl;
    }

    return 0;
}