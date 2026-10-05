/*
Задача: Lab 1 task 1 (variant - 12)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    //Задання констант типу float
    const float a_float = 1000.0f;
    const float b_float = 0.0001f;

    //Обчислення виразу зі збереженням проміжних значень (FLOAT)
    float sum_1_float = a_float + b_float;
    float power_float = pow(sum_1_float, 2.0f);
    float squared_a_float = pow(a_float, 2.0f);
    float squared_b_float = pow(b_float, 2.0f);
    float product_float = 2.0f * a_float * b_float;
    float sum_2_float = squared_a_float + product_float;
    float diff_float = power_float - sum_2_float;
    float division_float = diff_float / squared_b_float;

    //Виведення результату (FLOAT)
    cout << "Result (FLOAT): " << division_float;
    
    cout << endl;

    //Задання констант типу double
    const double a_double = 1000;
    const double b_double = 0.0001;

    //Обчислення виразу зі збереженням проміжних значень (DOUBLE)
    double sum_1_double = a_double + b_double;
    double power_double = pow(sum_1_double, 2);
    double squared_a_double = pow(a_double, 2);
    double squared_b_double = pow(b_double, 2);
    double product_double = 2 * a_double * b_double;
    double sum_2_double = squared_a_double + product_double;
    double diff_double = power_double - sum_2_double;
    double division_double = diff_double / squared_b_double;

    //Виведення результату (DOUBLE)
    cout << "Result (DOUBLE): " << division_double;

    return 0;
}
