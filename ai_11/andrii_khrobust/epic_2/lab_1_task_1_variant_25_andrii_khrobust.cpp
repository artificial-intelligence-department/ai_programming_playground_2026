/*Задача: лабораторна робота, завдання 1 (варіант 25)
Хробуст Андрій
Група ШІ-11
*/
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a = 1000;
    double b = 0.0001;
    double sum1 = pow(a - b, 3) - (pow(a, 3) - 3 * pow(a, 2) * b);//чисельник
    double sum2 = pow(b, 3) - 3 * a * pow(b, 2);//знаменник
    float a2 = 1000;
    float b2 = 0.0001;
    float sum3 = pow(a2 - b2, 3) - (pow(a2, 3) - 3 * pow(a2, 2) * b2);//чисельник
    float sum4 = pow(b2, 3) - 3 * a2 * pow(b2, 2);//знаменник
    cout << "double: " << sum1 / sum2 << endl;//результат за double
    cout << "float: " << sum3 / sum4;//результат за float

    return 0;
}
