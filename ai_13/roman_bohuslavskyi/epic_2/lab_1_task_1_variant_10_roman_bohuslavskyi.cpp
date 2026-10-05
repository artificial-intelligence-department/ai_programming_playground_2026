#include <iostream>
#include <cmath>
using namespace std;

int main() {
    // Початкові значення типу float
    float a_float = 100.0f;
    float b_float = 0.001f;

    // Обчислення проміжних значень для float
    float first_float = pow(a_float - b_float, 4);
    float second_float = pow(a_float, 4) - 4 * pow(a_float, 3) * b_float + 6 * pow(a_float, 2) * pow(b_float, 2);
    float numerator_float = first_float - second_float;
    float denominator_float = pow(b_float, 4) - 4 * a_float * pow(b_float, 3);

    // Результат для float
    float result_float = numerator_float / denominator_float;


    // Початкові значення типу double
    double a_double = 100.0;
    double b_double = 0.001;

    // Обчислення проміжних значень для double
    double first_double = pow(a_double - b_double, 4);
    double second_double = pow(a_double, 4) - 4 * pow(a_double, 3) * b_double + 6 * pow(a_double, 2) * pow(b_double, 2);
    double numerator_double = first_double - second_double;
    double denominator_double = pow(b_double, 4) - 4 * a_double * pow(b_double, 3);

    // Результат для double
    double result_double = numerator_double / denominator_double;


    // Вивід результатів
    cout << "Результат для float: " << result_float << endl;
    cout << "Результат для double: " << result_double << endl;

    return 0;
}