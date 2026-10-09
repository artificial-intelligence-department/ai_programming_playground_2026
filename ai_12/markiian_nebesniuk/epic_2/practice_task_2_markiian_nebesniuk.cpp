/*
Аналізатор надійності пароля
Небеснюк Маркіян
ШІ-12
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    int password_length;
    char number;
    char capital_letter;
    char special_symbol;

    // Зчитування довжини пароля та перевірка на обмеження
    cout << "Довжина пароля: ";
    cin >> password_length;
    if (password_length > 64 || password_length < 1) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 1;
    }

    // Зчитування інформації про наявність цифр та валідація вводу
    cout << "Чи є цифри (y/n): ";
    cin >> number;
    if (number != 'y' && number != 'n') {
        cout << "Помилка: введіть дійсне значення." << endl;
        return 1;
    }

    // Зчитування інформації про наявність великих літер та валідація вводу
    cout << "Чи є великі літери (y/n): ";
    cin >> capital_letter;
    if (capital_letter != 'y' && capital_letter != 'n') {
        cout << "Помилка: введіть дійсне значення." << endl;
        return 1;
    }

    // Зчитування інформації про наявність спецсимволів та валідація вводу
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> special_symbol;
    cout << endl;
    if (special_symbol != 'y' && special_symbol != 'n') {
        cout << "Помилка: введіть дійсне значення." << endl;
        return 1;
    }

    // Підрахунок кількості типів символів
    int symbol_type = 0;
    if (number == 'y') {
        symbol_type++;
    }
    if (capital_letter == 'y') {
        symbol_type++;
    }
    if (special_symbol == 'y') {
        symbol_type++;
    }

    // Перевірка мінімальних вимог
    if (password_length >= 8 && symbol_type >= 2) {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    }
    else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }

    // Визначення рівня надійності
    int reliability_level = 0;
    if (password_length < 6) {
        cout << "Рівень надійності: 1 - Дуже слабкий" << endl;
        reliability_level = 1;
    }
    else if (password_length < 8 || symbol_type == 0) {
        cout << "Рівень надійності: 2 - Слабкий" << endl;
        reliability_level = 2;
    }
    else if (symbol_type == 1) {
        cout << "Рівень надійності: 3 - Середній" << endl;
        reliability_level = 3;
    }
    else if (password_length >= 12 && symbol_type == 3) {
        cout << "Рівень надійності: 5 - Дуже надійний" << endl;
        reliability_level = 5;
    }
    else {
        cout << "Рівень надійності: 4 - Надійний" << endl;
        reliability_level = 4;
    }

    // Надання рекомендацій на основі рівня надійності
    cout << "Рекомендація: ";
    switch (reliability_level) {
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
            cout << "Невідомий рівень." << endl;
            break;
    }

    // Виведення попередження, якщо пароль тільки з літер
    if (number == 'n' && special_symbol == 'n') {
        cout << "Попередження: пароль тільки з літер підбирається швидше" << endl;
    }

    return 0;
}