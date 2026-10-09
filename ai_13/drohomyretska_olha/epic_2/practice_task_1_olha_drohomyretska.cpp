/*
Аналізатор надійності пароля
Дрогомирецька Ольга
ШІ - 13
*/
#include <iostream>
using namespace std;

int main() {
    // Ініціалізація змінних
    int length;
    char hasdigits, hasupper, hasspecial;

    cout << "Довжина пароля: ";
    cin >> length;

    // Перевірка введених даних
    if (length < 1 || length > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 1;
    }

    cout << "Чи є цифри (y/n): ";
    cin >> hasdigits;
    if (!(hasdigits == 'y' || hasdigits == 'n')) {
        cout << "Помилка: введіть y або n." << endl;
        return 1;
    }

    cout << "Чи є великі літери (y/n): ";
    cin >> hasupper;
    if (hasupper != 'y' && hasupper != 'n') {
        cout << "Помилка: введіть y або n." << endl;
        return 1;
    }
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> hasspecial;
    if (!(hasspecial == 'y' || hasspecial == 'n')) {
        cout << "Помилка: введіть y або n." << endl;
        return 1;
    }
    // Кількість типів символів потрібна для оцінки надійності пароля.
    int types = 0;
    if (hasdigits == 'y') types++;
    if (hasupper == 'y') types++;
    if (hasspecial == 'y') types++;
    cout << endl;

    // Перевірка вимог з умови: 8+ символів і 2+ типи символів
    if (length >= 8 && types >= 2) {
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    } else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;
    }
    int level;

    // Рівні 1-5 визначаються відповідно до таблиці з умови
    if (length < 6) {
        level = 1;
    } else if (length < 8 || types == 0) {
        level = 2;
    } else if (types == 1) {
        level = 3;
    } else if (length >= 12 && types == 3) {
        level = 5;
    } else {
        level = 4;
    }

    // Виведення рівня надійності
    cout << "Рівень надійності: " << level << " - ";
    switch (level) {
        case 1:
            cout << "Дуже слабкий" << endl;
            cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << endl;
            break;
        case 2:
            cout << "Слабкий" << endl;
            cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, "
                    "великі літери або спеціальні символи." << endl;
            break;
        case 3:
            cout << "Середній" << endl;
            cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << endl;
            break;
        case 4:
            cout << "Надійний" << endl;
            cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
            break;
        case 5:
            cout << "Дуже надійний" << endl;
            cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << endl;
            break;
        default:
            cout << "Помилка визначення рівня надійності." << endl;
            break;
    }
    // Додаткове попередження, якщо пароль складається тільки з літер
    if (hasdigits != 'y' && hasspecial != 'y') {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }
    return 0;
}