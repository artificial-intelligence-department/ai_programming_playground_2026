/* Задача: Аналізатор надійності пароля
    Автор: Сукaч Андрій
    Група: ШІ-14
    Аналізатор надійності пароля
*/
#include <iostream>
using namespace std;
int main() {
    int length; // довжина пароля
    char has_caps, has_digit, has_Spec; //змінні(Великі літери, цифри, спеціальні символи)(y/n)

    cout << "Введіть довжину пароля(ціле число 1-64): ";
    cin >> length;

    if (length > 64 || length < 1) { // перевірка довжини пароля
        cout << "Не правильне значення" << endl;
        return 0;
    }


    cout << "Чи містить пароль цифри? (y - так, n - ні): ";
    cin >> has_digit;
    cout << "Чи містить пароль великі літери? (y - так, n - ні): ";
    cin >> has_caps;
    cout << "Чи містить пароль спеціальні символи? (y - так, n - ні): ";
    cin >> has_Spec;

    //перевірка правильності введених значень
    if ((has_caps != 'y' && has_caps != 'n') || (has_digit != 'y' && has_digit != 'n') || (has_Spec != 'y' && has_Spec != 'n')) {
        cout << "Не правильне значення" << endl;
        return 0;
    }

    int typesymbols = 0; // підрахунок кількості типів символів
    if (has_caps == 'y') typesymbols++;
    if (has_digit == 'y') typesymbols++;
    if (has_Spec == 'y') typesymbols++;



    // Перевірка мінімальних вимог
    if (length >= 8 && typesymbols >= 2) {
        cout << "Мінімальні вимоги: ПРОЙДЕНІ" << endl;
    } else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНІ" << endl;
    }

    // Визначення рівня надійності
    int strengthLevel = 0; // Початковий рівень
    if (length < 6) {
        strengthLevel = 1; // Дуже слабкий
    } else if (length < 8 || typesymbols == 0) {
        strengthLevel = 2; // Слабкий
    } else if (typesymbols == 1) {
        strengthLevel = 3; // Середній
    } else if (length >= 12 && typesymbols == 3) {
        strengthLevel = 5; // Дуже надійний
    } else {
        strengthLevel = 4; // Надійний
    }

    // Виведення рекомендацій
    switch (strengthLevel) {
        case 1:
        cout << "ріввень надійності: 1 - Дуже слабкий" << endl;
            break;
        cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << endl;
            break;
        case 2:
            cout << "ріввень надійності: 2 - Слабкий" << endl;
            cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
            break;
        case 3:
            cout << "ріввень надійності: 3 - Середній" << endl;
            cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << endl;
            break;
        case 4:
            cout << "ріввень надійності: 4 - Надійний" << endl;
            cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl;
            break;
        case 5:
            cout << "ріввень надійності: 5 - Дуже надійний" << endl;
            cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << endl;
            break;
            default: cout << "Помилка: неможливо визначити рівень безпеки пароля." << endl; 
            break;
    }
    if (has_Spec == 'n' && has_digit == 'n') { // Перевірка на Попередження, що пароль містить лише літери
        cout << "Попередження: пароль тільки з літер підбирається швидше." << endl;
    } else cout << "Попередження: немає попереджень" << endl;
        return 0;
    }