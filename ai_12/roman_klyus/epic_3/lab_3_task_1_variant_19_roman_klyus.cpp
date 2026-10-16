#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    const double eps = 0.0001;
    const int k = 10, N = 20;
    constexpr double a = 0.1, b = 1.0;
    constexpr double step = (b - a) / k;



    cout << fixed << setprecision(6);
    cout << "Обчислення функції" << endl;

    // зовнішній цикл: змінюємо x від a до b з кроком h
    for (int i = 0; i <= k; i++) {
        double x = a + i * step;

        // а) арифметичний цикл: сума для заданого n (SN)
        // рекурентна формула: a_(n+1) = a_n * 2x / (n+1), a_0 = 1
        double SN = 1.0;
        double a_n = 1.0; // a_0
        for (int n = 0; n < N; n++) {
            a_n *= 2 * x / (n + 1);
            SN += a_n;
        }

        // б) ітераційний цикл: сума для заданої точності (SE)
        double SE = 0.0;
        a_n = 1.0; // знову a_0
        int n = 0;
        while (a_n >= eps) {
            SE += a_n;
            ++n;
            a_n *= 2 * x / n; // a_n через a_(n-1)
        }

        // точне значення функції
        double Y = exp(2 * x);

        cout << "X=" << x << "  SN=" << SN << "  SE=" << SE << "  Y=" << Y << endl;
    }
}