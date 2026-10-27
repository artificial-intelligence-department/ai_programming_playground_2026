
/*
Lab 1 task 2, Артем Момоток, ШІ-13, Варіант 4
*/
#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    // Вхідні дані для обчислення у форматі float
    float a_float = 1000;
    float b_float = 0.0001;

    // Допоміжні змінні для формули у float
    float c_float = pow(a_float, 3);        // a^3
    float d_float = pow(b_float, 3);        // b^3
    float ea_float = 3 * a_float * a_float * b_float;   // 3*a^2*b
    float eb_float = 3 * a_float * b_float * b_float;   // 3*a*b^2
    float g_float = a_float + b_float;      // a + b

    // Чисельник і знаменник виразу для float
    float f_numerator = pow(g_float, 3) - c_float;
    float f_denominator = ea_float + pow(b_float, 3) - eb_float;

    // Обчислення результату для float
    float result_float = f_numerator / f_denominator;

    // Вхідні дані для обчислення у форматі double
    double a_double = 1000;
    double b_double = 0.0001;

    // Допоміжні змінні для формули у double
    double c_double = pow(a_double, 3);        // a^3
    double d_double = pow(b_double, 3);        // b^3
    double ea_double = 3 * a_double * a_double * b_double;   // 3*a^2*b
    double eb_double = 3 * a_double * b_double * b_double;   // 3*a*b^2
    double g_double = a_double + b_double;      // a + b

    // Чисельник і знаменник виразу для double
    double d_numerator = pow(g_double, 3) - c_double;
    double d_denominator = ea_double + pow(b_double, 3) - eb_double;

    // Обчислення результату для double
    double result_double = d_numerator / d_denominator;

    // Вивід результатів обчислення для двох типів
    std::cout << "Float result: " << result_float << std::endl;
    std::cout << "Double result: " << result_double << std::endl;

    return 0;
}

