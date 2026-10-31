#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    cout << fixed << setprecision(6);
    const double eps = 0.0001;
    double x = 1.0 / 2.0;
    double y = 1.0 / 3.0;
    int n = 1;
    double an = x + y;
    double sum = 0.0;

    while (an >= 0.0001)
    {
        sum += an;

        x *= 0.5;
        y *= (1.0 / 3.0);

        an = x + y;
        n++;
    }
    cout << "==================\n";
    cout << "Results:\n";
    cout << "==================\n";
    cout << "total sum:\t" << sum << endl;
    cout << "sum of all numbers:\t" << n - 1 << endl;
    cout << "the last forgotten number:\t" << an << endl;
    cout << "==================\n";

    return 0;
}