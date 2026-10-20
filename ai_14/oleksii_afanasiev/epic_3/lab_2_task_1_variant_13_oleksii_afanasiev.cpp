/*
Задача: Lab 2 task 1 (variant - 13)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>
using namespace std;

int main()
{
    const double e = 0.0001;
    double a = 0.5;
    double sum = 0.0;
    int n = 1;

    while(a >= e)
    {
        sum += a;
        a = a / ((3 * n + 1) * (3 * n + 2));
        n++;
    }

    cout << "Сума послідовності" << " = "<< sum << " (точність: epsilon = "<< e << ")" << endl;

    return 0;
}
