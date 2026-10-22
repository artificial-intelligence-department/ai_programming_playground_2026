/*Лабораторна 3, варіант 13
Група: ШІ-11
Автор: Юлія Шведько*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
    double e = 0.0001;
    for(double x = 0.1; x <= 1; x += 0.09){ // оскільки (1 - 0.1)/10 = 0.09, то крок дорівнює 0.09
        double sn = 1;
        double se = 1;
        double en = cos(x);
        cout << fixed << setprecision(2) << "X = " << x << "   ";
        cout << fixed << setprecision(5);
        for(int n = 1; n <=20; n++){
            sn += en;
            en = en * cos((n + 1)*x)/((n + 1)*cos(n*x)); // оскільки a(n + 1) = a(n) * cos((n + 1)*x)/((n + 1)*cos(n*x))
        }
        cout << "SN = " << sn << "   ";
        int N = 1;
        en = cos(x);
        while(abs(en) >= e){
            se += en;
            en = en * cos((N + 1)*x)/((N + 1)*cos(N*x));
            N++;
        }
        cout << "SE = " << se << "   ";
        double y = exp(cos(x))*cos(sin(x));
        cout << "Y = " << y << ";";
        cout << endl;
    }
}