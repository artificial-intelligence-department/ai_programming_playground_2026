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

    cout << "Обчислення функції \n";
    cout << fixed << setprecision(6);

    for (double x = a; x <= b+step/2; x+=step) {

        double sumN = 0;
        for (int n = 1; n<=nMax; n++) {

            double An = pow(x, n) * sin(n * M_PI / 4);
            sumN += An;
        }

        double sumE = 0;
        for (int n = 1; ; n++) {

            double An = pow(x, n) * sin(n * M_PI / 4);
            
            sumE += An;

            if (fabs(pow(x, n)) < e) break;
        }

        double y = (x * sin(M_PI / 4)) / (1 - 2 * x * cos(M_PI / 4) + pow(x, 2));
     
        cout << "X = " << setw(7) << x;
        cout << "\nSN = " << setw(7) << sumN;
        cout << "\nSE = " << setw(7) << sumE;
        cout << "\nY = " << setw(7) << y << "\n\n"; 
    }

    return 0;
}