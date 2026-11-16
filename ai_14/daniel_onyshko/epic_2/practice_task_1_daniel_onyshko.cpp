/*
    Задача: Аналізатор надійності пароля
    Автор: Онишко Даніель
    Група: ШІ-14
*/

#include <iostream>
using namespace std;

int main() {
    // Змінні для зберігання введених користувачем даних
    int length_val;
    char digits_flag, upper_flag, special_flag;

    // Введення користувачем даних з перевіркою коректності
    cout << "Довжина пароля: ";
    if (!(cin >> length_val) || length_val < 1 || length_val > 64) {
        cout << "Помилка: довжина повинна бути в діапазоні від 1 до 64." << endl;
        return 1;
    } 
    cout << "Чи є цифри (y/n): ";
    cin >> digits_flag;
    cout << "Чи є великі літери (y/n): ";
    cin >> upper_flag;
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> special_flag;
    if ((digits_flag != 'y' && digits_flag != 'n') ||
        (upper_flag != 'y' && upper_flag != 'n') ||
        (special_flag != 'y' && special_flag != 'n')) {
        cout << "Помилка: дозволено вводити тільки 'y' або 'n'." << endl;
        return 1;
    }
    cout << " " << endl;

    // Підраховуємо кількість різних типів символів, які присутні в паролі
    int types_quantity = 0;
    if (digits_flag == 'y') {
        types_quantity++;
    }
    if (upper_flag == 'y') {
        types_quantity++;
    }
    if (special_flag == 'y') {
        types_quantity++;
    }

    // Перевірка мінімальних вимог до пароля
    if (length_val >= 8 && types_quantity >= 2) {
        cout << "Мінімальні вимоги: Пройдено" << endl;
    } else {
        cout << "Мінімальні вимоги: Не пройдено" << endl;
    }

    // Визначення рівня надійності пароля (шкала від 1 до 5)
    int security_level = 0;
    if (length_val < 6) {
        security_level = 1; // Дуже слабкий
    } else if (length_val < 8 || types_quantity == 0) {
        security_level = 2; // Слабкий
    } else if (types_quantity == 1) {
        security_level = 3; // Середній
    } else if (length_val >= 12 && types_quantity == 3) {
        security_level = 5; // Дуже надійний
    } else {
        security_level = 4; // Надійний
    }

    // Вивід рекомендації відповідно до визначеного рівня надійності
    switch (security_level) {
        case 1: 
            cout << "Рівень надійності: 1 - Дуже слабкий" << endl;
            cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << endl; 
        break;
        case 2:
            cout << "Рівень надійності: 2 - Слабкий" << endl;
            cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl; 
        break;
        case 3:
            cout << "Рівень надійності: 3 - Середній" << endl; 
            cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << endl;
         break;
        case 4: 
            cout << "Рівень надійності: 4 - Надійний" << endl;
            cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl; 
        break;
        case 5:
            cout << "Рівень надійності: 5 - Дуже надійний" << endl; 
            cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << endl; 
        break;
        default:
            cout << "Помилка: неможливо визначити рівень безпеки пароля." << endl; 
            break;
    }

    // Додаткове попередження, якщо пароль складається лише з малих літер
if (digits_flag == 'n' && special_flag == 'n') {
        cout << "Попередження: Пароль тільки з літер підбирається швидше.";
    }
    return 0;
}