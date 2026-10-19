/*Lab3 task1
Artem Mnikh
AI_14
*/
#include <cmath>
#include <iostream>
using namespace std;

int factorial(int n, int result = 1, int i = 1);

int main()
{
    int k = 10;
    double a = 0.1;
    double b = 1;
    double step = (b - a) / k;
    int n = 20;
    double simple_e = 0.0001;
    double sumN, sumE, elementN, elementE, Y;
    int i;
    for (double x = a; x < b; x += step)
    {
        sumN = 1.0;
        elementN = 1.0;
        for (int j = 1; j <= n; ++j)
        {
            elementN *= (2 * x) / j;
            sumN += elementN;
        }
        sumE = 1.0;
        elementE = 1.0;
        i = 1;
        while (true)
        {
            elementE *= (2 * x) / i;
            if (elementE < simple_e) break;
            sumE += elementE;
            ++i;
        }
        Y = exp(2 * x);
        cout << "X = " << x << ", SN = " << sumN << ", SE = " << sumE << ", Y = " << Y << endl;
    }

    return 0;
}
