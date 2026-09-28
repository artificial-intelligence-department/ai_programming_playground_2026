/*Аналізатор надійності пароля, Стехнович Андрій, студент ШІ-11*/
#include <iostream>
using namespace std;
int main(){
    //Ввід даних
    int password_length;
    cout << "Введіть довжину пароля: "<<endl;
    cin >> password_length;
    char digit;
    cout << "Чи є цифри?(y/n)"<<endl;
    cin >> digit;
    char capital;
    cout << "Чи є великі літери?(y/n)"<<endl;
    cin >> capital;
    char special;
    cout << "Чи є спеціальні символи?(y/n)"<<endl;
    cin >> special;
    //Перевірка валідності даних
    if (cin.fail() or password_length<1 or password_length>64) {
        cout << "Ви ввели неправильне значення. Довжина - ціле число від 1 до 64." <<endl;
        return 1;
    }
    if (digit!='y' and digit!='n') {
        cout << "Ви ввели неправильне значення наявності цифр. Введіть y чи n."<<endl;
        return 1;
    }
    if (capital!='y' and capital!='n') {
        cout << "Ви ввели неправильне значення наявності великих літер. Введіть y чи n."<<endl;
        return 1;
    }
    if (special!='y' and special!='n') {
        cout << "Ви ввели неправильне значення наявності спеціальних символів. Введіть y чи n."<<endl;
        return 1;
    }
    //Підрахунок кільксті типів символів
    int type_quantity = 0;
    if (digit=='y') {
        type_quantity++;
    }
    if (capital=='y') {
        type_quantity++;
    }
    if (special=='y') {
        type_quantity++;
    }
    //Перевірка мінімальних вимог
    bool minimum_requirements;
    if (password_length>=8 and type_quantity>=2) {
        minimum_requirements = true;
    } else {
        minimum_requirements = false;
    }
    //Визначення рівня захищеності пароля
    int level;
    string comment;
    if (password_length < 6) {
    level = 1;
    comment = "Дуже слабкий";
    } else if (password_length < 8 || type_quantity == 0) {
        level = 2;
        comment = "Слабкий";
    } else if (type_quantity == 1) {
        level = 3;
        comment = "Середній";
    } else if (password_length >= 12 && type_quantity == 3) {
        level = 5;
        comment = "Дуже надійний";
    } else {
        level = 4;
        comment = "Надійний";
    }
    if (!minimum_requirements) {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО"<<endl;
    } else {
        cout << "Мінімальні вимоги: ПРОЙДЕНО"<<endl;
    }
    cout << "Рівень надійності: "<<level<< " - "<<comment<<endl;
    //Визначення виду рекомендації
    string recommendation;
    switch (level)
    {
    case 1:
        recommendation = "Пароль надто короткий. Мінімум 8 символів.";
        break;
    case 2:
        recommendation = "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.";
        break;
    case 3:
        recommendation = "Додайте ще один тип символів або збільште довжину до 12.";
        break;
    case 4:
        recommendation = "Хороший пароль. Для максимуму 12+ символів і всі три типи символів.";
        break;
    case 5:
        recommendation = "Відмінно. Змінювати нічого не потрібно.";
        break;
    default:
        recommendation = "default";
        break;
    }
    cout<<"Рекомендація: "<<recommendation<<endl;
    //Перевірка чи потрібно попередження
    if (digit=='n' && special == 'n'){
        cout<<"Попередження: пароль тільки з літер підбирається швидше."<<endl;
    }
}