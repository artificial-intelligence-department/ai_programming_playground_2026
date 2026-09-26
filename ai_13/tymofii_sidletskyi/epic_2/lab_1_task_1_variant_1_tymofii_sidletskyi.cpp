#include <iostream>
#include <cmath>
using namespace std;
/* Задача 1 лаб 1 варіант 1
   Сідлецький Тимофій ШІ-13*/

int main () {
    // Оголошення змінних та запит їх у користувача
    double a, b, c, d, e, f;
    cout << "Введіть значення a: ";
    cin >> a;
    cout << "Введіть значення b: ";
    cin >> b;

    float a1 = a;
    float b1 = b;
    float c1, d1, e1, f1;

    // Обчислення значень виразу для double
    c = pow ((a+b), 2);
    d = pow (a, 2) + 2*a*b;
    e = c - d;
    f = e / pow (b, 2);

    // Обчислення значень виразу для float
    c1 = pow ((a1+b1), 2);
    d1 = pow (a1, 2) + 2*a1*b1;
    e1 = c1 - d1;
    f1 = e1 / pow (b1, 2);

    cout << "Результат обчислення для float: " << f1 << "\n";
    cout << "Результат обчислення для double: " << f;
}