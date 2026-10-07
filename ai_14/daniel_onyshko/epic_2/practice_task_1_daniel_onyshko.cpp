/*
    Задача: Аналізатор надійності пароля
    Автор: Онишко Даніель
    Група: ШІ-14
*/

#include <iostream>
using namespace std;

int main() {
    // Змінні для зберігання введених користувачем даних
    int password_length;
    char numbers, upper, special;

    // Введення користувачем даних з перевіркою коректності
    cout << "Довжина пароля: ";
    cin >> password_length;
    if (password_length < 1 || password_length > 64) {
        cout << "Помилка: довжина мусить бути від 1 до 64." << endl;
        return 1;
    } 
    cout << "Чи є цифри (y/n): ";
    cin >> numbers;
    if (numbers != 'y' && numbers != 'n') {
        cout << "Відповідь повинна бути y або n" << endl;
        return 1;
    }
    cout << "Чи є великі літери (y/n): ";
    cin >> upper;
    if (upper != 'y' && upper != 'n') {
        cout << "Відповідь повинна бути y або n" << endl;
        return 1;
    }
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> special;
    if (special != 'y' && special != 'n') {
        cout << "Відповідь повинна бути y або n" << endl;
        return 1;
    }
    cout << " " << endl;

    // Підраховуємо кількість різних типів символів, які присутні в паролі
    int types_quantity = 0;
    if (numbers == 'y') {
        types_quantity++;
    }
    if (upper == 'y') {
        types_quantity++;
    }
    if (special == 'y') {
        types_quantity++;
    }

    // Перевірка мінімальних вимог до пароля
    if (password_length >= 8 && types_quantity >= 2) {
        cout << "Мінімальні вимоги: Пройдено" << endl;
    } else {
        cout << "Мінімальні вимоги: Не пройдено" << endl;
    }

    // Визначення рівня надійності пароля (шкала від 1 до 5)
    int security_level = 0;
    if (password_length < 6) {
        cout << "Рівень надійності: 1 – Дуже слабкий" << endl;
        security_level = 1;
    } else if (password_length < 8 || types_quantity == 0) {
        cout << "Рівень надійності: 2 – Слабкий" << endl;
        security_level = 2;
    } else if (types_quantity == 1) {
        cout << "Рівень надійності: 3 – Середній" << endl;
        security_level = 3;
    } else if (password_length >= 12 && types_quantity == 3) {
        cout << "Рівень надійності: 5 – Дуже надійний" << endl;
        security_level = 5;
    } else {
        cout << "Рівень надійності: 4 – Надійний" << endl;
        security_level = 4;
    }

    // Вивід рекомендації відповідно до визначеного рівня надійності
    switch (security_level) {
        case 1: cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів." << endl; 
        break;
        case 2: cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl; 
        break;
        case 3: cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12." << endl;
         break;
        case 4: cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl; 
        break;
        case 5: cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно." << endl; 
        break;
        default: cout << "Помилка: неможливо визначити рівень безпеки пароля." << endl; 
            break;
    }

    // Додаткове попередження, якщо пароль складається лише з малих літер
    if (numbers == 'n' && special == 'n') {
        cout << "Попередження: Пароль тільки з літер підбирається швидше.";
    }
    return 0;
}