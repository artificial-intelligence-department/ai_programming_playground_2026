/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
#include <cmath>

using namespace std;

int main() {
    float a = 1000.0;
    float b = 0.0001;

    // Розбиваю складну формулу на частини, щоб не заплутатися в дужках
    float part1 = pow(a - b, 3);
    float part2 = pow(a, 3) - 3 * a * pow(b, 2);
    float den = pow(b, 3) - 3 * pow(a, 2) * b; // Знаменник
    
    float num = part1 - part2; // Чисельник
    float result = num / den;

    cout << "Результат обчислення (float): " << result << endl;


    double a_d = 1000.0;
    double b_d = 0.0001;

    double part1_d = pow(a_d - b_d, 3);
    double part2_d = pow(a_d, 3) - 3 * a_d * pow(b_d, 2);
    double den_d = pow(b_d, 3) - 3 * pow(a_d, 2) * b_d;

    double num_d = part1_d - part2_d;
    double result_d = num_d / den_d;

    cout << "Результат обчислення (double): " << result_d << endl;


}