/*
 * Лабораторна робота №1, Завдання 1, варіант 6
 * Обчислення значення виразу при різних дійсних типах даних (float і double)
 * Ткач Артем
 * ШІ-13
 *
 * Вираз:  ((a - b)^3 - (a^3 - 3*a^2*b)) / (b^3 - 3*a^2*b)
 * При a = 1000, b = 0.0001
 *
 * Обчислення виконується з використанням проміжних змінних, як
 * рекомендовано в методичних вказівках лабораторної роботи:
 *   c = a^3
 *   d = 3*a^2*b
 *   e = 3*a*b^2
 *   f = b^3
 * Тоді чисельник = e - f, знаменник = f - d.
 *
 * Обчислення повторюється двічі - окремо для float і окремо для double,
 * щоб порівняти точність результату.
 */

#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    std::cout << std::fixed << std::setprecision(15);

    // --- Обчислення для типу float ---
    float aFloat = 1000;
    float bFloat = 0.0001f;

    float cFloat = std::pow(aFloat, 3);          // a^3
    float dFloat = 3 * aFloat * aFloat * bFloat;  // 3*a^2*b
    float eFloat = 3 * aFloat * bFloat * bFloat;  // 3*a*b^2
    float fFloat = std::pow(bFloat, 3);           // b^3

    float numeratorFloat = eFloat - fFloat;       // (a-b)^3 - (a^3-3a^2b) спрощується до e - f
    float denominatorFloat = fFloat - dFloat;     // b^3 - 3*a^2*b
    float resultFloat = numeratorFloat / denominatorFloat;

    std::cout << "--- Тип float ---\n";
    std::cout << "c = a^3         = " << cFloat << "\n";
    std::cout << "d = 3*a^2*b     = " << dFloat << "\n";
    std::cout << "e = 3*a*b^2     = " << eFloat << "\n";
    std::cout << "f = b^3         = " << fFloat << "\n";
    std::cout << "Чисельник (e-f) = " << numeratorFloat << "\n";
    std::cout << "Знаменник (f-d) = " << denominatorFloat << "\n";
    std::cout << "Результат       = " << resultFloat << "\n\n";

    // --- Обчислення для типу double ---
    double aDouble = 1000;
    double bDouble = 0.0001;

    double cDouble = std::pow(aDouble, 3);           // a^3
    double dDouble = 3 * aDouble * aDouble * bDouble; // 3*a^2*b
    double eDouble = 3 * aDouble * bDouble * bDouble; // 3*a*b^2
    double fDouble = std::pow(bDouble, 3);            // b^3

    double numeratorDouble = eDouble - fDouble;       // e - f
    double denominatorDouble = fDouble - dDouble;     // f - d
    double resultDouble = numeratorDouble / denominatorDouble;

    std::cout << "--- Тип double ---\n";
    std::cout << "c = a^3         = " << cDouble << "\n";
    std::cout << "d = 3*a^2*b     = " << dDouble << "\n";
    std::cout << "e = 3*a*b^2     = " << eDouble << "\n";
    std::cout << "f = b^3         = " << fDouble << "\n";
    std::cout << "Чисельник (e-f) = " << numeratorDouble << "\n";
    std::cout << "Знаменник (f-d) = " << denominatorDouble << "\n";
    std::cout << "Результат       = " << resultDouble << "\n";

    return 0;
}
