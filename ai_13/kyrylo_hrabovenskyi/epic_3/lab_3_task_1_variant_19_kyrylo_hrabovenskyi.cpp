#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
int main()
{
    cout << fixed << setprecision(6);
    const double eps = 0.0001;
    double k = 10;
    double n = 20;
    double a = 0.1;
    double b = 1;

    double step = (b - a) / k;

    for (int i = 0; i <= k; i++)
    {
        double x = a + i * step;

        double sn = 1.0;
        double term_n = 1.0;
        for (int m = 1; m <= n; m++) 
        {
            term_n *= (2.0 * x) / m;
            sn += term_n;
        }

        double se = 1.0;
        double term_e = 1.0;
        int m = 1;

        while (true) 
        {
            term_e *= (2.0 * x) / m;
            if (abs(term_e) < eps) {
                break;
            }
            se += term_e;
            m++;
        }
        double y = exp(2.0 * x);

        cout << "X=" << setw(8) << x << " SN=" << setw(10) << sn << " SE=" << setw(10) << se << " Y=" << setw(10) << y << endl;
    }

    return 0;
    }