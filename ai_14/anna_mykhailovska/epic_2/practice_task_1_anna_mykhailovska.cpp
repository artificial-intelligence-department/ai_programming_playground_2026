/*
    Задача: Аналізатор надійності пароля
    Михайловська Анна
    ШІ-14
*/
#include <iostream>
using namespace std;

int main() {

    const int MAX_LENGTH = 64;   // максимальне значення довжини паролю

    int password_length = 0;
    char number = ' ';
    char uppercase_letters = ' ';
    char special_characters = ' ';

    cout << "Довжина пароля: ";
    if (!(cin >> password_length) || password_length < 1 || password_length > MAX_LENGTH ){
        cout << "Помилка: довжина паролю має бути числом від 1 до 64\n";
        return 1;
    }

    // Зчитуємо характеристики пароля і завершуємо роботу за некоректного вводу
    cout << "Чи є цифри (y/n): ";
    cin >> number;
    if (!(number == 'y') && !(number == 'n')){
        cout << "Помилка: вкажіть лише y чи n\n";
        return 1;
    }

    cout << "Чи є великі літери (y/n): ";
    cin >> uppercase_letters;
    if (!(uppercase_letters == 'y') && !(uppercase_letters == 'n')){
        cout << "Помилка: вкажіть лише y чи n\n";
        return 1;
    }

    cout << "Чи є спеціальні символи (y/n): ";
    cin >> special_characters;
    if (!(special_characters == 'y') && !(special_characters == 'n')){
        cout << "Помилка: вкажіть лише y чи n\n";
        return 1;
    }
    
    // Рахуємо, скільки з трьох типів символів є в паролі
    int count = 0;
    if (number == 'y')
    count = count + 1;

    if (uppercase_letters == 'y')
    count = count + 1;

    if (special_characters == 'y')
    count = count + 1;

    // Перевіряємо мінімальні вимоги
    if (password_length >= 8 && count >= 2 )
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << endl;
    else 
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << endl;

    
    int level = 0;

    // Перевіряємо рівень надійності паролю
    if (password_length < 6) {
        level = 1;
    } else if (password_length < 8 || count ==0) {
        level = 2;
    } else if (count == 1) {
        level = 3;
    } else if (password_length >= 12 && count == 3) {
        level = 5;
    } else {
        level = 4;
    }

     // Для кожного рівня виводимо відповідну рекомендацію
    switch (level){
        case 1:
            cout << "Рівень надійності: 1 - Дуже слабкий \nРекомендація: Пароль надто короткий. Мінімум 8 символів.";
            break;
        case 2:
            cout << "Рівень надійності: 2 - Слабкий \nРекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.";
            break;
        case 3:
            cout << "Рівень надійності: 3 - Середній \nРекомендація: Додайте ще один тип символів або збільште довжину до 12.";
            break;
        case 4:
            cout << "Рівень надійності: 4 - Надійний \nРекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів.";
            break;
        case 5:
            cout << "Рівень надійності: 5 - Дуже надійний \nРекомендація: Відмінно. Змінювати нічого не потрібно.";
            break;
        default:
            cout << "Помилка: невідомий рівень надійності.\n";
            break;
    }

    cout << '\n';

    // Якщо немає цифр і спеціальних символів, виводимо попередження.
    if (number == 'n' && special_characters == 'n') {
        cout << "Попередження: пароль тільки з літер підбирається швидше.\n";
    }

    return 0;
}
