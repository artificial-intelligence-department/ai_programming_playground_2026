/*
    Лабораторна робота №2 Завдання 1 Варіант 3
    Прізвище: Палєй
    Група: ШІ-14
*/

#include <iostream>

int main()
{
    const int DVISTI = 200;
    int sum = 0;

    for (int n = 1; n < DVISTI; n++)
    {
        if (n%2 != 0)
            sum += n;
    }

    std::cout << "Сума цілих додатних непарних чисел менших за 200 дорівнює: " << sum << std::endl;

    return 0;
}