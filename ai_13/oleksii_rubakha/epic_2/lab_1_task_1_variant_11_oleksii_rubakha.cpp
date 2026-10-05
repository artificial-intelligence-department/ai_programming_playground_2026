
/*
Lab 1 task 1, Олексій Рубакха, ШІ-13, Варіант 11
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
    /*
    Приклад: Обчислити значення виразу:
     (a - b)^4 - (a^4 - 4 * a^3 * b)
     ---------------------------------
     6 * a^2 * b^2 - 4 * a * b^3 + b^4

    де a = 100, b = 0.001
    */

    // Варіант з float

    // Оголошення константних значень
    const float f_a = 100.0;
    const float f_b = 0.001;

    // Обчислення (a - b)^4
    float f_ab = f_a - f_b;
    float f_ab4 = pow(f_ab, 4);

    // Обчислення a^4 - 4 * a^3 * b
    float f_a4 = pow(f_a, 4);
    float f_fourA3B = 4.0 * pow(f_a, 3) * f_b;

    // Обчислення чисельника
    float f_numerator = f_ab4 - (f_a4 - f_fourA3B);

    // Обчислення знаменника
    // 6 * a^2 * b^2 - 4 * a * b^3 + b^4
    float f_denominator =
        6.0 * pow(f_a, 2) * pow(f_b, 2)
        - 4.0 * f_a * pow(f_b, 3)
        + pow(f_b, 4);

    // Обчислення результату
    float f_result = f_numerator / f_denominator;

    // Виведення результату
    cout << fixed << setprecision(10);
    cout << "Результат float: " << f_result << endl;


    // Варіант з double

    // Оголошення константних значень
    const double d_a = 100.0;
    const double d_b = 0.001;

    // Обчислення (a - b)^4
    double d_ab = d_a - d_b;
    double d_ab4 = pow(d_ab, 4);

    // Обчислення a^4 - 4 * a^3 * b
    double d_a4 = pow(d_a, 4);
    double d_fourA3B = 4.0 * pow(d_a, 3) * d_b;

    // Обчислення чисельника
    double d_numerator = d_ab4 - (d_a4 - d_fourA3B);

    // Обчислення знаменника
    // 6 * a^2 * b^2 - 4 * a * b^3 + b^4
    double d_denominator =
        6.0 * pow(d_a, 2) * pow(d_b, 2)
        - 4.0 * d_a * pow(d_b, 3)
        + pow(d_b, 4);

    // Обчислення результату
    double d_result = d_numerator / d_denominator;

    // Виведення результату
    cout << fixed << setprecision(10);
    cout << "Результат double: " << d_result << endl;

    return 0;
}