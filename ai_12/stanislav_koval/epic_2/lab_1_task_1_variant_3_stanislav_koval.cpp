/*
Лабораторна робота №1, Завдання 1, Варіант 3
Коваль Станіслав
СШІ-12
*/
#include <iostream>
using namespace std;
#include <iomanip>

int main() {
    //Розрахунки з float
    cout.precision(10);
    const float a1 = 1000.0, b1 = 0.0001;
    float sum1 = a1 + b1;// a + b
    float cb1_1 = sum1 * sum1 * sum1;// (a+b)^3
    float cb_a1 = a1 * a1 * a1;// a^3
    float a2b1_1 = 3 * a1 * a1 * b1;// 3a^2b
    float f1_1 = cb_a1 + a2b1_1;// a^3 + 3a^2b
    float sq_b1 = b1 * b1;// b^2
    float cb_b1 = sq_b1 * b1;// b^3
    float ab2_1 = 3 * a1 * sq_b1;// 3ab^2
    float d1 = ab2_1 + cb_b1;// 3ab^2 + b^3
    float f1_2 = (cb1_1 - f1_1) / d1;
    cout << f1_2 << endl;

    //Розрахунки з double
    const double a2 = 1000.0, b2 = 0.0001;
    double sum2 = a2 + b2;
    double cb2_1 = sum2 * sum2 * sum2;
    double cb_a2 = a2 * a2 * a2;
    double a2b1_2 = 3 * a2 * a2 * b2;
    double f2_1 = cb_a2 + a2b1_2;
    double sq_b2 = b2 * b2;
    double cb_b2 = sq_b2 * b2;
    double ab2_2 = 3 * a2 * sq_b2;
    double d2 = ab2_2 + cb_b2;
    double f2_2 = (cb2_1 - f2_1) / d2;
    cout << f2_2 << endl;
}