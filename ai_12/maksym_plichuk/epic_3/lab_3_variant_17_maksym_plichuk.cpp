#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main(){
    const double a = 0.1;
    const double b = 1.0;
    const int k = 10;
    const int n = 10;
    const double eps = 0.0001;

    const double step = (b - a) / k;

    cout << fixed << setprecision(6);

    for (int i = 0; i < k; i++)
    {
        double x = a + i * step;
        double SN = 1.0;
        double u_n = 1.0;
        for (int m = 1; m <= n; m++) {
            u_n *= (x * x) / ((2 * m - 1) * (2 * m));
            SN += u_n;
        }

        double SE = 1.0;
        double u_e = 1.0;
        int m = 1;
        while (true) {
            u_e *= (x * x) / ((2 * m - 1) * (2 * m));
            if (u_e < eps) {
                break;
            }
            SE += u_e;
            m++;
        }

        double Y = (exp(x) + exp(-x)) / 2.0;
        cout << "X=" << setw(7) << x << "    SN=" << setw(8) << SN << "    SE=" << setw(8) << SE << "    Y=" << setw(8) << Y << endl;
    }
    
}