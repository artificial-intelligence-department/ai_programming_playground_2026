/*
    Аналізатор надійності пароля
    Королюк Соломія
    СШІ-13
*/

#include <iostream>
#include <string>

using namespace std;

int main(){

    int c = 0; // Змінна для підрахунку кількості критеріїв, які виконуються

    // Введення довжини пароля та перевірка на коректність

    int password_length;
    cout << "Введіть довжину пароля: ";
    cin >> password_length;
    
    if (password_length < 1 or password_length > 64){
        cout << "Довжина пароля повинна бути від 1 до 64 символів!" << endl;
        return 1;
    }


    //Введення інформації про наявність цифр у паролі та перевірка на коректність

    string ans1;
    cout << "Чи є цифри (y/n): ";
    cin >> ans1;

    if (!(ans1 == "y" or ans1 == "n")){ // логічне заперечення: якщо введено не "y" і не "n"
        cout << "Введено некоректне значення!" << endl;
        return 1;
    }


    //Введення інформації про наявність великих літер у паролі та перевірка на коректність

    string ans2;
    cout << "Чи є великі літери (y/n): ";
    cin >> ans2;

    if (!(ans2 == "y" or ans2 == "n")){
        cout << "Введено некоректне значення!" << endl;
        return 1;
    }


    //Введення інформації про наявність спеціальних символів у паролі та перевірка на коректність

    string ans3;
    cout << "Чи є спеціальні символи (y/n): ";
    cin >> ans3;

    if (!(ans3 == "y" or ans3 == "n")){
        cout << "Введено некоректне значення!" << endl;
        return 1;
    }


    if (ans1 == "y") c++; // якщо є цифри, збільшуємо лічильник на 1
    if (ans2 == "y") c++; // якщо є великі літери, збільшуємо лічильник на 1
    if (ans3 == "y") c++; // якщо є спеціальні символи, збільшуємо лічильник на 1


    // Мінімальні вимоги (if else)
    
    bool min_requirements;

    if (password_length >= 8 and c >= 2){
        min_requirements = true;
    } else {
        min_requirements = false;
    }


    // Рівень надійності пароля (if, else if)

    int strength_level;

    if (strength_level < 6){
        strength_level = 1; // дуже слабкий
    }

    else if (strength_level < 8 or c == 0){
        strength_level = 2; // слабкий
    }

    else if (c == 1){
        strength_level = 3; // середній
    }

    else if (password_length >= 12 and c == 3){
        strength_level = 5; // дуже надійний 
    }

    else {
        strength_level = 4; // надійний
    }

    cout << "Мінімальні вимоги: " << (min_requirements ? "ПРОЙДЕНО" : "НЕ ПРОЙДЕНО") << endl;
    cout << "Рівень надійності: " << strength_level << endl;


    // Рекомендація з використанням switch case

    switch (strength_level){
        case 1: cout << "Пароль надто короткий. Мінімум 8 символів." << endl; break;
        case 2: cout << "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи." << endl; break;
        case 3: cout << "Додайте ще один тип символів (цифри, великі літери або спеціальні символи)." << endl; break;
        case 4: cout << "Хороший пароль. Для максимуму 12+ символів і всі три типи символів." << endl; break;
        case 5: cout << "Відмінно. Змінювати нічого не потрібно." << endl; break;
    }

    return 0;
}