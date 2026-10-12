#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    const double A = 0.1, B = 1.0;
    const int K = 10;       // кількість кроків
    const int N = 10;       // кількість доданків для випадку а)
    const double EPS = 0.0001;
    const double ln3 = log(3.0);
    const double step = (B - A) / K;

    cout << "Обчислення функції y = 3^x" << endl;
    cout << setw(8) << "X" << setw(14) << "SN" << setw(14) << "SE" << setw(14) << "Y" << endl;

    for (int i = 0; i <= K; i++) {
        double x = A + i * step;

        // а) для заданого n: a_k = a_(k-1) * x * ln3 / k
        double term = 1, sn = 1;
        for (int k = 1; k <= N; k++) {
            term *= x * ln3 / k;
            sn += term;
        }

        // б) для заданої точності
        term = 1;
        double se = 1;
        int k = 1;
        while (true) {
            term *= x * ln3 / k;
            if (fabs(term) < EPS) break;
            se += term;
            k++;
        }

        cout << fixed << setprecision(6)
             << setw(8) << x << setw(14) << sn << setw(14) << se
             << setw(14) << pow(3.0, x) << endl;
    }
    return 0;
}
