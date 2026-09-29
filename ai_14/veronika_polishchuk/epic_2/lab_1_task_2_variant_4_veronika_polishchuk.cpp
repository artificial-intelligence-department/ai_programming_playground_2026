/* Задача: Лабораторна робота, завдання 2
* Поліщук Вероніка
* Група 14
*/

#include <iostream>

using namespace std;

int main() {
    int n, m;

    cout << "Завдання 2 (Варіант 4)" << endl;

    // 1) Вираз: n++ * m
    n = 5; m = 3;
    cout << "1) Початкові значення: n = " << n << ", m = " << m << endl;
    int res1 = n++ * m;
    cout << "   Вираз: n++ * m" << endl;
    cout << "   Результат виразу: " << res1 << endl;
    cout << "   Значення змінних після: n = " << n << ", m = " << m << endl;

    // 2) Вираз: n++ < m
    n = 5; m = 3;
    cout << "2) Початкові значення: n = " << n << ", m = " << m << endl;
    bool res2 = n++ < m;
    cout << "   Вираз: n++ < m" << endl;
    cout << "   Результат виразу (bool): " << boolalpha << res2 << endl;
    cout << "   Значення змінних після: n = " << n << ", m = " << m << endl;

    // 3) Вираз: m-- > m
    n = 5; m = 3;
    cout << "3) Початкові значення: n = " << n << ", m = " << m << endl;
    bool res3 = m-- > m;
    cout << "   Вираз: m-- > m" << endl;
    cout << "   Результат виразу (bool): " << boolalpha << res3 << endl;
    cout << "   Значення змінних після: n = " << n << ", m = " << m << endl;

    return 0;
}