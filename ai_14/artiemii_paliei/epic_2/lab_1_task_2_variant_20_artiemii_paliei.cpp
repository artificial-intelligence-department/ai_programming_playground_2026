/*
    Лабораторна робота №1 Завдання 2 Варіант 20
    Прізвище: Палєй
    Група: ШІ-14
*/
#include <iostream>

int main()
{
    int m, n;
    std::cout << "Введіть два числа (m і n): ";
    std::cin >> m >> n;

    // Operation 1: m-++n
    std::cout << "Результат 1-ої операції: " << m - ++n << std::endl;

    // Operation 2: ++m>--n
    std::cout << "Результат 2-ої операції: " << bool(++m > --n) << std::endl;

    // Operation 3: --n<++m
    std::cout << "Результат 3-ої операції: " << bool(--n < ++m) << std::endl;

    return 0;
}