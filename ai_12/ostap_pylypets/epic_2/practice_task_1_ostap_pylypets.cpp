/*Практичне завдання 1
Пилипець Остап
Ші-12
*/
#include <iostream>
using namespace std;
int main()
{
    int passwordLength, passScore, allSymbols = 0;
    char simbols, bigLetter, numbers;
    //Просимо довжину пароля та перевяряємо чи вона в межах від 1 до 64 символів
    cout << "Введіть довжину пароля: ";
    cin >> passwordLength;
    if (passwordLength < 1 || passwordLength > 64)
    {
        cout << "Довжина пароля повинна бути від 1 до 64 символів. Введіть дійне значення. \n";
        return 1;
    }
    //наступні 3 блоки перевіряємо чи є потрібні типи символів у паролі та рахуємо їх кількість
    cout << "У вашому паролі є символи?: ";
    cin >> simbols;
    if (simbols != 'y' && simbols != 'n'){
        cout << "Введіть дійсне значення (y/n).\n";
        return 1;
    }
    if (simbols == 'y') allSymbols ++;
    cout << "У вашому паролі є великі літери?: ";
    cin >> bigLetter;
    if (bigLetter != 'y' && bigLetter != 'n'){
        cout << "Введіть дійсне значення (y/n).\n";
        return 1;
    }
    if (bigLetter == 'y') allSymbols ++;
    cout << "У вашому паролі є числа?: ";
    cin >> numbers;
    if (numbers != 'y' && numbers != 'n'){
        cout << "Введіть дійсне значення (y/n).\n";
        return 1;
    }
    if (numbers == 'y') allSymbols ++;
    
    //зігдно з умововю заввдання визначаємо рівень надійності
    if (passwordLength < 6) passScore = 1;
    else if (passwordLength < 8 || allSymbols== 0)passScore = 2;
    else if (allSymbols == 1) passScore = 3;
    else if (passwordLength >= 12 && allSymbols == 3) passScore = 5;
    else passScore = 4;

    //Вивидиом чи пройдено мінімальні вимоги
    if (passScore <= 3) cout <<"Мінімальні вимоги не пройдено\n";
    else cout <<"Мінімальні вимоги пройдено\n";
    //за допомогою switch case відповідно до рівня виводимо рекомендації
    cout << "Рекомендація: ";
    switch(passScore){
        case 1:
            cout << "Рівень надійності: 1 Дуже слабкий\n";
            cout << "Ваш пароль надто короткий. Ввеідть мінімум 8 символів.\n";
            break;
        case 2:
            cout << "Рівень надійності: 2 Слабкий\n";   
            cout << "Збільште довжину до 8+ символів або додайте цифри, великі літери або символи.\n";
            break;
        case 3:
            cout << "Рівень надійності: 3 Середній\n";
            cout << "додайте ще один тип символів або збільште довжину до 12\n";
            break;
        case 4:
            cout << "Рівень надійності: 4 Надійний\n";
            cout << "Хороший пароль. Для максимуму потрібно 12+ символів і всі три типи символів.\n";
            break;
        case 5:
            cout << "Рівень надійності: 5 Дуже надійний\n";
            cout << "Супер, нічого не потрібно!\n";
            break;
        default:
            cout << "Помилка визначення рівня";
            break;
    }
    return 0;
}