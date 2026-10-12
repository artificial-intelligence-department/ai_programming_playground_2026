#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    const double pi = acos(-1.0);
    const double eps = 0.0001;
    const int count = 40;
    const double a = pi / 5.0;
    const double b = 9.0 * pi / 5.0;
    const double step = (b - a) / 10.0;

    cout << fixed << setprecision(6);
    cout << "X          SN           SE           Y\n";

    for (int i = 0; i <= 10; ++i) {
        double x = a + i * step;

        // сума перших 40 членів
        double sn = 0.0;
        for (int n = 1; n <= count; ++n) {
            sn += cos(n * x) / n;
        }

        // продовжуємо, доки оцінка похибки не стане меншою за eps
        double se = 0.0;
        int n = 1;
        while (1.0 / (n * sin(x / 2.0)) >= eps) {
            se += cos(n * x) / n;
            ++n;
        }

        double y = -log(2.0 * sin(x / 2.0));
        cout << x << "  " << sn << "  " << se << "  " << y << '\n';
    }
}
