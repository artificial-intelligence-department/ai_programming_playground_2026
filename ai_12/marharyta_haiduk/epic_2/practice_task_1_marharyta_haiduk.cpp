/*
    Задача: Аналізатор надійності пароля
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
using namespace std;
int main() {
    // Введення довжини пароля та перевірка діапазону (1-64)
    int password_length;
    cout << "Введіть довжину пароля: ";
    cin >> password_length;
    if (password_length<1 || password_length>64) 
    {
        cout<<"Помилка: довжина мусить бути від 1 до 64.";
        return 1;
    }
    // Введення наявності цифр та перевірка (тільки y або n)
    char has_digits;
    cout << "Чи є цифри (y/n): ";
    cin >> has_digits;
    if (!(has_digits == 'y' || has_digits == 'n')) 
    {
        cout<<"Помилка: потрібно ввести y або n.";
        return 1;
    }
    // Введення наявності великих літер та перевірка
    char has_uppercase;
    cout << "Чи є великі літери (y/n): ";
    cin >> has_uppercase;
    if (has_uppercase != 'y' && has_uppercase != 'n') 
    {
        cout<<"Помилка: потрібно ввести y або n.";
        return 1;
    }
    // Введення наявності спеціальних символів та перевірка
    char has_special;
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> has_special; 
    if (has_special != 'y' && has_special != 'n') 
    {
        cout<<"Помилка: потрібно ввести y або n.";
        return 1;
    }
    // Підрахунок кількості типів символів у паролі (від 0 до 3)
    int type_count = 0; 
    if (has_digits == 'y') 
    {
        type_count++;
    }
    if (has_uppercase == 'y') 
    {
        type_count++;
    }
    if (has_special == 'y') 
    {
        type_count++;
    }
    // Перевірка мінімальних вимог 
    cout<<"Мінімальні вимоги: "; 
    if (password_length>=8 && type_count>=2) 
    {
        cout<<"ПРОЙДЕНО"<<endl;
    }
    else 
    {
        cout<<"НЕ ПРОЙДЕНО"<<endl;
    }
    // Визначення рівня надійності
    int level; 
    if (password_length<6) 
    {
        level = 1;
    }
    else if (password_length<8 || type_count == 0)
    {
        level = 2;
    }
    else if (type_count == 1)
    {
        level = 3;
    }
    else if (password_length>=12 && type_count == 3)
    {
        level = 5;
    }
    else
    {
        level = 4;
    }
    // Виведення назви рівня та рекомендації
    switch (level) 
    {
        case 1:
        cout << "Рівень надійності: 1 - Дуже слабкий"<< endl;
        cout << "Рекомендація: Пароль надто короткий. Мінімум 8 символів.";
        break;
        case 2:
        cout << "Рівень надійності: 2 - Слабкий"<< endl;
        cout << "Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.";
        break;
        case 3:
        cout << "Рівень надійності: 3 - Середній"<< endl;
        cout << "Рекомендація: Додайте ще один тип символів або збільште довжину до 12.";
        break;
        case 4:
        cout << "Рівень надійності: 4 - Надійний"<< endl;
        cout << "Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів.";
        break;
        case 5:
        cout << "Рівень надійності: 5 - Дуже надійний"<< endl; 
        cout << "Рекомендація: Відмінно. Змінювати нічого не потрібно. ";
        break;
        default:
        cout << "Помилка: невідомий рівень надійності.";
        break;
    }
    // Попередження для пароля без цифр і спеціальних символів
    if (has_digits == 'n' && has_special == 'n') {
        cout << endl << "Попередження: пароль тільки з літер підбирається швидше.";
    }
    return 0;
}
