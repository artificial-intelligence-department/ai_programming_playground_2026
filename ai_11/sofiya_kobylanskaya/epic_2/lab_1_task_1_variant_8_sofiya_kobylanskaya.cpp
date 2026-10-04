/*
Епік 2. Лабораторна робота 1. Варіант 8. Завдання 1.
Автор: Кобилянська Софія
Група: ші-11
*/

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    float a_1 = 100;
    float b_1 = 0.001;

    float c_1 = pow(a_1 + b_1, 4);
    float d_1 = pow(a_1, 4);
    float e_1 = 4 * pow(a_1, 3) * b_1;
    float f_1 = 6 * pow(a_1, 2) * pow(b_1, 2);

    float g_1 = 4 * a_1 * pow(b_1, 3);
    float h_1 = pow(b_1, 4);

    float numerator_1 = c_1 - (d_1 + e_1 + f_1);
    float denominator_1 = g_1 + h_1;

    float result_1 = numerator_1 / denominator_1;

    double a_2 = 100;
    double b_2 = 0.001;

    double c_2 = pow(a_2 + b_2, 4);
    double d_2 = pow(a_2, 4);
    double e_2 = 4 * pow(a_2, 3) * b_2;
    double f_2 = 6 * pow(a_2, 2) * pow(b_2, 2);

    double g_2 = 4 * a_2 * pow(b_2, 3);
    double h_2 = pow(b_2, 4);

    double numerator_2 = c_2 - (d_2 + e_2 + f_2);
    double denominator_2 = g_2 + h_2;

    double result_2 = numerator_2 / denominator_2;

    cout << "float:  " << result_1 << endl;
    cout << "double: " << result_2 << endl;

    return 0;
}