#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double a = 0.1, b = 1;
    int k = 10, n = 30;
    double eps = 0.0001;
    double h = (b - a) / k;

    cout << "Обчислення функції" << endl;

    for (int i = 0; i <= k; i++) {            // зовнішній цикл: зміна x
        double x = a + i * h;
        double t = x / 2;

        // а) для заданого n
        double s1 = 0, p = 1;                 // p = t^j / j!
        for (int j = 0; j <= n; j++) {
            s1 += (j * j + 1) * p;
            p *= t / (j + 1);
        }

        // б) для заданої точності
        double s2 = 0, q = 1, term;
        int j = 0;
        do {
            term = (j * j + 1) * q;
            s2 += term;
            j++;
            q *= t / j;
        } while (fabs(term) >= eps);

        // точне значення
        double y = (x * x / 4 + x / 2 + 1) * exp(t);

        cout << "X=" << x << "\tSN=" << s1 << "\tSE=" << s2 << "\tY=" << y << endl;
    }
    return 0;
}