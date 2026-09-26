#include <iostream>
#include <cmath>
using namespace std;
/* Задача 1 лаб 1 варіант 1
   Сідлецький Тимофій ШІ-13*/

int main () {
    // Оголошення змінних та запит їх у користувача
    double a, b, c, d, e, f, g;
    cout << "Введіть значення a: ";
    cin >> a;
    cout << "Введіть значення b: ";
    cin >> b;

    float a1 = a;
    float b1 = b;
    float c1 = c;
    float d1, e1, f1, g1;

    // Обчислення значень виразу для double
    d = pow ((a+b), 2);
    e = pow (a, 2) + 2*a*b;
    f = d - e;
    g = f / pow (b, 2);

    // Обчислення значень виразу для float
    d1 = pow ((a1+b1), 2);
    e1 = pow (a1, 2) + 2*a1*b1;
    f1 = d1 - e1;
    g1 = f1 / pow (b1, 2);

    cout << "Результат обчислення для float: " << g1 << "\n";
    cout << "Результат обчислення для double: " << g;
}