/*
Задача: Lab 3 task 1 (variant - 7)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    const double e = 0.0001;
    const double a = 0.1;
    const double b = 1;
    const int k = 10;
    const double step = (b - a) / k;
    const int n = 10;

    double a_n = 1.0, a_e = 1.0;
    double sum_n = 0.0;
    double sum_e = 0.0;

    double x;

    int count = 0;

    for(double i = 0; i <= k; i++)
    {
        x = a + i * step;

        for(int j = 0; j <= n; j++)
        {
            sum_n += a_n;
            a_n = a_n * -((x*x) / ((2*j + 1)*(2*j + 2)));
        }
        
        while(fabs(a_e) >= e)
        {
            sum_e += a_e;
            a_e = a_e * -((x*x) / ((2*count + 1)*(2*count + 2)));
            count++;
        }

        cout << "X = " << x << " SN = " << sum_n << " SE = " << sum_e << " Y = " << cos(x) << endl;

        a_n = 1.0;
        a_e = 1.0;
        sum_n = 0.0;
        sum_e = 0.0;
        count = 0;
    }

    return 0;
}
