/*
    Лабораторна робота №3 Завдання 1 Варіант 23
    Прізвище: Палєй
    Група: ШІ-14
*/

#include <iostream>
#include <cmath>
#include <stdio.h>

int main()
{
    const double EPSILON = 0.0001;
    const double STEP = (1 - 0.1) / 10;
    double x_n = 0.1;

    printf("▬▬▬▬▬▬▬▬▬▬▬ Таблиця результатів обчисель ▬▬▬▬▬▬▬▬▬▬▬\n");
    for (x_n; x_n <= 1; x_n += STEP)
    {
        long double y = 2 * (cos(x_n) * cos(x_n) - 1);
        long double sum_n = 0;
        long double sum_epsilon = 0;
        long double a_n = -(2 * 2 * x_n * x_n) / 2;
        int i = 1;
        for (i; i <= 15; i++)
        {
            sum_n = sum_n + a_n;
            a_n *= -(2 * 2 * x_n * x_n) / ((2 * i + 1) * (2 * i + 2));
        }

        a_n = -(2 * 2 * x_n * x_n) / 2;
        int j = 1;
        while (a_n * (pow(-1, j)) > EPSILON)
        {
            sum_epsilon += a_n;
            a_n *= -(2 * 2 * x_n * x_n) / ((2 * j + 1) * (2 * j + 2));
            j++;
        }

        printf("X=%.2f\t SN=%Lf\t SE=%Lf\t Y=%Lf\n", x_n, sum_n, sum_epsilon, y);
    }

    return 0;
}