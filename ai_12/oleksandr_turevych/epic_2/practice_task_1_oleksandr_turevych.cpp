/* Задача: Практична задача: аналізатор надійності пароля
* Туревич Олександр
* Група ШІ-12
*/

#include <iostream>

using namespace std;

int main() {
    int length;
    char has_digits; 
    char has_upper; 
    char has_special;

    // 1. Введення даних
    cout << "Довжина пароля: ";
    cin >> length;

    if (length < 1 || length > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 0;
    }

    cout << "Чи є цифри (y/n): ";
    cin >> has_digits;
    if (has_digits != 'y' && has_digits != 'n') {
        cout << "Помилка: введіть дійсне значення (y/n)." << endl;
        return 0;
    }

    cout << "Чи є великі літери (y/n): ";
    cin >> has_upper;
    if (has_upper != 'y' && has_upper != 'n') {
        cout << "Помилка: введіть дійсне значення (y/n)." << endl;
        return 0;
    }

    cout << "Чи є спеціальні символи (y/n): ";
    cin >> has_special;
    if (has_special != 'y' && has_special != 'n') {
        cout << "Помилка: введіть дійсне значення (y/n)." << endl;
        return 0;
    }

    // 2. Підрахунок типів символів
    int count = 0;
    if (has_digits == 'y') count++;
    if (has_upper == 'y') count++;
    if (has_special == 'y') count++;

    // 3. Мінімальні вимоги
    cout << "Мінімальні вимоги: ";
    if (length >= 8 && count >= 2) {
        cout << "ПРОЙДЕНО" << endl;
    } else {
        cout << "НЕ ПРОЙДЕНО" << endl;
    }

    // 4. Визначення рівня
    int level = 0;
    cout << "Рівень надійності: ";

    if (length < 6) {
        level = 1;
        cout << level << " - Дуже слабкий" << endl;
    } 
    else if (length < 8 || count == 0) {
        level = 2;
        cout << level << " - Слабкий" << endl;
    } 
    else if (count == 1) {
        level = 3;
        cout << level << " - Середній" << endl;
    } 
    else if (length >= 12 && count == 3) {
        level = 5;
        cout << level << " - Дуже надійний" << endl;
    } 
    else {
        level = 4;
        cout << level << " - Надійний" << endl;
    }

    // 5. Рекомендація
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
            cout << "Невідомий рівень." << endl;
            break;
    }

    // 6. Попередження (пароль без цифр і спецсимволів, тобто тільки з літер)
    if (has_digits == 'n' && has_special == 'n' && length >= 4) {
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    }

    return 0;
}