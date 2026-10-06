#include <iostream>

using namespace std;

int main() {
    int length;
    char digits, uppercase, special;

    // Введення довжини пароля
    cout << "Довжина пароля (1-64): ";
    cin >> length;

    // Перевірка допустимого діапазону довжини
    if (length < 1 || length > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 0;
    }

    // Введення наявності цифр
    cout << "Чи є цифри (y/n): ";
    cin >> digits;

    // Перевірка правильності введення
    if (digits != 'y' && digits != 'n') {
        cout << "Помилка: потрібно ввести тільки y або n." << endl;
        return 0;
    }

    // Введення наявності великих літер
    cout << "Чи є великі літери (y/n): ";
    cin >> uppercase;

    if (uppercase != 'y' && uppercase != 'n') {
        cout << "Помилка: потрібно ввести тільки y або n." << endl;
        return 0;
    }

    // Введення наявності спеціальних символів
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> special;

    if (special != 'y' && special != 'n') {
        cout << "Помилка: потрібно ввести тільки y або n." << endl;
        return 0;
    }

    // Підрахунок кількості типів символів
    int types = 0;

    if (digits == 'y') {
        types++;
    }

    if (uppercase == 'y') {
        types++;
    }

    if (special == 'y') {
        types++;
    }

    // Перевірка мінімальних вимог
    bool minimumRequirements;

    if (length >= 8 && types >= 2) {
        minimumRequirements = true;
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    } else {
        minimumRequirements = false;
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }

    // Визначення рівня надійності
    int level;

    if (length < 6) {
        level = 1;
    }
    else if (length < 8 || types == 0) {
        level = 2;
    }
    else if (types == 1) {
        level = 3;
    }
    else if (length >= 12 && types == 3) {
        level = 5;
    }
    else {
        level = 4;
    }

    // Назва рівня
    cout << "Рівень надійності: ";

    if (level == 1) {
        cout << "1 - Дуже слабкий" << endl;
    }
    else if (level == 2) {
        cout << "2 - Слабкий" << endl;
    }
    else if (level == 3) {
        cout << "3 - Середній" << endl;
    }
    else if (level == 4) {
        cout << "4 - Надійний" << endl;
    }
    else {
        cout << "5 - Дуже надійний" << endl;
    }

    // Рекомендація за допомогою switch case
    cout << "Рекомендація: ";

    switch (level) {
        case 1:
            cout << "Пароль надто короткий. Мінімум 8 символів.";
            break;

        case 2:
            cout << "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.";
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

        default:
            cout << "Невідомий рівень.";
            break;
    }

    cout << endl;

    return 0;
}