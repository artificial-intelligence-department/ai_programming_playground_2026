/*
 * Практична робота: Аналізатор надійності пароля
 * Ткач Артем
 * ШІ-13
 *
 * Програма не зчитує сам пароль, а лише його характеристики:
 * довжину та наявність цифр / великих літер / спеціальних символів.
 * За цими даними визначається, чи пройдено мінімальні вимоги (if/else),
 * рівень надійності від 1 до 5 (if/else if) та рекомендація (switch/case).
 *
 * Сторонні бібліотеки заборонені: використовується лише <iostream>.
 * Циклів немає: при некоректному вводі одразу виводиться помилка
 * і програма завершується.
 */

#include <iostream>

int main() {
    int length;
    char hasDigits, hasUpper, hasSpecial;

    // --- Зчитування вхідних даних ---
    std::cout << "Довжина пароля: ";
    if (!(std::cin >> length) || length < 1 || length > 64) {
        std::cout << "Помилка: довжина мусить бути від 1 до 64.\n";
        return 1;
    }

    std::cout << "Чи є цифри (y/n): ";
    // "!" (NOT) разом з "||" (OR): якщо символ НЕ 'y' і НЕ 'n' - помилка.
    if (!(std::cin >> hasDigits) || !(hasDigits == 'y' || hasDigits == 'n')) {
        std::cout << "Помилка: відповідь має бути y або n.\n";
        return 1;
    }

    std::cout << "Чи є великі літери (y/n): ";
    if (!(std::cin >> hasUpper) || !(hasUpper == 'y' || hasUpper == 'n')) {
        std::cout << "Помилка: відповідь має бути y або n.\n";
        return 1;
    }

    std::cout << "Чи є спеціальні символи (y/n): ";
    if (!(std::cin >> hasSpecial) || !(hasSpecial == 'y' || hasSpecial == 'n')) {
        std::cout << "Помилка: відповідь має бути y або n.\n";
        return 1;
    }

    // Кількість типів символів, присутніх у паролі (0..3)
    int charTypesCount = 0;
    if (hasDigits == 'y') charTypesCount++;
    if (hasUpper == 'y') charTypesCount++;
    if (hasSpecial == 'y') charTypesCount++;

    // --- Крок 1: мінімальні вимоги (if / else) ---
    // "&&" (AND): довжина не менше 8 І кількість типів символів не менше 2.
    bool passesMinimum;
    if (length >= 8 && charTypesCount >= 2) {
        passesMinimum = true;
    } else {
        passesMinimum = false;
    }

    // --- Крок 2: рівень надійності (if / else if) ---
    // Правила перевіряються послідовно згори вниз, перше спрацьоване визначає рівень.
    int level;
    if (length < 6) {
        level = 1;
    } else if (length < 8 || charTypesCount == 0) {
        level = 2;
    } else if (charTypesCount == 1) {
        level = 3;
    } else if (length >= 12 && charTypesCount == 3) {
        level = 5;
    } else {
        level = 4;
    }

    // --- Вивід результатів ---
    std::cout << "\n";
    std::cout << "Мінімальні вимоги: " << (passesMinimum ? "ПРОЙДЕНО" : "НЕ ПРОЙДЕНО") << "\n";
    std::cout << "Рівень надійності: " << level;

    // --- Крок 3: назва рівня і рекомендація (switch / case) ---
    // switch працює лише з цілочисельним типом - рівень якраз int.
    // Кожна гілка завершується break; гілка default присутня.
    switch (level) {
        case 1:
            std::cout << " - Дуже слабкий\n";
            std::cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів.\n";
            break;
        case 2:
            std::cout << " - Слабкий\n";
            std::cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.\n";
            break;
        case 3:
            std::cout << " - Середній\n";
            std::cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12.\n";
            break;
        case 4:
            std::cout << " - Надійний\n";
            std::cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів.\n";
            break;
        case 5:
            std::cout << " - Дуже надійний\n";
            std::cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно.\n";
            break;
        default:
            std::cout << " - Невідомий рівень\n";
            std::cout << "Рекомендація: Невідомий рівень надійності.\n";
            break;
    }

    return 0;
}
