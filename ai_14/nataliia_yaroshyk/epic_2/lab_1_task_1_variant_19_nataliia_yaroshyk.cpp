/* Лабораторна 1 завдання 1
   Варіант 19
   Ярошик Наталія
   ШІ-14
*/
#include <iostream>
#include <math.h>
using namespace std;

int main(){
    //float
    float a = 100;
    float b = 0.001;

    float step1 = a+b;
    float step2 = pow(step1, 4);
    float step3 = pow(a, 4);
    float step4 = pow(a, 3);
    float step5 = pow(a, 2);
    float step6 = pow(b, 2);
    float step7 = step3 + 4*step4*b + 6*step5*step6;
    float step8 = step2 - step7;
    float step9 = pow(b, 3);
    float step10 = pow(b, 4);
    float step11 = 4*a*step9 + step10;
    float step12 = step8/step11;

    cout << step12 << endl;

    //double
    double a1 = 100;
    double b1 = 0.001;

    double step01 = a1+b1;
    double step02 = pow(step01, 4);
    double step03 = pow(a1, 4);
    double step04 = pow(a1, 3);
    double step05 = pow(a1, 2);
    double step06 = pow(b1, 2);
    double step07 = step03 + 4*step04*b1 + 6*step05*step06;
    double step08 = step02 - step07;
    double step09 = pow(b1, 3);
    double step010 = pow(b1, 4);
    double step011 = 4*a1*step09 + step010;
    double step012 = step08/step011;

    cout << step012 << endl;
    return 0;
}