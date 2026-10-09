/*
Аналізатор надійності пароля
Перерва Олександр
ШІ-11
*/
#include <iostream>

using namespace std;

int main() {
    // оголошення змінних
    int pass_length,level,symbtype;
    char is_num, is_upLetter, is_specialChar;
    // ввід pass_length
    cout<<"Довжина пароля: "; cin>>pass_length;
    // перевірка на допустиме значення
    if(pass_length<1 || pass_length>64){
        cout<<"Помилка: довжина мусить бути від 1 до 64."<<endl;
        return 1;
    }
    // ввід is_num
    cout<<"Чи є цифри (y/n): "; cin>>is_num;
    // перевірка на допустиме значення
    if(is_num!='y' && is_num!='n'){
        cout<<"Введіть y або n"<<endl;
        return 1;
    }
    // ввід is_upLetter
    cout<<"Чи є великі літери (y/n): "; cin>>is_upLetter;
    // перевірка на допустиме значення
    if(is_upLetter!='y' && is_upLetter!='n'){
        cout<<"Введіть y або n"<<endl;
        return 1;
    }
    // ввід is_specialChar
    cout<<"Чи є спеціальні символи (y/n): "; cin>>is_specialChar;
    // перевірка на допустиме значення
    if(is_specialChar!='y' && is_specialChar!='n'){
        cout<<"Введіть y або n"<<endl;
        return 1;
    }
    // визначення рівня надійності пароля
    if(pass_length<6){
        level=1;
    } else if(pass_length<8 || symbtype==0){
        level=2;
    } else if(symbtype==1){
        level=3;
    } else if(pass_length>=12 || symbtype==3){
        level=5;
    } else{
        level=4;
    }
    // переврка мінімальних вимог
    if(pass_length>=8 && symbtype>=2){
        cout<<"Мінімальні вимоги: ПРОЙДЕНО"<<endl;
    } else{
        cout<<"Мінімальні вимоги: НЕ ПРОЙДЕНО"<<endl;
    }
    // вивід рівня надійності та рекомендації
    switch(level){
        case 1:
            cout<<"Рівень надійності 1 -Дуже слабкий"<<endl;
            cout<<"Рекомендація: Пароль надто короткий. Мінімум 8 символів."<<endl;
            break;
        case 2:
            cout<<"Рівень надійності 2 - Слабкий"<<endl;
            cout<<"Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи."<<endl;
            break;
        case 3:
            cout<<"Рівень надійності 3 - Середній"<<endl;
            cout<<"Рекомендація: Додайте ще один тип символів або збільште довжину до 12."<<endl;
            break;
        case 4:
            cout<<"Рівень надійності 4 - Надійний"<<endl;
            cout<<"Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів."<<endl;
            break;
        case 5:
            cout<<"Рівень надійності 5 - Дуже надійний"<<endl;
            cout<<"Рекомендація: Відмінно. Змінювати нічого не потрібно."<<endl;
            break;
        default:
            cout<<"Неправильний рівень"<<endl;
            break;

            // ПОПЕРЕДЖЕННЯ 
            //!!!!
    }

    
    return 0;
}