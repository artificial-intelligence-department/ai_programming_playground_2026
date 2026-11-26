/*
 * Задача: Аналізатор надійності пароля
 * Автор: Михалевич Олег Миколайович
 * Група: ШІ-11
 */

#include <iostream>

int main() {
    // Константи меж довжини та вимог за умовою задачі
    const int MIN_VALID_LEN = 1;    // Мінімально допустима довжина пароля при вводі
    const int MAX_VALID_LEN = 64;   // Максимально допустима довжина пароля при вводі
    const int VERY_WEAK_LIM = 6;    // Межа довжини для дуже слабкого пароля
    const int MIN_REQ_LEN = 8;      // Мінімальна довжина для проходження базових вимог
    const int STRONG_LEN = 12;      // Довжина для дуже надійного пароля
    const int MIN_REQ_TYPES = 2;    // Мінімальна кількість типів символів для базових вимог
    const int MAX_TYPES = 3;        // Максимальна кількість додаткових типів символів

    int length = 0;
    char hasDigits = ' ';
    char hasUpper = ' ';
    char hasSpec = ' ';

    std::cout << "Довжина пароля: ";
    if (!(std::cin >> length) || length < MIN_VALID_LEN || length > MAX_VALID_LEN) {
        std::cout << "Помилка: довжина мусить бути від 1 до 64." << std::endl;
        return 1;
    }

    std::cout << "Чи є цифри (y/n): ";
    std::cin >> hasDigits;
    if (!(hasDigits == 'y' || hasDigits == 'n')) {
        std::cout << "Помилка: введіть дійсне значення (y або n)." << std::endl;
        return 1;
    }

    std::cout << "Чи є великі літери (y/n): ";
    std::cin >> hasUpper;
    if (!(hasUpper == 'y' || hasUpper == 'n')) {
        std::cout << "Помилка: введіть дійсне значення (y або n)." << std::endl;
        return 1;
    }

    std::cout << "Чи є спеціальні символи (y/n): ";
    std::cin >> hasSpec;
    if (!(hasSpec == 'y' || hasSpec == 'n')) {
        std::cout << "Помилка: введіть дійсне значення (y або n)." << std::endl;
        return 1;
    }

    // Обчислюємо кількість присутніх типів символів (від 0 до 3)
    int typesCount = 0;
    if (hasDigits == 'y') {
        typesCount = typesCount + 1;
    }
    if (hasUpper == 'y') {
        typesCount = typesCount + 1;
    }
    if (hasSpec == 'y') {
        typesCount = typesCount + 1;
    }

    std::cout << "\n";

    // Крок 1: Перевірка мінімальних вимог за допомогою if / else та оператора AND (&&)
    if (length >= MIN_REQ_LEN && typesCount >= MIN_REQ_TYPES) {
        std::cout << "Мінімальні вимоги: ПРОЙДЕНО" << std::endl;
    } else {
        std::cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << std::endl;
    }

    // Крок 2: Визначення рівня надійності (від 1 до 5) через драбинку if / else if
    int level = 0;
    if (length < VERY_WEAK_LIM) {
        level = 1;
        std::cout << "Рівень надійності: 1 - Дуже слабкий" << std::endl;
    } else if (length < MIN_REQ_LEN || typesCount == 0) {
        level = 2;
        std::cout << "Рівень надійності: 2 - Слабкий" << std::endl;
    } else if (typesCount == 1) {
        level = 3;
        std::cout << "Рівень надійності: 3 - Середній" << std::endl;
    } else if (length >= STRONG_LEN && typesCount == MAX_TYPES) {
        level = 5;
        std::cout << "Рівень надійності: 5 - Дуже надійний" << std::endl;
    } else {
        level = 4;
        std::cout << "Рівень надійності: 4 - Надійний" << std::endl;
    }

    // Крок 3: Вибір рекомендації відповідно до рівня через switch / case
    switch (level) {
        case 1:
            std::cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << std::endl;
            break;
        case 2:
            std::cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << std::endl;
            break;
        case 3:
            std::cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << std::endl;
            break;
        case 4:
            std::cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << std::endl;
            break;
        default:
            std::cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << std::endl;
            break;
    }

    // Попередження, якщо в паролі немає ні цифр, ні спецсимволів (тільки літери)
    if (hasDigits == 'n' && hasSpec == 'n') {
        std::cout << "Попередження: пароль тільки з літер підбирається швидше." << std::endl;
    }

    return 0;
}
