/* Задача: Лабораторна робота, завдання 2
* Туревич Олександр
* Група ШІ-12
*/

#include <iostream>
using namespace std;

int main() {
    int n, m;

    cout << "Завдання 2 (Варіант 9)" << endl;

    // 1) Вираз: ++n * ++m
    n = 5; m = 3;
    cout << "\n1) Початкові значення: n = " << n << ", m = " << m << endl;
    int res1 = ++n * ++m;
    cout << "   Вираз: ++n * ++m" << endl;
    cout << "   Результат виразу: " << res1 << endl;
    cout << "   Значення змінних після: n = " << n << ", m = " << m << endl;

    // 2) Вираз: m++ < n
    n = 5; m = 3;
    cout << "\n2) Початкові значення: n = " << n << ", m = " << m << endl;
    bool res2 = m++ < n;
    cout << "   Вираз: m++ < n" << endl;
    cout << "   Результат виразу (bool): " << boolalpha << res2 << endl;
    cout << "   Значення змінних після: n = " << n << ", m = " << m << endl;

    // 3) Вираз: n++ > m
    n = 5; m = 3;
    cout << "\n3) Початкові значення: n = " << n << ", m = " << m << endl;
    bool res3 = n++ > m;
    cout << "   Вираз: n++ > m" << endl;
    cout << "   Результат виразу (bool): " << boolalpha << res3 << endl;
    cout << "   Значення змінних після: n = " << n << ", m = " << m << endl;

    return 0;
}