#include <iostream>

int main()
{
    // Ініцілізація змінних

    int password_lenght, security_lvl;               // Змінні довжини і надійності пароля
    bool warning, requirements;                      // Змінні попередження і мінімальних вимог
    bool is_digit, is_uppercase, is_special_symbols; // Змінні наявності цифр, великих літер і спец. сиволів
    is_digit = is_uppercase = is_special_symbols = false;
    char input_letter; // Змінна вводу букви 'y'/'n'

    // Введення довжини пароля
    std::cout << "Довжина паролю: ";
    if (!(std::cin >> password_lenght) || password_lenght <= 0 || password_lenght > 64)
    {
        std::cout << "Помилка: Довжина пароля повинна бути від 1 до 64" << std::endl;
        return 1;
    }

    // Введення наявності цифр у паролі
    std::cout << "Чи є цифри в паролі (введіть 'y' для Yes або 'n' для No): ";
    std::cin >> input_letter;

    if (input_letter == 'y')
        is_digit = true;
    else if (input_letter == 'n')
    {
    }
    else
    {
        std::cout << "Помилка: Введені значення повинні бути або 'y' або 'n'." << std::endl;
        return 1;
    }

    // Введення наявності великих літер у паролі
    std::cout << "Чи є великі літери в паролі (введіть 'y' для Yes або 'n' для No): ";
    std::cin >> input_letter;

    if (input_letter == 'y')
        is_uppercase = true;
    else if (input_letter == 'n')
    {
    }
    else
    {
        std::cout << "Помилка: Введені значення повинні бути або 'y' або 'n'." << std::endl;
        return 1;
    }

    // Введення наявності спеціальних символів у паролі
    std::cout << "Чи є спеціальні символи в паролі (введіть 'y' для Yes або 'n' для No): ";
    std::cin >> input_letter;

    if (input_letter == 'y')
        is_special_symbols = true;
    else if (input_letter == 'n')
    {
    }
    else
    {
        std::cout << "Помилка: Введені значення повинні бути або 'y' або 'n'." << std::endl;
        return 1;
    }

    // Оцінка рівня надійності пароля

    int sum = is_digit + is_special_symbols + is_uppercase; // Сума булевих даних для оцінки складності пароля

    if (password_lenght < 6)
        security_lvl = 1;
    else if (password_lenght < 8 || sum == 0)
        security_lvl = 2;
    else if (sum == 1)
        security_lvl = 3;
    else if (password_lenght >= 12 && sum == 3)
        security_lvl = 5;
    else
        security_lvl = 4;

    // Перевірка на те, чи пароль є суто буквенним
    if (!is_digit && !is_special_symbols)
        warning = true;
    else
        warning = false;

    // Перевірка на мінімальні вимоги
    if (password_lenght >= 8 && sum >= 2)
        requirements = true;
    else
        requirements = false;

    if (requirements)
        std::cout << "\nМінімальні вимоги: ПРОЙДЕНО" << std::endl;
    else
        std::cout << "\nМінімальні вимоги: НЕ ПРОЙДЕНО" << std::endl;

    switch (security_lvl)
    {
    case 1:
        std::cout << "Рівень надійності: 1 – Дуже слабкиий" << std::endl;
        std::cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << std::endl;
        break;
    case 2:
        std::cout << "Рівень надійності: 2 – Слабкиий" << std::endl;
        std::cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << std::endl;
        break;
    case 3:
        std::cout << "Рівень надійності: 3 – Середній" << std::endl;
        std::cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << std::endl;
        break;
    case 5:
        std::cout << "Рівень надійності: 5 – Дуже сильний" << std::endl;
        std::cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << std::endl;
        break;
    default:
        std::cout << "Рівень надійності: 4 – Сильний" << std::endl;
        std::cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << std::endl;
        break;
    }

    if (warning)
        std::cout << "Попередження: пароль тільки з літер підбирається швидше." << std::endl;

    return 0;
}