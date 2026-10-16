/*
Епік 3. Лабораторна робота №3. Завдання №1. Варіант №8
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main () {

    const int k = 10;
    const double a = 0.1;
    const double b = 0.8;
    const int nMax = 40;
    const double e = 0.0001;

    double step = (b-a)/k;

    cout << "\nОбчислення функції \n";
    cout << fixed << setprecision(6);

    for (double x = a; x <= b+step/2; x+=step) {

        double SN = 0;
        for (int n = 1; n<=nMax; n++) {

            double An = pow(x, n) * sin(n * M_PI / 4);
            SN += An;
        }

        double SE = 0;
        for (int n = 1; ; n++) {

            double An = pow(x, n) * sin(n * M_PI / 4);
            
            SE += An;

            if (fabs(pow(x, n)) < e) break;
        }

        double Y = (x * sin(M_PI / 4)) / (1 - 2 * x * cos(M_PI / 4) + pow(x, 2));
     
        cout << "X = " << setw(7) << x;
        cout << "   SN = " << setw(7) << SN;
        cout << "   SE = " << setw(7) << SE;
        cout << "   Y = " << setw(7) << Y << "\n"; 
    }

    return 0;
}