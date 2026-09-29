/* Задача: Лабораторна робота, завдання 1 
* Поліщук Вероніка
* Група 14
*/

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // Обчислення з float
    float a_f = 1000.0;
    float b_f = 0.0001;

    // Чисельник
    float f1_f = pow(a_f + b_f, 3);
    float f2_f = pow(a_f, 3);
    float num_f = f1_f - f2_f; // (a+b)^3 - a^3

    // Знаменник
    float f3_f = 3 * a_f * pow(b_f, 2);
    float f4_f = pow(b_f, 3);
    float f5_f = 3 * pow(a_f, 2) * b_f;
    float den_f = f3_f + f4_f + f5_f; // 3*a*b^2 + b^3 + 3*a^2 * b

    float res_f = num_f / den_f;

    // Обчислення з double
    double a_d = 1000.0;
    double b_d = 0.0001;

    // Чисельник
    double f1_d = pow(a_d + b_d, 3);
    double f2_d = pow(a_d, 3);
    double num_d = f1_d - f2_d; // (a+b)^3 - a^3

    // Знаменник
    double f3_d = 3 * a_d * pow(b_d, 2);
    double f4_d = pow(b_d, 3);
    double f5_d = 3 * pow(a_d, 2) * b_d;
    double den_d = f3_d + f4_d + f5_d; // 3*a*b^2 + b^3 + 3*a^2 * b

    double res_d = num_d / den_d;

    // Вивід результатів
    cout << "Результат float  " << res_f << endl;
    cout << "Результат double " << res_d << endl;

    return 0;
}
