/*
Аналізатор надійності пароля
Нечай ШІ-12
*/

#include <iostream>

using namespace std;

int main() {
    int password_length;
    cout << "Довжина пароля: ";
    cin >> password_length;

    if (cin.fail() || password_length < 1 || password_length > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64" << endl;
        return 1;
    }

    cout << "Чи є цифри: ";
    char is_numbers_exist;
    cin >> is_numbers_exist;

    cout << "Чи є великі літери: ";
    char is_uppercase_exist;
    cin >> is_uppercase_exist;

    cout << "Чи є спеціальні символи: ";
    char is_special_characters_exist;
    cin >> is_special_characters_exist;

    int character_types_count = 0;

    // Підрахунок кількості типів символів
    if (is_numbers_exist == 'y') {
        character_types_count++;
    } else if (is_numbers_exist != 'n') {
        cout << "Помилка вводу" << endl;
        return 1;
    }

    if (is_uppercase_exist == 'y') {
        character_types_count++;
    } else if (is_uppercase_exist != 'n') {
        cout << "Помилка вводу" << endl;
        return 1;
    }
    
    if (is_special_characters_exist == 'y') {
        character_types_count++;
    } else if (is_special_characters_exist != 'n') {
        cout << "Помилка вводу" << endl;
        return 1;
    }

    // Розділяємо ввід та вивід для кращої читабельності
    cout << endl;

    if (password_length >= 8 && character_types_count >= 2) {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    } else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }
    
    int security_level;

    if (password_length < 6) {
        security_level = 1;
        cout << "Рівень надійності: 1 - Дуже слабкий" << endl;

    } else if (password_length < 8 || character_types_count == 0) {
        security_level = 2;
        cout << "Рівень надійності: 2 - Слабкий" << endl;

    } else if (character_types_count == 1) {
        security_level = 3;
        cout << "Рівень надійності: 3 - Середній" << endl;

    } else if (password_length >= 12 && character_types_count == 3) {
        security_level = 5;
        cout << "Рівень надійності: 5 - Дуже надійний" << endl;

    } else {
        security_level = 4;
        cout << "Рівень надійності: 4 - Надійний" << endl;
    }

    switch (security_level) {
        case 1:
            cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << endl;
            break;
        case 2:
            cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
            break;
        case 3:
            cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12" << endl;
            break;
        case 4:
            cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
            break;
        case 5:
            cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << endl;
            break;
    }

    if (is_numbers_exist != 'y') {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}