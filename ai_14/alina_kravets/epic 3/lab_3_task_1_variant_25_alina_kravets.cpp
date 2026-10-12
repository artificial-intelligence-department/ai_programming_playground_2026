/*Лабораторна №3 варіант №25
ШІ-14
Кравець Аліна*/
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    const double STEP = 0.09;
    const double EPS = 0.0001;
    const int N = 20;

    double x = 0.1;
    double sumn = 0;
    double sume = 0;
    double a = 0;
    int n = 0;
    double y = 0;

    while (x <= 1)
    {
        a = x;
        sumn = a;

        for (int i = 0; i < N; i++)
        {
            a = a * pow(x, 2)/(2 * (i+1) * (2*i+3));
            sumn += a;
        }

        a = x;
        sume = 0;
        n = 0;

        while (a >= EPS)
        {
            sume += a;
            a = a * pow(x, 2)/(2 * (n+1) * (2*n+3));
            n++;
        }
    
        y = (exp(x) - exp(-x))/2;

        cout << "X = " << x << "   \t SN = " << sumn << " \t   SE = " << sume << "    \t Y = " << y << endl;

        x += STEP;
    }

    return 0;
}
