
/*
Lab 1 task 1, Олексій Рубакха, ШІ-13, Варіант 11
*/

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{

    /*
    Приклад: Обчислити значення виразу:
     (a - b)^4 - (a^4 - 4 * a^3 * b) / (6 * a^2 * b^2 - 4 * a * b^3 + b^4)
    де a = 100, b = 0.001
    */

    // Оголошення константних значень
    const double a = 100.0;
    const double b = 0.001;

    // Обчислення (a - b)^4
    double ab = a - b;
    double ab4 = ab * ab * ab * ab;

    // Обчислення a^4 - 4 * a^3 * b
    double a4 = a * a * a * a;
    double fourA3B = 4.0 * a * a * a * b;

    // Обчислення чисельника
    double numerator = ab4 - (a4 - fourA3B);

    // Обчислення знаменника 6 * a^2 * b^2 - 4 * a * b^3 + b^4
    double denominator =
        6.0 * a * a * b * b
        - 4.0 * a * b * b * b
        + b * b * b * b;

    // Обчислення результату
    double result = numerator / denominator;

    // Виведення результату
    cout << fixed << setprecision(10);
    cout << "Результат: " << result << endl;

    return 0;
}