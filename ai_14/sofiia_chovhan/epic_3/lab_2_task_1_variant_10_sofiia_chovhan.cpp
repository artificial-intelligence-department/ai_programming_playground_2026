/* Sofiia Chovhan AI 14
   Labratory work 2 variant 10
   n! / (2n)!*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    const double eps = 0.0001;
    int n = 0;
    int count = 0;
    double a = 1;
    double sum = 0;

    while (a >= eps)
    {
        sum += a;
        count++;

        a = a / (2.0 * (2 * n + 1));
        n++;
    }
    cout << fixed << setprecision(6);
    cout << "Sum of the series: " << sum << endl;
    cout << "Number of terms: " << count << endl;
    return 0;
}