#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Lab 3, Task 1 (варіант 9)
double exactValue(double x) {
    return 0.25 * log((1.0 + x) / (1.0 - x)) + 0.5 * atan(x);
}

double seriesByN(double x, int n) {
    double sum = 0.0;
    double power = x;
    const double x4 = x * x * x * x;
    for (int k = 0; k <= n; k++) {
        sum += power / (4 * k + 1);
        power *= x4;
    }
    return sum;
}

double seriesByEps(double x, double eps, int &terms) {
    double sum = 0.0;
    double power = x;
    const double x4 = x * x * x * x;
    int k = 0;
    terms = 0;
    while (true) {
        double a = power / (4 * k + 1);
        if (fabs(a) < eps)
            break;
        sum += a;
        terms++;
        power *= x4;
        k++;
    }
    return sum;
}

int main() {
    const double A = 0.1, B = 0.8;
    const int K = 10;
    const int N = 3;
    const double EPS = 0.0001;
    const double step = (B - A) / K;

    cout << "Lab 3 Task 1, variant 9\n";
    cout << "y = 1/4*ln((1+x)/(1-x)) + 1/2*arctg(x), x in [" << A << "; " << B
         << "], крок = " << step << ", n = " << N << ", eps = " << EPS << "\n\n";
    cout << fixed << setprecision(6);
    cout << setw(6) << "x" << setw(14) << "S(n=3)" << setw(14) << "S(eps)"
         << setw(8) << "terms" << setw(14) << "y точне"
         << setw(14) << "|y-S(n)|" << setw(14) << "|y-S(eps)|" << '\n';

    for (int i = 0; i <= K; i++) {
        double x = A + i * step;
        int terms;
        double sn = seriesByN(x, N);
        double se = seriesByEps(x, EPS, terms);
        double y = exactValue(x);
        cout << setw(6) << x << setw(14) << sn << setw(14) << se
             << setw(8) << terms << setw(14) << y
             << setw(14) << fabs(y - sn) << setw(14) << fabs(y - se) << '\n';
    }
    return 0;
}