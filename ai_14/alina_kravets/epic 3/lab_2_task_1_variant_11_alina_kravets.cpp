/*Лабораторна №2 варіант №11
ШІ-14
Кравець Аліна*/
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    const double EPS = 0.0001;

    double a = 1;
    int n = 1;
    double sum = 0;

    while (a >= EPS)
    {
        sum += a;
        a = a * pow(n/(n+1.0), n);
        n++;
    }

    cout << "Сума: " << sum << endl;

    return 0;
}
