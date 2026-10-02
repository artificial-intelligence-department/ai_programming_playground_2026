
/* 
Епік 2. Лабораторна робота 1. Варіант 23. Завдання 1.
Авторка: Ташогло Влада
Група: ші-11
*/

#include <iostream>
#include <cmath>

using namespace std;

int main() {

    // Обчислення для типу float
    cout << "Обчислення для типу змінних float" << endl;

    // Початкові значення
    int a_f = 1000;
    float b_f = 0.0001f;

    // Обчислення чисельника
    float c_f = pow(a_f + b_f, 3);
    float d_f = pow(a_f, 3);
    float e_f = 3 * pow(a_f, 2) * b_f;
    float f_f = d_f + e_f;
    float numerator_f = c_f - f_f;

    // Обчислення знаменника
    float g_f = 3 * a_f * pow(b_f, 2);
    float h_f = pow(b_f, 3);
    float denominator_f = g_f + h_f;

    // Результат для float
    float result_f = numerator_f / denominator_f;

    cout << "Результат: " << result_f << endl;

    // Обчислення для типу double
    cout << "Обчислення для типу змінних double" << endl;

    // Початкові значення
    int a_d = 1000;
    double b_d = 0.0001;

    // Обчислення чисельника
    double c_d = pow(a_d + b_d, 3);
    double d_d = pow(a_d, 3);
    double e_d = 3 * pow(a_d, 2) * b_d;
    double f_d = d_d + e_d;
    double numerator_d = c_d - f_d;

    // Обчислення знаменника
    double g_d = 3 * a_d * pow(b_d, 2);
    double h_d = pow(b_d, 3);
    double denominator_d = g_d + h_d;

    // Результат для double
    double result_d = numerator_d / denominator_d;

    cout << "Результат: " << result_d << endl;

    return 0;
    
}