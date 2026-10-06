/*Аналізатор надійності пароля
ШІ-14
Кравець Аліна*/
#include <iostream>

using namespace std;

int main()
{
    int password_length = 0; //створення змінних
    char numbers = 'n';
    char capital_letters = 'n';
    char special_characters = 'n';
    int symbol_types = 0;
    int reliability_level = 0;

    cout << "Довжина пароля: ";
    cin >> password_length;
    if (password_length < 1 || password_length > 64) //довжина пароля має бути від 1 до 64 включно
    {
        cout << "Помилка: довжина пароля може бути від 1 до 64" << endl;
        return 1;
    }

    cout << "Чи є цифри (y/n): ";
    cin >> numbers;
    if (numbers != 'y' && numbers != 'n') //ми можемо ввести лише так('y') або ні('n')
    {
        cout << "Помилка: введіть 'y' або 'n'" << endl;
        return 1;
    }
    if (numbers == 'y') //якщо є цифри, в нас є +1 тип символів
    {
        symbol_types++;
    }

    cout << "Чи є великі літери (y/n): ";
    cin >> capital_letters;
    if (capital_letters != 'y' && capital_letters != 'n')//ми можемо ввести лише так('y') або ні('n')
    {
        cout << "Помилка: введіть 'y' або 'n'" << endl;
        return 1;
    }
    if (capital_letters == 'y')//якщо є великі літери, в нас є +1 тип символів
    {
        symbol_types++;
    }

    cout << "Чи є спеціальні символи (y/n): ";
    cin >> special_characters;
    if (special_characters != 'y' && special_characters != 'n')//ми можемо ввести лише так('y') або ні('n')
    {
        cout << "Помилка: введіть 'y' або 'n'" << endl;
        return 1;
    }
    if (special_characters == 'y')//якщо є спеціальні символи, в нас є +1 тип символів
    {
        symbol_types++;
    }
    
    if (password_length >= 8 && symbol_types >=2)//мінімальні вимоги - хоча б 8 символів і 2 типи символів 
    {
        cout << "Мінімальні вимоги: Пройдено" << endl;
    }
    else
    {
        cout << "Мінімальні вимоги: Не пройдено" << endl;
    }

    if (password_length < 6)//<6 символів - дуже слабкий рівень надійності
    {
        reliability_level = 1;
    }
    else if (password_length < 8 || symbol_types == 0)//<8 символів або 0 типів символів - слабкий рівень надійності
    {
        reliability_level = 2;
    }
    else if (symbol_types == 1)//1 тип сиволів - середній рівень надійності
    {
        reliability_level = 3;
    }
    else if (password_length >= 12 && symbol_types == 3)//>12 символів і 3 типи символів - дуже високий рівень надійності
    {
        reliability_level = 5;
    }
    else//всі інщі випадки - високий рівень надійності
    {
        reliability_level = 4;
    }

    switch (reliability_level)//при різних рівнях надійності виводяться різні рекомендації
    {
        case 1:
        cout << "Рівень надійності: 1 - дуже слабкий" << endl;
        cout << "Рекомендація: пароль занадто короткий, мінімум - 8 символів" << endl;
        break;
        case 2:
        cout << "Рівень надійності: 2 - слабкий" << endl;
        cout << "Рекомендація: збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl;
        break;
        case 3:
        cout << "Рівень надійності: 3 - середній" << endl;
        cout << "Рекомендація: додайте ще один тип символів або збільште довжину до 12" << endl;
        break;
        case 4:
        cout << "Рівень надійності: 4 - надійний" << endl;
        cout << "Рекомендація: хороший пароль, для максимуму 12+ символів і всі три типи символів" << endl;
        break;
        case 5:
        cout << "Рівень надійності: 5 - дуже надійний" << endl;
        cout << "Рекомендація: відмінно, змінювати нічого не потрібно." << endl;
        break;
        default:
        cout << "Рівень надійності: відсутній" << endl;
        cout << "Рекомендація: немає рекомендацій" << endl;
    }

    if(numbers == 'n' && special_characters == 'n')//якщо немає чисел і спеціальних символів - виводиться попередження
    {
        cout << "Попередження: пароль тільки з літер підбирається швидше" << endl;
    }

    return 0;
}
