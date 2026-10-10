/*Остання сосиска
Група: ШІ-11
Автор: Шведько Юлія*/

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
    double r;
    double h;

    cin >> r >> h;
    double v = (4.0/3.0)*M_PI*pow(r, 3) + M_PI*pow(r, 2)*(h - 2*r);
    double s = 4*M_PI*pow(r, 2) + 2*M_PI*r*(h - 2*r);

    cout << fixed << setprecision(7) << v << " " << s << endl;

    return 0;
}