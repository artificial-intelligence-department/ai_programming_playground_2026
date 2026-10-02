#include <iostream>

using namespace std;

int main() {
    int length;
    char has_digits, has_uppercase, has_special;

    cout << "Довжина пароля: ";
    cin >> length;

    if (length < 1 || length > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 0;
    }

    cout << "Чи є цифри (y/n): ";
    cin >> has_digits;
    cout << "Чи є великі літери (y/n): ";
    cin >> has_uppercase;
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> has_special;

    if (!(has_digits == 'y' || has_digits == 'n') ||
        !(has_uppercase == 'y' || has_uppercase == 'n') ||
        !(has_special == 'y' || has_special == 'n')) {
        cout << "Помилка: введіть дійсне значення (y/n)." << endl;
        return 0;
    }

    // Мінімальні вимоги
    if (length >= 8 && ((has_digits == 'y' && has_uppercase == 'y') || 
                        (has_digits == 'y' && has_special == 'y') || 
                        (has_uppercase == 'y' && has_special == 'y'))) {
        cout << "\nМінімальні вимоги: ПРОЙДЕНО" << endl;
    } else {
        cout << "\nМінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }

    // Рівень надійності
    int lvl;
    if (length < 6) {
        lvl = 1;
    } else if (length < 8 || (has_digits == 'n' && has_uppercase == 'n' && has_special == 'n')) {
        lvl = 2;
    } else if ((has_digits == 'y' && has_uppercase == 'n' && has_special == 'n') ||
               (has_digits == 'n' && has_uppercase == 'y' && has_special == 'n') ||
               (has_digits == 'n' && has_uppercase == 'n' && has_special == 'y')) {
        lvl = 3;
    } else if (length >= 12 && has_digits == 'y' && has_uppercase == 'y' && has_special == 'y') {
        lvl = 5;
    } else {
        lvl = 4;
    }

    // Світч кейс для рівня надійності
    cout << "Рівень надійності: " << lvl << " - ";
    switch (lvl) {
        case 1:
            cout << "Дуже слабкий" << endl;
            break;
        case 2:
            cout << "Слабкий" << endl;
            break;
        case 3:
            cout << "Середній" << endl;
            break;
        case 4:
            cout << "Надійний" << endl;
            break;
        case 5:
            cout << "Дуже надійний" << endl;
            break;
        default:
            cout << "Невідомо" << endl;
            break;
    }

    // Світч кейс для рекомендації
    cout << "Рекомендація: ";
    switch (lvl) {
        case 1:
            cout << "Пароль надто короткий. Мінімум 8 символів." << endl;
            break;
        case 2:
            cout << "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
            break;
        case 3:
            cout << "Додайте ще один тип символів або збільште довжину до 12." << endl;
            break;
        case 4:
            cout << "Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
            break;
        case 5:
            cout << "Відмінно. Змінювати нічого не потрібно." << endl;
            break;
        default:
            cout << "Немає рекомендації." << endl;
            break;
    }

    // Попередження
    if (has_digits == 'n' && has_special == 'n') {
        cout << "Попередження: Пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}