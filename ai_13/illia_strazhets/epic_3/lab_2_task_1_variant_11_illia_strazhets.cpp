/*
 * Лабораторна робота №2
 * Задача: 1, варіант: 11
 * Автор: Illia Strazhets
 * Група: AI-13
 */
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    const long double epsilon = 0.0001; // Епсилон-точність задана в умові задачі
    long double a_n = 1.0;              // Перший член ряду: a_1 = 1
    long double sum = 0.0;
    int n = 1; // Починаємо з першого члена

    while (true)
    {
        sum += a_n;

        if (a_n < epsilon) // Якщо член менший за ε, завершуємо цикл
            break;

        // a_(n+1) = a_n * (n / (n + 1))^n
        a_n *= pow((long double)(n) / (n + 1), n); // Рекурентна формула, визначена з основної формули підстановкою n+1, замість n
        ++n;
    }

    cout << sum; // Вивід суми ряду
    return 0;
}