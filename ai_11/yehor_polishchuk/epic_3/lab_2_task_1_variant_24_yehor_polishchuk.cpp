#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    const int N = 9;           
    const double eps = 0.0001; // точність

    int n = 1;
    double a = exp(-1.0);      // a1 = e^(-sqrt(1))
    double S = 0;

    cout << fixed << setprecision(6);

    while (n <= N && a >= eps) {
        S += a;
        cout << "a[" << n << "] = " << a << endl;

        a = a * exp(-(sqrt(n + 1.0) - sqrt((double)n)));
        n++;
    }

    cout << "Сума S = " << S << endl;

    return 0;
}