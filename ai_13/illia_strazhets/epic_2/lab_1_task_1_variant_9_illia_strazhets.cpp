/*
 * Лабораторна робота №1
 * Задача: 1, варіант: 9
 * Автор: Illia Strazhets
 * Група: AI-13
 */
#include <iostream>
#include <cmath>
using namespace std;

// Функція для обчислення виразу з використанням типу даних float
int float_calc()
{
    // Визначення констант a та b, як вказано в умові задачі
    const float a = 100;
    const float b = 0.001;
    float c = 0;

    // Обчислення виразу з використанням типу даних float
    c = (pow(a + b, 4) - (pow(a, 4) + 4 * pow(a, 3) * b)) / (6 * pow(a, 2) * pow(b, 2) + 4 * a * pow(b, 3) + pow(b, 4));
    cout << "Результат обчислення, за використання типу даних float: " << c << endl;
    return 0;
}

// Функція для обчислення виразу з використанням типу даних double
int double_calc()
{
    // Визначення констант a та b, як вказано в умові задачі
    const double a = 100;
    const double b = 0.001;
    double c = 0;
    c = (pow(a + b, 4) - (pow(a, 4) + 4 * pow(a, 3) * b)) / (6 * pow(a, 2) * pow(b, 2) + 4 * a * pow(b, 3) + pow(b, 4));
    cout << "Результат обчислення, за використання типу даних double: " << c << endl;
    return 0;
}

int main()
{
    float_calc();
    double_calc();
    return 0;
}