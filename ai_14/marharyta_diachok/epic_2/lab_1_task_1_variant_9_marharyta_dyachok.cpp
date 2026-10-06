/* 
Задача: Лабораторна робота №1. Завдання 1. Варіант №9. 
Автор: Дячок Маргарита.
Група: ШІ-14
*/

#include <iostream>
#include <cmath>
using namespace std;
int main() {
    /*a і b дані за умовою, змінні названі відповідно до першої літери в назві виконуваної дії 
    та її номеру в порядку виконання*/
    float a = 100.0;
    float b = 0.001;
    float d1 = a + b; 
    float s1 = pow(d1,4);
    float s2 = pow(a, 4);
    float s3 = pow(a, 3);
    float m1 = 4 * s3 * b; 
    float d2 = s2 + m1; 
    float v1 = s1 - d2; 
    float s4 = pow(a, 2);
    float s5 = pow(b, 2);
    float s6 = pow(b, 3);
    float s7 = pow(b, 4);
    float m2 = 6 * s4 * s5;
    float m3 = 4 * a * s6;
    float d3 = m2 + m3 + s7;
    float dil = v1 / d3;
cout << dil << endl;
//той самий принцип назви змінних, але з припискою _double, що вказує на відповідний тип даних
    double a_double = 100.0;
    double b_double = 0.001;
    double d1_double = a_double + b_double; 
    double s1_double = pow(d1_double,4); 
    double s2_double = pow(a_double, 4);
    double s3_double = pow(a_double, 3);
    double m1_double = 4 * s3_double * b_double; 
    double d2_double = s2_double + m1_double; 
    double v1_double = s1_double - d2_double; 
    double s4_double = pow(a_double, 2);
    double s5_double = pow(b_double, 2);
    double s6_double = pow(b_double, 3);
    double s7_double = pow(b_double, 4);
    double m2_double = 6 * s4_double * s5_double;
    double m3_double = 4 * a_double * s6_double;
    double d3_double = m2_double + m3_double + s7_double;
    double dil_double = v1_double / d3_double;
cout << dil_double << endl;

    return 0;
}