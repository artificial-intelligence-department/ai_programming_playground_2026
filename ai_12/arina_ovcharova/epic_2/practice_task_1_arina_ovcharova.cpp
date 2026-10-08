#include <iostream>

using namespace std;

int main()
{
    int length;
    char digits;
    char uppercase;
    char special;

    // Введення та перевірка довжини пароля
    cout << "Довжина пароля: ";
    if (!(cin >> length) || length < 1 || length > 64)
    {
        cout << "Помилка: введено недійсне значення." << endl;
        return 0;
    }

    // Введення та перевірка наявності цифр
    cout << "Чи є цифри (y/n): ";
    cin >> digits;

    if (digits != 'y' && digits != 'n')
    {
        cout << "Помилка: введено недійсне значення." << endl;
        return 0;
    }

    // Введення та перевірка наявності великих літер
    cout << "Чи є великі літери (y/n): ";
    cin >> uppercase;

    if (uppercase != 'y' && uppercase != 'n')
    {
        cout << "Помилка: введено недійсне значення." << endl;
        return 0;
    }

    // Введення та перевірка спеціальних символів
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> special;

    if (special != 'y' && special != 'n')
    {
        cout << "Помилка: введено недійсне значення." << endl;
        return 0;
    }

    // Визначення кількості типів символів
    int types = 0;

    if (digits == 'y')
        types++;

    if (uppercase == 'y')
        types++;

    if (special == 'y')
        types++;

    // Перевірка мінімальних вимог
    if (length >= 8 && types >= 2)
    {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    }
    else
    {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }

    // Визначення рівня надійності
    int level;

    if (length < 6)
    {
        level = 1;
    }
    else if (length < 8 || types == 0)
    {
        level = 2;
    }
    else if (types == 1)
    {
        level = 3;
    }
    else if (length >= 12 && types == 3)
    {
        level = 5;
    }
    else
    {
        level = 4;
    }

    // Виведення рівня
    cout << "Рівень надійності: " << level;

    if (level == 1)
        cout << " - Дуже слабкий" << endl;
    else if (level == 2)
        cout << " - Слабкий" << endl;
    else if (level == 3)
        cout << " - Середній" << endl;
    else if (level == 4)
        cout << " - Надійний" << endl;
    else
        cout << " - Дуже надійний" << endl;

    // Виведення рекомендації
    cout << "Рекомендація: ";

    switch (level)
    {
        case 1:
            cout << "Пароль надто короткий. Мінімум 8 символів.";
            break;

        case 2:
            cout << "Збільште довжину до 8+ символів і додайте цифри, "
                    "великі літери або спеціальні символи.";
            break;

        case 3:
            cout << "Додайте ще один тип символів або збільште довжину до 12.";
            break;

        case 4:
            cout << "Хороший пароль. Для максимуму 12+ символів і всі три типи символів.";
            break;

        case 5:
            cout << "Відмінно. Змінювати нічого не потрібно.";
            break;
    }

    cout << endl;

    // Попередження для паролів тільки з літер
    if (digits == 'n' && special == 'n')
    {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}