/*Epic 2 - Завдання 1 лабораторної 1 варіант 6
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    //Щоб дані виводились в простому вигляді, 7 знаків після коми
    cout << fixed << setprecision(7);

    //Обчислення за допомогою float
    float a_float = 1000.0;
    float b_float = 0.0001;
    //num - numerator (чисельник), den - denominator (знаменник)
    float num_float1 = pow(a_float - b_float, 3);
    float num_float2 = pow(a_float, 3) - 3 * a_float * pow(b_float, 2);
    float num_float = num_float1 - num_float2;
    float den_float = pow(b_float, 3) - 3 * pow(a_float, 2) * b_float;
    float result_float = num_float / den_float;

    cout << "Результат для float: " << result_float << endl;

    //Обчислення за допомогою double
    double a_double = 1000.0;
    double b_double = 0.0001;
    
    double num_double1 = pow(a_double - b_double, 3);
    double num_double2 = pow(a_double, 3) - 3 * a_double * pow(b_double, 2);
    double num_double = num_double1 - num_double2;
    double den_double = pow(b_double, 3) - 3 * pow(a_double, 2) * b_double;
    double result_double = num_double / den_double;

    cout << "Результат для double: " << result_double << endl;

    return 0;
}
