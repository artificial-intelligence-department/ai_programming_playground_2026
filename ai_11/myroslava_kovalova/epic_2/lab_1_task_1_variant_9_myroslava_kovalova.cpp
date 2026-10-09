/* Лабораторна робота 1, завдання 1
Ковальова Мирослава
ШІ-11
*/

#include <iostream>
#include <cmath>

using namespace std;

int main(){

    float a_f = 100;
    float b_f =0.001;
    double a_d = 100;
    double b_d = 0.001;
    float step1f, step2f, step3f, step4f, step5f, step6f;
    double step1d, step2d, step3d, step4d, step5d, step6d;

    //обчислення у float
    step1f = a_f + b_f;
    step2f = pow(step1f, 4);
    step3f=pow(a_f,4) + 4*pow(a_f,3)*b_f;
    step4f = step2f - step3f;
    step5f = 6*a_f*a_f*b_f*b_f + 4*a_f*pow(b_f,3) + pow(b_f,4);
    step6f = step4f/step5f;

    //обчислення у double
    step1d = a_d + b_d;
    step2d = pow(step1d, 4);
    step3d=pow(a_d,4) + 4*pow(a_d,3)*b_d;
    step4d = step2d - step3d;
    step5d = 6*a_d*a_d*b_d*b_d + 4*a_d*pow(b_d,3) + pow(b_d,4);
    step6d = step4d/step5d;

    cout<<"Результат обчислювання у float: "<<step6f<<endl;
    cout<<"Результат обчислювання у double: "<<step6d<<endl;
   
    return 0;
}