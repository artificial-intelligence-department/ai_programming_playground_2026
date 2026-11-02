#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    const double x = 0.0001;
    int n = 1;
    double a = 1;
    double sum = a;
    while (abs(a) > x){
        a = a*pow(n, n)*(-1)/pow((n+1), (n+1));
        sum += a;
        n++;
    }
    cout << fixed << setprecision(4) << sum << endl;
}