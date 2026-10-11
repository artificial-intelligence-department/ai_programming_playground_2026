#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    double a = 0.1, b = 1;
    const int k = 10;
    const int N = 40;
    const double limit = 0.0001; 
    const double step = (b - a) / k;

    cout << fixed << setprecision(6);
    
    for (int i = 0; i <= k; i++) {
        double x = a + i * step;

        double a_n = x;
        double S_N = x;
        for (int n = 1; n < N; n++) {
            a_n *= -x * x * (2*n - 1) / (2*n + 1);
            S_N += a_n;
        }

        a_n = x;
        double S_E = x;
        int n = 1;
        while (true) {
           a_n *= -x * x * (2*n - 1) / (2*n + 1);
            if (fabs(a_n) < limit) break;
            S_E += a_n;
            n++;
        }

        cout << "X=" << x << "  SN=" << S_N
             << "  SE=" << S_E << "  Y=" << atan(x) << endl;
    }
    return 0;
}