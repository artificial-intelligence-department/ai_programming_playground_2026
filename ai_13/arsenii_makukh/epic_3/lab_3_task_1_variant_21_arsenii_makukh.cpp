/*
Назва: Lab 3 - Task 1-21
Автор: Макух Арсеній
Група: ШІ-13
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double a = 0.1, b = 1.0;
    int k = 10;
    int n = 40;
    double e = 0.0001;
    double h = (b - a) / k;

    cout << fixed << setprecision(6);

    for (int i = 0; i <= k; i++) {
        double x = a + i * h;
        double Sn = 0;

        for (int j = 0; j <= n; j++) {
            Sn += pow(-1, j) * pow(x, 2 * j + 1) / (2 * j + 1);
        }

        double Se = 0;
        int j = 0;
        double term = x;

        while (fabs(term) >= e) {
            Se += term;
            j++;
            term = pow(-1, j) * pow(x, 2 * j + 1) / (2 * j + 1);
        }

        double y = atan(x);

        cout << "x = " << x
             << " | y = " << y
             << " | Sn = " << Sn
             << " | Se = " << Se
             << " | |y-Sn| = " << fabs(y - Sn)
             << " | |y-Se| = " << fabs(y - Se) << endl;
    }

    return 0;
}