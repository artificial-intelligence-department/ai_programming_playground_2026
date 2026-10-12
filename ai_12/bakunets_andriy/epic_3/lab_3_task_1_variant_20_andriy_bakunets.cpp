#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    const double a = 0.1;       // початок проміжку
    const double b = 1.0;       // кінець проміжку
    const int k = 10;           // кількість кроків
    const int n = 30;           // кількість доданків для суми SN
    const double eps = 0.0001;  // точність для суми SE

    double h = (b - a) / k;     // крок зміни x

    cout << "Обчислення функції" << endl;
    cout << fixed << setprecision(6);

    // зовнішній цикл: змінюємо x від a до b
    for (int i = 0; i <= k; i++) {
        double x = a + i * h;
        double t = x / 2;

        // а) сума для заданого n (арифметичний цикл)
        double c = 1;       // c = t^j / j!, для j = 0
        double sn = 1;      // a0 = 1
        for (int j = 1; j <= n; j++) {
            c = c * t / j;
            sn += (j * j + 1) * c;
        }

        // б) сума для заданої точності (ітераційний цикл)
        int j = 0;
        c = 1;
        double term = 1;    // a0 = 1
        double se = 0;
        while (term >= eps) {
            se += term;
            j++;
            c = c * t / j;
            term = (j * j + 1) * c;
        }

        // точне значення функції
        double y = (x * x / 4 + x / 2 + 1) * exp(x / 2);

        cout << "X=" << x << "  SN=" << setw(9) << sn
             << "  SE=" << setw(9) << se << "  Y=" << setw(9) << y << endl;
    }

    return 0;
}
