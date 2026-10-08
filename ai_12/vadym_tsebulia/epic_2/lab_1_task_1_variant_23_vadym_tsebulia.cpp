/*
Лабораторна робота №1, Завдання №1, Варіант №23.
Цебуля Вадим
ШІ-12
*/

#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main(){
        // Обчислення з точністю float
        float a_float = 1000.0f;
        float b_float = 0.0001f;

        // Чисельник: (a + b)^3 - (a^3 + 3a^2*b)
        float sum_float = a_float + b_float;
        float sum_cube_float = pow(sum_float, 3);
        float a_cube_float = pow(a_float, 3);
        float three_a2b_float = 3 * pow(a_float, 2) * b_float;
        float bracket_float = a_cube_float + three_a2b_float;
        float numerator_float = sum_cube_float - bracket_float;

        // Знаменник: 3a*b^2 + b^3
        float three_ab2_float = 3 * a_float * pow(b_float, 2);
        float b_cube_float = pow(b_float, 3);
        float denominator_float = three_ab2_float + b_cube_float;

        // Фінальний результат float
        float result_float = numerator_float / denominator_float;

        // Обчислення з точністю double
        double a_double = 1000.0;
        double b_double = 0.0001;

        // Чисельник: (a + b)^3 - (a^3 + 3a^2*b)
        double sum_double = a_double + b_double;
        double sum_cube_double = pow(sum_double, 3);
        double a_cube_double = pow(a_double, 3);
        double three_a2b_double = 3 * pow(a_double, 2) * b_double;
        double bracket_double = a_cube_double + three_a2b_double;
        double numerator_double = sum_cube_double - bracket_double;

        // Знаменник: 3a*b^2 + b^3
        double three_ab2_double = 3 * a_double * pow(b_double, 2);
        double b_cube_double = pow(b_double, 3);
        double denominator_double = three_ab2_double + b_cube_double;

        // Фінальний результат double 
        double result_double = numerator_double / denominator_double;

        // Вивід результатів із точністю 12 знаків після коми
        cout << fixed << setprecision(12);
        cout << "Результат для float: " << result_float << endl;
        cout << "Результат для double: " << result_double << endl;

        return 0;
}