#include <iostream>
using namespace std;

int main() {
    // Змінні
    int password_length;
    char has_digits, has_uppercase, has_special_symbols;
    bool meets_minimum_requirements = false;
    int character_type_count = 0;
    int security_level = 0;

    // Введення
    cout << "Довжина пароля (1-64): ";
    if (!(cin >> password_length) || password_length < 1 || password_length > 64) {
        cout << "Помилка: введіть ціле число від 1 до 64.\n";
        return 1;
    }

    cout << "Чи є цифри (y/n): ";
    if (!(cin >> has_digits) || (has_digits != 'y' && has_digits != 'n')) {
        cout << "Помилка: введіть лише y або n.\n";
        return 1;
    } else if (has_digits == 'y') {
        character_type_count++;
    }

    cout << "Чи є великі літери (y/n): ";
    if (!(cin >> has_uppercase) || (has_uppercase != 'y' && has_uppercase != 'n')) {
        cout << "Помилка: введіть лише y або n.\n";
        return 1;
    } else if (has_uppercase == 'y') {
        character_type_count++;
    }

    cout << "Чи є спеціальні символи (y/n): ";
    if (!(cin >> has_special_symbols) ||
        (has_special_symbols != 'y' && has_special_symbols != 'n')) {
        cout << "Помилка: введіть лише y або n.\n";
        return 1;
    } else if (has_special_symbols == 'y') {
        character_type_count++;
    }

    // Мінімальні вимоги
    if (password_length >= 8 && character_type_count >= 2) {
        meets_minimum_requirements = true;
    } else {
        meets_minimum_requirements = false;
    }

    // Рівень надійності
    if (password_length < 6) {
        security_level = 1;
    } else if (password_length < 8 || character_type_count == 0) {
        security_level = 2;
    } else if (character_type_count == 1) {
        security_level = 3;
    } else if (password_length >= 12 && character_type_count == 3) {
        security_level = 5;
    } else {
        security_level = 4;
    }

    // Вивід
    cout << "\nМінімальні вимоги: ";
    if (meets_minimum_requirements) {
        cout << "ПРОЙДЕНО\n";
    } else {
        cout << "НЕ ПРОЙДЕНО\n";
    }

    cout << "Рівень надійності: " << security_level << " - ";

    switch (security_level) {
        case 1:
            cout << "Дуже слабкий\n";
            cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів.\n";
            break;
        case 2:
            cout << "Слабкий\n";
            cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.\n";
            break;
        case 3:
            cout << "Середній\n";
            cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12.\n";
            break;
        case 4:
            cout << "Надійний\n";
            cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів.\n";
            break;
        case 5:
            cout << "Дуже надійний\n";
            cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно.\n";
            break;
        default:
            cout << "Невідомий рівень\n";
            cout << "Помилка: рівень має бути від 1 до 5.\n";
            break;
    }

    // Попередження
    if (!(has_digits == 'y' || has_special_symbols == 'y')) {
        cout << "Попередження: пароль тільки з літер підбирається швидше.\n";
    }

    return 0;
}
