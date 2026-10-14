/*
Epic 3
Lab_2_task_1
Кобилянська Софія ШІ-11 варіант 16
*/

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double eps = 0.0001;
    double sum = 0.0;
    double factorial = 1.0;
    double n = 1.0;

    while (true)
    {
        factorial *= n;
        double current = log10(factorial) * exp(-n * sqrt(n));

        if (n > 1 && current < eps)
        {
            break;
        }

        sum += current;
        n++;
    }

    cout << "Сума ряду: " << sum << endl;

    return 0;
}