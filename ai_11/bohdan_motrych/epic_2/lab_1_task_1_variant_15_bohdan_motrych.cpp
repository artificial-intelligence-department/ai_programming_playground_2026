#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // Ініціналізація змінних для float
    float a_f = 1000.0f;
    float b_f = 0.0001f;

    // Обчислення значень для float
    float num1_f = pow(a_f + b_f, 3);
    float num2_f = pow(a_f, 3);
    float numerator_f = num1_f - num2_f;

    float den1_f = 3 * a_f * pow(b_f, 2);
    float den2_f = pow(b_f, 3);
    float den3_f = 3 * pow(a_f, 2) * b_f;
    float denominator_f = den1_f + den2_f + den3_f;

    float result_float = numerator_f / denominator_f;

    // Ініціналізація змінних для double
    double a_d = 1000.0;
    double b_d = 0.0001;

    // Обчислення значень для double
    double num1_d = pow(a_d + b_d, 3);
    double num2_d = pow(a_d, 3);
    double numerator_d = num1_d - num2_d;

    double den1_d = 3 * a_d * pow(b_d, 2);
    double den2_d = pow(b_d, 3);
    double den3_d = 3 * pow(a_d, 2) * b_d;
    double denominator_d = den1_d + den2_d + den3_d;

    double result_double = numerator_d / denominator_d;

    // Виведення результатів
    cout << "Float result:  " << result_float << endl;
    cout << "Double result: " << result_double << endl;

    return 0;
}