// Lab 1, task 1, Дрогомирецька Ольга, варіант 1
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
    /* 
    Обчислити значення виразу:((a + b)^2 - (a^2 + 2*a*b)) / b^2, 
    якщо a = 1000, b = 0.0001.
    Порівняти результати обчислень для типів float і double.
    Порядок дій:
    c_f = (a + b)^2
    d_f = a^2 + 2*a*b
    e_f = c_f - d_f
    f_f = b^2
    result_f = e_f / f_f
    Обчислити вираз для double тими самими діями.
    */
    double a_d, b_d;

    cout << "Enter a: ";
    cin >> a_d;
    cout << "Enter b: ";
    cin >> b_d;

    float a_f = a_d;
    float b_f = b_d;
    float c_f = pow(a_f + b_f, 2);
    float d_f = a_f * a_f + 2 * a_f * b_f;
    float e_f = c_f - d_f;
    float f_f = b_f * b_f;
    float result_f = e_f / f_f;

    double c_d = pow(a_d + b_d, 2);
    double d_d = a_d * a_d + 2 * a_d * b_d;
    double e_d = c_d - d_d;
    double f_d = b_d * b_d;
    double result_d = e_d / f_d;

    cout << fixed << setprecision(8);
    cout << "\nResult with float:  " << result_f << endl;
    cout << "Result with double: " << result_d << endl;
    return 0;
}
