/*
Лабораторна робота №1, Завдання №1, Варіант №23.
Онишко Даніель
ШІ-14
*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    // розрахунки для типу float 4
    float a_float = 1000.0f;
    float b_float = 0.0001f;

    // Рахую чисельник за частинами
    float sum_float = a_float + b_float;                  // a + b
    float sum_cube_float = pow(sum_float, 3);             // підношу (a + b) до куба
    float a_cube_float = pow(a_float, 3);                 // підношу a до куба
    float three_a2b_float = 3 * pow(a_float, 2) * b_float; //  3 * a^2 * b
    float bracket_float = a_cube_float + three_a2b_float; // додаю це все в дужках
    float numerator_float = sum_cube_float - bracket_float; // віднімаю від куба суми те, що в дужках

    // Те ж саме роблю для знаменника (теж розбиваю на дії)
    float three_ab2_float = 3 * a_float * pow(b_float, 2); //3 * a * b^2
    float b_cube_float = pow(b_float, 3);                 // підношу b до куба
    float denominator_float = three_ab2_float + b_cube_float; // додаю їх для знаменника

    // Ділю чисельник на знаменник і отримую фінальний результат для float
    float result_float = numerator_float / denominator_float;


    // Тепер роблю все те саме, але для типу double8
    double a_double = 1000.0;
    double b_double = 0.0001;

    // Рахую чисельник для double
    double sum_double = a_double + b_double;
    double sum_cube_double = pow(sum_double, 3);
    double a_cube_double = pow(a_double, 3);
    double three_a2b_double = 3 * pow(a_double, 2) * b_double;
    double bracket_double = a_cube_double + three_a2b_double;
    double numerator_double = sum_cube_double - bracket_double;

    // Рахую знаменник для double
    double three_ab2_double = 3 * a_double * pow(b_double, 2);
    double b_cube_double = pow(b_double, 3);
    double denominator_double = three_ab2_double + b_cube_double;

    // Фінальний результат для double
    double result_double = numerator_double / denominator_double;


    cout << "Результат для float:  " << result_float << endl;
    cout << "Результат для double: " << result_double <<     endl;

    return 0;
}