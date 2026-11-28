/*
 * Задача: Algotester Lab 1v1
 * Автор: Михалевич Олег Миколайович
 * Група: ШІ-11
 */

#include <iostream>

int main() {
    // Використовуємо 64-бітний тип long long, оскільки вхідні значення сягають 10^12
    long long H = 0, M = 0;
    if (!(std::cin >> H >> M)) {
        return 0;
    }

    long long h1 = 0, m1 = 0;
    long long h2 = 0, m2 = 0;
    long long h3 = 0, m3 = 0;

    std::cin >> h1 >> m1;
    std::cin >> h2 >> m2;
    std::cin >> h3 >> m3;

    // Перевіряємо, чи жодне закляття не витрачає хітпойнти та ману одночасно
    bool bothUsed = (h1 > 0 && m1 > 0) || (h2 > 0 && m2 > 0) || (h3 > 0 && m3 > 0);

    // Обчислюємо залишок хітпойнтів та мани після трьох заклять
    H = H - h1 - h2 - h3;
    M = M - m1 - m2 - m3;

    // Персонаж виграє, якщо не порушено правило касту і обидва показники строго більші за 0
    if (!bothUsed && H > 0 && M > 0) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
