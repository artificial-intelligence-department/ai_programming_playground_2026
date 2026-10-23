#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    const double eps = 0.0001;

    double a = 1.0;   // a_1 = 1^3 / 0! = 1
    double sum = 0.0;
    int n = 1;

    while (a >= eps) {
        sum += a;

        double nd = n;
        a = a * (nd + 1) * (nd + 1) * (nd + 1)
              / (nd * nd * nd * (3 * nd - 2) * (3 * nd - 1) * (3 * nd));
        n++;
    }

    cout << "Сума ряду: " << fixed << setprecision(4) << sum << endl;
    return 0;
}