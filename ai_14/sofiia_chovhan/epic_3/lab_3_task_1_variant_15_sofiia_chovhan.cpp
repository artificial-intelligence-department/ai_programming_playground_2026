/* Sofiia Chovhan AI 14
   Labratory work 2 variant 15
   */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    const double a = 0.1;
    const double b = 1.0;
    const int k = 10;
    const int N = 30;
    const double eps = 0.0001;

    double h = (b - a) / k;

    cout << fixed << setprecision(8);
    cout << "Calculation of the function" << endl;

    // loop: changing x
    for (int i = 0; i <= k; i++)
    {
        double x = a + i * h;

        // 1 Sum for fixed
        double SN = 0;

        for (int n = 1; n <= N; n++)
        {
            double term = pow(-1.0, n + 1) *
                          pow(x, 2 * n + 1) /
                          (4.0 * n * n - 1);

            SN += term;
        }

        // 2. Sum
        double SE = 0;
        double term = 0;
        int n = 1;

        while (true)
        {
            term = pow(-1.0, n + 1) *
                   pow(x, 2 * n + 1) /
                   (4.0 * n * n - 1);

            if (fabs(term) < eps)
                break;

            SE += term;
            n++;
        }

        // 3 function value
        double Y = ((1.0 + x * x) / 2.0) * atan(x)
                   - x / 2.0;


        cout << "X=" << x
             << " SN=" << SN
             << " SE=" << SE
             << " Y=" << Y << endl;
    }

    return 0;
}
