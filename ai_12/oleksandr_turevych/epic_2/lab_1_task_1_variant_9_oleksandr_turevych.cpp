/* Задача: Лабораторна робота, завдання 1
* Туревич Олександр
* Група ШІ-12
*/

#include <iostream>
#include <cmath> // Підключаємо бібліотеку для математичної функції pow()
using namespace std;

int main() {

    // Обчислення з використанням типу float
    float a_f = 100;
    float b_f = 0.001;

    // чисельник (a + b)^4 - (a^4 + 4*a^3*b)
    float stp1_f = pow(a_f + b_f, 4);
    float stp2_f = pow(a_f, 4) + 4 * pow(a_f, 3) * b_f;
    float num_f = stp1_f - stp2_f;

    //знаменник (6*a^2*b^2 + 4*a*b^3 + b^4)
    float den_f = 6 * pow(a_f, 2) * pow(b_f, 2) + 4 * a_f * pow(b_f, 3) + pow(b_f, 4);
    float res_f = num_f / den_f;


    // Обчислення з використанням типу double
    double a_d = 100;
    double b_d = 0.001;

    // чисельник (a + b)^4 - (a^4 + 4*a^3*b)
    double stp1_d = pow(a_d + b_d, 4);
    double stp2_d = pow(a_d, 4) + 4 * pow(a_d, 3) * b_d;
    double num_d = stp1_d - stp2_d;

    //знаменник (6*a^2*b^2 + 4*a*b^3 + b^4)
    double den_d = 6 * pow(a_d, 2) * pow(b_d, 2) + 4 * a_d * pow(b_d, 3) + pow(b_d, 4);
    double res_d = num_d / den_d;
    cout << "Результат для float: " << res_f << endl;
    cout << "Результат для double: " << res_d << endl;

    return 0;
}