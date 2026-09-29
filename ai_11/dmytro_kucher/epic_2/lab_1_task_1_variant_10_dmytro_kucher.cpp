/*
Епік 2. Лабораторна робота №1. Завдання 1
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
#include<cmath>
#include <iomanip>
using namespace std;

int main() {

    float a1 = 100, b1 = 0.001;

    float d11 = pow((a1-b1), 4);
    float d12 = pow(a1, 4);
    float d13 = 4 * pow(a1, 3) * b1;
    float d14 = 6 * pow(a1, 2) * pow(b1, 2);
    float d15 = pow(b1, 4);
    float d16 = 4 * a1 * pow(b1, 3);
    float d17 = d12 - d13 + d14;
    float d18 = d11 - d17;
    float d19 = d15 - d16;
    float r1 = d18 / d19; 

    cout << "\nРезультат типу float: " << fixed << setprecision(10) << r1 << endl;

    double a2 = 100, b2 = 0.001;

    double d21 = pow((a2-b2), 4);
    double d22 = pow(a2, 4);
    double d23 = 4 * pow(a2, 3) * b2;
    double d24 = 6 * pow(a2, 2) * pow(b2, 2);
    double d25 = pow(b2, 4);
    double d26 = 4 * a2 * pow(b2, 3);
    double d27 = d22 - d23 + d24;
    double d28 = d21 - d27;
    double d29 = d25 - d26;
    double r2 = d28 / d29; 

    cout << "Результат типу double: " << fixed << setprecision(10) << r2 << endl;

    return 0;
}