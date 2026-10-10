/*Епік 2. Лабораторна робота 1. Варіант 12. Завдання 1
Автор: Матішак Михайло
Група: ШІ-11*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    // 1. Обчислення з використанням float
    float a = 1000;
    float b = 0.0001;
    float step1_f = a + b;            // (a+b)
    float step2_f = pow(step1_f, 2);      // (a+b)^2
    float step3_f = pow(a, 2);          // a^2
    float step4_f = 2 * a * b;        // 2ab
    float step5_f = step3_f + step4_f;    // (a^2 + 2ab)
    float upper_f = step2_f - step5_f; // чисельник
    float lower_f = pow(b, 2);     // знаменник
    float result_f = upper_f / lower_f;

    // 2. обчислення з використанням double
    double c = 1000;
    double d = 0.0001;
    double step1_d = c + d;            // (a+b)
    double step2_d = pow(step1_d, 2);      // (a+b)^2
    double step3_d = pow(c, 2);          // a^2
    double step4_d = 2 * c * d;        // 2ab
    double step5_d = step3_d + step4_d;    // (a^2 + 2ab)
    double upper_d = step2_d - step5_d; // чисельник
    double lower_d = pow(d, 2);     // знаменник
    double result_d = upper_d / lower_d;

    // Виведення результатів
    cout << "Результат для FLOAT:  " << result_f << endl;
    cout << "Результат для DOUBLE: " << result_d << endl;

    return 0;
}