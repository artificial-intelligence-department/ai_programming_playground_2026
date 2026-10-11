/* 
Lab 1 task 1, Мадяр Андрій, ШІ-13, варіант 16
*/
#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    /*  приклад: Обчислити значення виразу:
((a-b)^3 - (a^3 - 3*a^2*b)) / (b^3 - 3*a*b^2)
де a=1000, b=0.0001
 */

// варіант з використанням float
    // оголошую константи
    const float f_a=1000.0 , f_b=0.0001;
    // обчислення значення виразу
    float f_op1 = f_a - f_b;
    float f_op2 = f_op1 * f_op1 * f_op1;
    float f_op3 = f_a * f_a * f_a;
    float f_op4 = 3.0 * f_a * f_a * f_b;
    float f_op5 = f_op3 - f_op4;
    float f_op6 = f_b * f_b * f_b;
    float f_op7 = 3.0 * f_a * f_b * f_b;
    float f_op8 = f_op6 - f_op7;
    float f_op9 = f_op2 - f_op5;
    float f_op10 = f_op9 / f_op8;
    // виведення результату
    cout << "float: " << fixed << setprecision(10) << f_op10 << endl;

// варіант з використанням double
    // оголошую константи
    const double d_a=1000.0 , d_b=0.0001;
    // обчислення значення виразу
    double d_op1 = d_a - d_b;
    double d_op2 = d_op1 * d_op1 * d_op1;
    double d_op3 = d_a * d_a * d_a;
    double d_op4 = 3.0 * d_a * d_a * d_b;
    double d_op5 = d_op3 - d_op4;
    double d_op6 = d_b * d_b * d_b;
    double d_op7 = 3.0 * d_a * d_b * d_b;
    double d_op8 = d_op6 - d_op7;
    double d_op9 = d_op2 - d_op5;
    double d_op10 = d_op9 / d_op8;
    // виведення результату
    cout << "double: " << fixed << setprecision(10) << d_op10 << endl;
    return 0;
}