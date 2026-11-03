/*
Задача: Лабораторна робота 1, завдання 2
Автор: Роман Лупій
Група: ШІ-13
Варіант: 2
*/

#include <iostream>

using namespace std;

int main()
{
    // Зчитуємо початкові значення змінних n та m
    int initialN, initialM;

    cout << "Введіть початкові значення n : ";
    cin >> initialN;
    cout << "Введіть початкові значення m : ";
    cin >> initialM;

    int n, m;

    // Перевіряємо префіксний інкремент у виразі ++n * ++m
    n = initialN;
    m = initialM;

    int result1 = ++n * ++m;

    cout << "1) ++n * ++m = " << result1
         << "; n = " << n << ", m = " << m << '\n';

    // Повертаємо початкові значення перед наступним виразом
    n = initialN;
    m = initialM;

    // Порівнюємо m з n, після чого збільшуємо m на 1
    bool result2 = m++ < n;

    cout << "2) m++ < n = " << boolalpha << result2
         << "; n = " << n << ", m = " << m << '\n';

    // Знову повертаємо початкові значення
    n = initialN;
    m = initialM;

    // Порівнюємо n з m, після чого збільшуємо n на 1
    bool result3 = n++ > m;

    cout << "3) n++ > m = " << result3
         << "; n = " << n << ", m = " << m << '\n';

    return 0;
}