/*
Задача: Аналізатор надійності пароля
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
    //Ініціалізація змінних
    int pass_length;        //Довжина пароля
    int level;              //Рівень надійності пароля
    string t;               //Проміжна змінна для конвертації рядкової відповіді 'y'/'n' у bool
    string level_label;     //Назва рівня надійності пароля
    string recommendation;  //Текст рекомендації до пароля
    bool warning = false;
    bool contains_digit;    //Чи містить пароль цифри
    bool contains_capital;  //Чи містить пароль великі літери
    bool contains_specials; //Чи містить пароль спеціальні знаки

    int diff_types = 0;     //Кількість типів символів
    bool min_requirements;  //Чи пройдено мінімальні вимоги до пароля

    //Блок введення змінних користувачем і їх валідацієя
    cout << "Enter password length: ";
    cin >> pass_length;
    if(pass_length < 1 || pass_length > 64)
    {
        cout << "Error: length must be between 1 and 64.";
        return 1;
    }

    cout << "Contains digits (y/n): ";
    cin >> t;
    if(t == "y")
    {
        contains_digit = true;
        diff_types++;
    }
    else if(t == "n")
    {
        contains_digit = false;
    }
    else
    {
        cout << "Error: answer with either 'y' or 'n'.";
        return 1;
    }

    cout << "Contains capitals (y/n): ";
    cin >> t;
    if(t == "y")
    {
        contains_capital = true;
        diff_types++;
    }
    else if(t == "n")
    {
        contains_capital = false;
    }
    else
    {
        cout << "Error: answer with either 'y' or 'n'.";
        return 1;
    }

    cout << "Contains special symbols (y/n): ";
    cin >> t;
    if(t == "y")
    {
        contains_specials = true;
        diff_types++;
    }
    else if(t == "n")
    {
        contains_specials = false;
    }
    else
    {
        cout << "Error: answer with either 'y' or 'n'.";
        return 1;
    }

    //Перевірка на проходження мінімальних вимог до пароля
    if(pass_length < 8 || diff_types < 2)
    {
        min_requirements = false;
    }
    else
    {
        min_requirements = true;
    }

    //Визначення рівня надійності пароля
    if(pass_length < 6)
    {
        level = 1;
        level_label = "Too weak";
    }
    else if(pass_length < 8 || diff_types == 0)
    {
        level = 2;
        level_label = "Weak";
    }
    else if(diff_types == 1)
    {
        level = 3;
        level_label = "Medium";
    }
    else if(pass_length >= 12 && diff_types == 3)
    {
        level = 5;
        level_label = "Very reliable";
    }
    else
    {
        level = 4;
        level_label = "Reliable";
    }

    //Визначення рекомендації в залежності від рівня надійності пароля. Використовуємо switch case
    switch (level)
    {
        case 1:
            recommendation = "Password is too short. Minimum 8 characters.";
            break;
        case 2:
            recommendation = "Increase the length to 8+ characters and add numbers, uppercase letters, or special characters.";
            break;
        case 3:
            recommendation = "Add another character type or increase the length to 12.";
            break;
        case 4:
            recommendation = "A good password. For a maximum of 12+ characters and all three character types.";
            break;
        case 5:
            recommendation = "Excellent. No need to change anything.";
            break;
        default:
            recommendation = "An incorrect reliability level is given, no recommendation.";
            break;
    }

    if(!contains_digit && !contains_specials) warning = true; //Перевірка, чи потрібно виводити користувачу попередження

    //Блок виведення
    cout << endl;
    cout << "Minimal requirements: " << (min_requirements ? "PASSED" : "NOT PASSED") << endl;
    cout << "Reliability level: " << level << " - " << level_label << endl;
    cout << "Recommendation: " << recommendation;
    if(warning) cout << endl << "Warning: a password with only letters is cracked faster."; //Якщо попередження потрібне - виводимо його

    return 0;
}
