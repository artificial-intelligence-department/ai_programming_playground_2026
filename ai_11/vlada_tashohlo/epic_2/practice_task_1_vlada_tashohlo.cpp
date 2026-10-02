
/* 
Епік 2. Практичне завдання: Аналізатор надійності пароля
Авторка: Ташогло Влада
Група: ші-11
*/

#include <iostream>

using namespace std;

int main() {
    
    // Змінні для параметрів пароля та підрахунку його характеристик.
    int password_length = 0;
    char has_digits = 'n';
    char has_uppercase = 'n';
    char has_specials = 'n';
    int count = 0;
    int level = 0;

    // Отримання та перевірка довжини пароля.
    cout << "Довжина пароля: ";
    cin >> password_length;

    if (password_length < 1 || password_length > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 1;
    }

    // Перевірка наявності цифр у паролі.
    cout << "Чи є цифри (y/n): ";
    cin >> has_digits;

    if (has_digits != 'y' && has_digits != 'n') {
        cout << "Введіть 'y' або 'n'!" << endl;
        return 1;
    }
    
    if (has_digits == 'y') {
        count++;
    }

    // Перевірка наявності великих літер у паролі.
    cout << "Чи є великі літери (y/n): ";
    cin >> has_uppercase;

    if (has_uppercase != 'y' && has_uppercase != 'n') {
        cout << "Введіть 'y' або 'n'!" << endl;
        return 1;
    }

    if (has_uppercase == 'y') {
        count++;
    }

    // Перевірка наявності спеціальних символів у паролі.
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> has_specials;

    if (has_specials != 'y' && has_specials != 'n') {
        cout << "Введіть 'y' або 'n'!" << endl;
        return 1;
    }
    
    if (has_specials == 'y') {
        count++;
    }

    // Перевірка мінімальних вимог до надійності пароля.
    if (count >= 2 && password_length >= 8) {
        cout << "Мінімальні вимоги: ПРОЙДЕНО " << endl;
    } else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО " << endl;
    }

    // Визначення рівня надійності за довжиною та складом пароля.
    if (password_length < 6) {
        level = 1;
        cout << "Рівень надійності: " << level << " - Дуже слабкий" << endl; 
    }

    else if (password_length < 8 || count == 0) {
        level = 2;
        cout << "Рівень надійності: " << level << " - Слабкий" << endl;
    }

    else if (count == 1) {
        level = 3;
        cout << "Рівень надійності: " << level << " - Середній" << endl;
    }

    else if (password_length >= 12 && count == 3) {
        level = 5;
        cout << "Рівень надійності: " << level << " - Дуже надійний" << endl;
    }

    else {
        level = 4;
        cout << "Рівень надійності: " << level << " - Надійний" << endl;
    }

    // Виведення рекомендації відповідно до визначеного рівня.
    switch (level) {
        case 1:
            cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << endl;
            break;

        case 2:
            cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
            break;

        case 3:
            cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << endl;
            break;

        case 4:
            cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
            break;

        case 5:
            cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << endl;
            break;

        default:
            cout << "Невідомий рівень надійності." << endl;
            break;
    }

    // Попередження для паролів без достатньої різноманітності символів.
    if (count == 0 || (!(has_digits == 'y') && !(has_specials == 'y'))) {
        cout << "Попередження: Пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;

}