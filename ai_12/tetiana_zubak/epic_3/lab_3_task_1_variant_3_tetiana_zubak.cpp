/*
Лабораторна робота 3, варіант 3
Зубак Тетяна
ШІ-12
*/
#include <iostream>
#include <cmath>

using namespace std;


const int k = 10, n = 10;
const double e = 0.0001, a = 0.1,b = 1, s = (b -a)/k;

double sumN(double x){
    double an, SN;
        an = x;
        SN = x;
        for(int j = 0; j < n; j++){
            an *= (-x * x) / ((2 * j + 2) * (2 * j + 3));
            SN += an;
        }
    return SN;
}

double sumE(double x){
    double an = x, SE = x, j = 0;
        while(fabs(an) >= e){
            an *= (-x * x) / ((2 * j + 2) * (2 * j + 3));
            SE += an;
            j++;
        }
    return SE;
}

int main(){
    for(int i = 0; i <= k; i++){
        double x = a + i*s;
        cout << "X =" << x << "   SN = " << sumN(x) << "   SE = " << sumE(x) << "   Y = " << sin(x) << endl;
    }

    return 0;
}