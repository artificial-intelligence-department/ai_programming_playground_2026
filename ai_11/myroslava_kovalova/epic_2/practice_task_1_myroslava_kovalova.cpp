/* Аналізатор надійності пароля
Ковальова Мирослава
ШІ-11*/

#include <iostream>

using namespace std;

int main(){

    int pas_lenght, char_types = 0, level;
    char pas_numbers, pas_capitals, pas_special;
    bool min_req;

    cout<<"Довжина пароля: ";
    cin>>pas_lenght;
    
    //перевірка чи входить довжина паролю у допустимий діапазон
    if (pas_lenght>64 || pas_lenght<1){
        cout<<"Помилка: довжина мусить бути від 1 до 64."<<endl;
        return 1;
    }

    cout<<"Чи є цифри (y/n): ";
    cin>>pas_numbers;

    cout<<"Чи є великі літери (y/n): ";
    cin>>pas_capitals;
    
    cout<<"Чи є спеціальні символи (y/n): ";
    cin>>pas_special;

    //якщо хоча б одна з змінних "Чи є цифри/великі літери/ спеціальні символи?" не містить y або n, то програма зупиняється та видає помилку
    if (!((pas_numbers == 'y' || pas_numbers == 'n') && (pas_capitals == 'y' || pas_capitals == 'n') && (pas_special == 'y' || pas_special == 'n') )){
        cout<<"Помилка: відповідь має бути або y, або n"<<endl;
        return 1;
    } 

    //рахуємо кількість типів символів
    if (pas_numbers == 'y'){
        char_types ++;
    }
    if (pas_capitals == 'y'){
        char_types ++;
    }
    if (pas_special == 'y'){
        char_types ++;
    }

    //перевірка на мінімальні вимоги, зберігаємо як булеве значення
    if (pas_lenght <8 || char_types<2 ){
        min_req = 0;
    }else{
        min_req = 1;
    }
    if (min_req){
        cout<<"Мінімальні вимоги: ПРОЙДЕНО"<<endl;
    }else{
        cout<<"Мінімальні вимоги: НЕ ПРОЙДЕНО"<<endl;
    }
    
    //блок коду з визначенням рівня надійності
    if (pas_lenght<6){
        level=1;
    } else if (pas_lenght<8 || char_types==0){
        level = 2;
    } else if (char_types==1){
        level = 3;
    } else if (pas_lenght>=12 && char_types == 3){
        level = 5;
    } else{
        level =4;
    }

    
    //надання рекомендацій в залежності від рівня надійності, гілка default для непередбачуваних результатів, вона індикатор помилки коду
    switch(level){
        case 1:
        cout<<"Рівень: "<<level<<" - Дуже слабкий"<<endl;
        cout<<"Рекомендації: Пароль надто короткий. Мінімум 8 символів."<<endl;
        break;
        case 2:
        cout<<"Рівень: "<<level<<" - Слабкий"<<endl;
        cout<<"Рекомендації: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи."<<endl;
        break;
        case 3:
        cout<<"Рівень: "<<level<<" - Середній"<<endl;
        cout<<"Рекомендації: Додайте ще один тип символів або збільште довжину до 12."<<endl;
        break;
        case 4:
        cout<<"Рівень: "<<level<<" - Надійний"<<endl;
        cout<<"Рекомендації: Хороший пароль. Для максимуму 12+ символів і всі три типи символів."<<endl;
        break;
        case 5:
        cout<<"Рівень: "<<level<<" - Дуже надійний"<<endl;
        cout<<"Рекомендації: Відмінно. Змінювати нічого не потрібно."<<endl;
        break;
        default:
        cout<<"Помилка визначення рівня та рекомендацій"<<endl;
    }
    
    if (pas_numbers == 'n' && pas_special == 'n'){
        cout<<"Попередження: пароль тільки з літер підбирається швидше."<<endl;
    }


    return 0;
}