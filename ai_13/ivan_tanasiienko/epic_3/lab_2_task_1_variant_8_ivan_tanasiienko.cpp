/*
    Lab 2 - Task 1-8, Танасієнко Іван, ШІ-13, Варіант 8
*/
#include<iostream>
#include<cmath>

/*
Знайти суму ряду з точністю ε=0.0001, загальний член якого
an = (2n - 1)/2^n
*/

int main()
{
    const double EPS = 0.0001;
    double sum = 0;
    int n = 1;
    double a = (2 * n - 1)/std::pow(2, n);;

    while(a >= EPS)
    {
        sum = sum + a;
        n++;
        a = (2 * n - 1)/std::pow(2, n);
    }
    std::cout << "Сума ряду з точністю ε=0.0001: " << sum << std::endl;

    return 0;
}