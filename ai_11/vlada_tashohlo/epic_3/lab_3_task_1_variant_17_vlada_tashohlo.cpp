
/* 
Епік 3. Лабораторна робота 3. Варіант 17.
Авторка: Ташогло Влада
Група: ші-11
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    const double a = 0.1, b = 1.0;
    const int k = 10;
    const int n = 10;
    const double eps = 0.0001;
    const double h = (b - a) / k;

    cout << "===== y=cosh(x), x in [0.1,1], n=10, eps=0.0001 =====" << endl;
    cout << left << setw(8) << "x"
         << setw(14) << "S(n=10)"
         << setw(14) << "S(eps)"
         << setw(14) << "exact"
         << setw(6) << "m" << endl;

    // for: перебір x від a до b
    for (int i = 0; i <= k; ++i) {
        double x = a + i * h;

        // а) для заданого n
        double Sn = 1.0, term = 1.0;
        for (int j = 1; j <= n; ++j) {
            term = term * x * x / ((2 * j - 1) * (2 * j));
            Sn += term;
        }

        // б) для заданої точності
        double Seps = 1.0;
        term = 1.0;
        int m = 1, cnt = 1;
        while (1) {
            term = term * x * x / ((2 * m - 1) * (2 * m));
            if (term < eps) break;
            Seps += term;
            m++;
            cnt = m;
        }
        // якщо перший же член < eps, cnt=0 лишається 1.0

        double exact = (exp(x) + exp(-x)) / 2.0;

        cout << left << setw(8) << fixed << setprecision(2) << x
             << setw(14) << fixed << setprecision(6) << Sn
             << setw(14) << fixed << setprecision(6) << Seps
             << setw(14) << fixed << setprecision(6) << exact
             << setw(6) << cnt << endl;
    }
    return 0;
}