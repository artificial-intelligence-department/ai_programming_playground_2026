#include <iostream>
using namespace std;
int main()
{
    int length;
    //Ввід даних і перевірка чи вони дозволені в програмі, якщо ні, то після неправильного вводу виводиться, що поправити
    cout <<"Довжина пароля: ";
    if(cin >>length)
    {
        if(length>=1 && length<=64){}
        else
        {
            cout <<"Введіть число від 1 до 64"  <<endl;
            return 1;
        }
    } else
    {
        cout <<"Введіть число від 1 до 64" <<endl;
        return 1;
    }
    cout <<"Чи є цифри (y/n): ";
    char numbers;
    if(cin >>numbers)
    {
        if(numbers=='y' || numbers=='n'){}
        else
        {
            cout <<"Введіть букви y або n" <<endl;
            return 1;
        }
    }
    else
    {
        cout <<"Введіть букви y або n" <<endl;
        return 1;
    }
    cout <<"Чи є великі літери (y/n): ";
    char big_letters;
    if(cin >>big_letters)
    {
        if(big_letters=='y' || big_letters=='n'){}
        else
        {
            cout <<"Введіть букви y або n" <<endl;
            return 1;
        }
    }
    else
    {
        cout <<"Введіть букви y або n" <<endl;
        return 1;
    }
    cout <<"Чи є спеціальні символи (y/n): ";
    char special_characters;
    if(cin >>special_characters)
    {
        if(special_characters=='y' || special_characters=='n'){}
        else
        {
            cout <<"Введіть букви y або n" <<endl;
            return 1;
        }
    }
    else
    {
        cout <<"Введіть букви y або n" <<endl;
        return 1;
    }
    cout <<endl;
    int number_of_character_types=0;
    int level=0;
    //Враховуємо всі типи символів
    if(numbers=='y')
    {
        number_of_character_types++;
    }
    if(big_letters=='y')
    {
        number_of_character_types++;
    }
    if(special_characters=='y')
    {
        number_of_character_types++;
    }
    //Визначаємо чи пароль проходить мінімальні вимоги
    if(length>=8 && number_of_character_types>=2)
    {
        cout <<"Мінімальні вимоги: ПРОЙДЕНО" <<endl;
    } else
    {
        cout <<"Мінімальні вимоги: НЕ ПРОЙДЕНО" <<endl;
    }
    //Визначаємо рівень надійності пароля
    if(length<6)
    {
        cout <<"Рівень надійності: 1 - Дуже слабкий" <<endl;
        level=1;
    }
    else if(length<8 || number_of_character_types==0)
    {
        cout <<"Рівень надійності: 2 - Слабкий" <<endl;
        level=2;
    }
    else if(number_of_character_types==1)
    {
        cout <<"Рівень надійності: 3 - Середній" <<endl;
        level=3;
    }
    else if(length>=12 && number_of_character_types==3)
    {
        cout <<"Рівень надійності: 5 - Дуже надійний" <<endl;
        level=5;
    }
    else
    {
        cout <<"Рівень надійності: 4 - Надійний" <<endl;
        level=4;
    }
    //Виведення рекомендації для пароля залежно від рівня його надійності
    switch(level)
    {
        case 1:
        {
            cout <<"Пароль надто короткий. Мінімум 8 символів." <<endl;
            break;
        }
        case 2:
        {
            cout <<"Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." <<endl;
            break;
        }
        case 3:
        {
            cout <<"Додайте ще один тип символів або збільште довжину до 12." <<endl;
            break;
        }
        case 4:
        {
            cout <<"Хороший пароль. Для максимуму 12+ символів і всі три типи символів." <<endl;
            break;
        }
        case 5:
        {
            cout <<"Відмінно. Змінювати нічого не потрібно." <<endl;
            break;
        }
    }
    return 0;
}