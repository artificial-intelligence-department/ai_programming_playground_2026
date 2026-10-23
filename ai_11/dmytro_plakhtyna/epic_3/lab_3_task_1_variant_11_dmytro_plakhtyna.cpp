#include <iostream>
using namespace std;

int main() {
    double a = 0.1;
    double b = 1.0;
    int n = 10;
    double eps = 0.0001;
    int k = 10;
    double h = (b - a) / k;

    cout << "Обчислення функції" << endl;

    for (double x = a; x <= b + h / 2; x += h) {

        // SN: сума n доданків
        double c = 1;
        double sn = 1;
        for (int i = 1; i <= n; i++) {
            c = c * x * x / i;
            double t = (2 * i + 1) * c;
            sn = sn + t;
        }

        // SE: сума з точністю eps
        c = 1;
        double t = 1;
        double se = 0;
        int i = 0;
        while (t >= eps) {
            se = se + t;
            i++;
            c = c * x * x / i;
            t = (2 * i + 1) * c;
        }

        // Y: точне значення, e^(x*x) рахуємо рядом
        double e = 1;
        double d = 1;
        for (int m = 1; m <= 30; m++) {
            d = d * x * x / m;
            e = e + d;
        }
        double y = (1 + 2 * x * x) * e;

        cout << "X=" << x << "  SN=" << sn << "  SE=" << se << "  Y=" << y << endl;
    }

    return 0;
}