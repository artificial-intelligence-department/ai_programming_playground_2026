/*
Lab 1 Task 1 Variant 6
Небеснюк Маркіян
ШІ-12
*/
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // Обчислення з використанням типу float
    float af = 1000;
    float bf = 0.0001;

    // Обчислення чисельника
    float f1 = pow((af-bf), 3);
    float f2 = pow(af, 3);
    float f3 = 3 * af * pow(bf, 2);
    float f4 = f2 - f3;
    float f5 = f1 - f4;

    // Обчислення знаменника
    float f6 = pow(bf, 3);
    float f7 = 3 * pow(af, 2) * bf;
    float f8 = f6 - f7;

    
    float result_float = f5 / f8; // Результат ділення

    // Обчислення з використанням типу double
    double ad = 1000;
    double bd = 0.0001;

    // Обчислення чисельника
    double d1 = pow((ad-bd), 3);
    double d2 = pow(ad, 3);
    double d3 = 3 * ad * pow(bd, 2);
    double d4 = d2 - d3;
    double d5 = d1 - d4;

    // Обчислення знаменника
    double d6 = pow(bd, 3);
    double d7 = 3 * pow(ad, 2) * bd;
    double d8 = d6 - d7;

    double result_double = d5 / d8; // Результат ділення

    // Виведення результатів
    cout << "float: " << result_float << endl;
    cout << "double: " << result_double << endl;
    return 0;
}