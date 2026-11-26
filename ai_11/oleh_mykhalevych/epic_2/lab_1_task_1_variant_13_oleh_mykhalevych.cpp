/*
 * Лабораторна робота №1, Завдання 1, Варіант 13
 * Автор: Михалевич Олег Миколайович
 * Група: ШІ-11
 */

#include <iostream>
#include <cmath>

int main() {
    // 1. Обчислення з використанням типу float (32 біти, ~7 значущих цифр)
    float a_f = 1000.0f;
    float b_f = 0.0001f;

    float c_f = std::pow(a_f - b_f, 2);      // Проміжна змінна: (a - b)^2
    float d_f = std::pow(a_f, 2);            // Проміжна змінна: a^2
    float e_f = 2.0f * a_f * b_f;            // Проміжна змінна: 2ab
    float f_f = d_f - e_f;                   // Проміжна змінна: a^2 - 2ab
    float num_f = c_f - f_f;                 // Чисельник
    float den_f = std::pow(b_f, 2);          // Знаменник: b^2
    float res_f = num_f / den_f;             // Підсумковий результат для float

    // 2. Обчислення з використанням типу double (64 біти, ~15 значущих цифр)
    double a_d = 1000.0;
    double b_d = 0.0001;

    double c_d = std::pow(a_d - b_d, 2);     // Проміжна змінна: (a - b)^2
    double d_d = std::pow(a_d, 2);           // Проміжна змінна: a^2
    double e_d = 2.0 * a_d * b_d;            // Проміжна змінна: 2ab
    double f_d = d_d - e_d;                  // Проміжна змінна: a^2 - 2ab
    double num_d = c_d - f_d;                // Чисельник
    double den_d = std::pow(b_d, 2);         // Знаменник: b^2
    double res_d = num_d / den_d;            // Підсумковий результат для double

    std::cout << "--- Результати для float ---\n";
    std::cout << "Чисельник: " << num_f << "\n";
    std::cout << "Знаменник: " << den_f << "\n";
    std::cout << "Результат (float):  " << res_f << "\n\n";

    std::cout << "--- Результати для double ---\n";
    std::cout << "Чисельник: " << num_d << "\n";
    std::cout << "Знаменник: " << den_d << "\n";
    std::cout << "Результат (double): " << res_d << "\n";

    return 0;
}
