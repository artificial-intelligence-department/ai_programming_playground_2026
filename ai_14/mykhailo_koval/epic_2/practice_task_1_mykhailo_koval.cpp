/*
Task: Аналізатор надійності пароля
Name: Mykhailo Koval
Group: AI-14 
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    //Змінні для параметрів пароля
    int lenght; 
    char digits; 
    char caps; 
    char specials; 
    //змінні для кількості типів символів та рівня надійності пароля
    int symbol_types = 0; 
    int password_level; 
    //змінні для виводу рівня надійності та рекомендацій
    string passwordLevel; 
    string recomendations; 
    
    //Введення даних та валідація
    cout << "Довжина пароля: ";
    cin >> lenght;
    if (lenght < 1 && lenght > 64){
        cout << "Помилка, введіть правильне значення" << '\n';
        return 1;
    }

    cout << "Чи є цифри: ";
    cin >> digits;
    if (digits != 'y' && digits != 'n'){
        cout << "Помилка, введіть значення y(yes) або n(no)" << '\n';
        return 1;
    } 

    cout << "Чи є великі літери: ";
    cin >> caps;
    if (caps != 'y' && caps != 'n'){
        cout << "Помилка, введіть значення y(yes) або n(no)" << '\n';
        return 1;
    } 

    cout << "Чи є спецііальні символи : ";
    cin >> specials;
    if (specials != 'y' && specials != 'n'){
        cout << "Помилка, введіть значення y(yes) або n(no)" << '\n';
        return 1;
    }

    if (digits == 'y'){
        symbol_types++;
    }
    if (caps == 'y'){
        symbol_types++;
    }
    if (specials == 'y'){
        symbol_types++;
    }


    //Перевірка мінімальних вимог
    if (lenght >= 8 && symbol_types >= 2){
        cout << "Мінімальні вимоги: ПРОЙДЕНО" << '\n';
    } else {
        cout << "Мінімальні вимоги: НЕ ПРОЙДЕНО" << '\n';
    }

    //Визначення рівня надійності пароля
    if (lenght < 6){
        password_level = 1;
        passwordLevel = "Дуже слабкий";
    } else if (lenght < 8 || symbol_types == 0){
        password_level = 2;
        passwordLevel = "Слабкий";
    } else if (symbol_types == 1){
        password_level = 3;
        passwordLevel = "Середній";
    } else if (lenght >= 12 && symbol_types == 3){
        password_level = 5;
        passwordLevel = "Дуже надійний";
    } else {
        password_level = 4;
        passwordLevel = "Надійний";
    }

    //Визначення рекоменацій для даних рівнів надійності пароля
    switch (password_level){
        case 1:
        recomendations = "Пароль надто короткий. Мінімум 8 символів.";
        break;
        case 2:
        recomendations = "Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи.";
        break;
        case 3:
        recomendations = "Додайте ще один тип символів або збільште довжину до 12.";
        break;
        case 4: 
        recomendations = "Хороший пароль. Для максимуму 12+ символів і всі три типи символів.";
        break;
        case 5:
        recomendations = "Відмінно. Змінювати нічого не потрібно.";
        break;
        default:
        recomendations = "Помилка";
    }

    //Вивід рівня надійності та рекомендацій
    cout << "Рівень надійності: " << password_level << " - " << passwordLevel << '\n';
    cout << "Рекомендації: " << recomendations << '\n';
    if (digits == 'n' && specials == 'n'){
        cout << "Попередження: пароль тільки з літер підбирається швидше." << '\n';
    }

    return 0; 
    
}