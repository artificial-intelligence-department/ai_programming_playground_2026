/*
Lab 2 Task 1 Variant 23
Небеснюк Маркіян
ШІ-12
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
    const int N = 10;      // кількість членів ряду
    double sum = 0;        // змінна для накопичення суми
    double fact = 1;

    for (int n = 1; n <= N; n++) {
        fact = fact * n;                         // n! = (n-1)! * n
        double a = fact / pow(n, sqrt((double)n)); // a_n = n! / n^(sqrt(n))
        sum += a;
    }

    cout << fixed << setprecision(4);
    cout << "Сума 10 членів ряду S = " << sum << endl;
    return 0;
}