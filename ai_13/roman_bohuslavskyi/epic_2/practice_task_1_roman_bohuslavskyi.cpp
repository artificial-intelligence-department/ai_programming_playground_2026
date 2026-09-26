/*
Задача:  Аналізатор надійності пароля
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
using namespace std;

int main() {
    int length;
    char digits;
    char uppercase;
    char special;

    // Довжина пароля: ціле число від 1 до 64
    cout << "Введіть довжину пароля (від 1 до 64): ";
    cin >> length;

    if (cin.fail() || length < 1 || length > 64) {
        cout << "Помилка: довжина пароля мусить бути від 1 до 64." << endl;
        return 1;
    }

    // Наявність цифр
    cout << "Чи є цифри? Введіть y або n: ";
    cin >> digits;

    if (cin.fail() || (digits != 'y' && digits != 'n')) {
        cout << "Помилка: введіть y або n." << endl;
        return 1;
    }

    // Наявність великих літер
    cout << "Чи є великі літери? Введіть y або n: ";
    cin >> uppercase;

    if (cin.fail() || (uppercase != 'y' && uppercase != 'n')) {
        cout << "Помилка: введіть y або n." << endl;
        return 1;
    }

    // Наявність спеціальних символів
    cout << "Чи є спеціальні символи? Введіть y або n: ";
    cin >> special;

    if (cin.fail() || (special != 'y' && special != 'n')) {
        cout << "Помилка: введіть y або n." << endl;
        return 1;
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

    cout << " " << endl;
    // Перевірка мінімальних вимог
    if (length >= 8 && types >= 2) {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    }
    else {
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

    // Вивід рівня надійності
    cout << "Рівень надійності: " << level << " - ";

    if (level == 1) {
        cout << "Дуже слабкий" << endl;
    }
    else if (level == 2) {
        cout << "Слабкий" << endl;
    }
    else if (level == 3) {
        cout << "Середній" << endl;
    }
    else if (level == 4) {
        cout << "Надійний" << endl;
    }
    else {
        cout << "Дуже надійний" << endl;
    }

    // Рекомендація користувачу
    cout << "Рекомендація: ";

    switch (level) {
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
        cout << "Помилка визначення рівня." << endl;
        break;
    }

    // Попередження для пароля тільки з літер
    if (!(digits == 'y' || special == 'y')) {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}