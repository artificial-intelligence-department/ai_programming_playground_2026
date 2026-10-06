/*"Аналізатор надійності пароля"
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
#include <locale>
using namespace std;
int main() {
    setlocale(LC_ALL, "uk_UA");
    int passwordlength;
    char numbers, capital_let, symbols;
    cout<<"Довжина паролю: ";
    cin>>passwordlength;
    //Перевіряємо правильність значення довжини паролю
    if (passwordlength<1 || passwordlength>64){
        cout<<"Помилка: довжина мусить бути від 1 до 64."<<endl;
        return 1;
    }
    cout<<"Чи є цифри(y/n): ";
    cin>>numbers;

    //Перевіряємо правильність вводу значень наявності цифр, спеціальних символів та великих літер
    if (numbers !='y' && numbers !='n'){
        cout<<"Помилка:ведіть дійсне значення."<<endl;
        return 1;
    }
    cout<<"Чи є великі літери(y/n): ";
    cin>>capital_let;
    if (capital_let !='y' && capital_let !='n'){
        cout<<"Помилка:введіть дійсне значення."<<endl;
        return 1;
    }
    cout<<"Чи є спеціальні символи(y/n): ";
    cin>>symbols;
    if (symbols !='y' && symbols !='n'){
        cout<<"Помилка:введіть дійсне значення."<<endl;
        return 1;
    }
    cout<<endl;
    //Задаємо лічильник, який рахує різні типи символів
    int typesCount=0;
    if(numbers=='y')typesCount++;
    if(capital_let=='y')typesCount++;
    if(symbols=='y')typesCount++;

    //Перевірка за мінімальними вимогами
    if (passwordlength>=8 && typesCount>=2){
        cout<<"Мінімальні вимоги: ПРОЙДЕНО"<<endl;
    }
    else{
        cout<<"Мінімальні вимоги: НЕ ПРОЙДЕНО"<<endl;
    }
    //Оголошуємо змінну, яка відповідає за рівень надійності паролю, будемо змінювати її відповідно до умов
    int reliability=0;
    cout<<"Рівень надійності: ";
    if (passwordlength<6){
        reliability=1;
        cout<<reliability<<" - Дуже слабкий"<<endl;
    }
    else if (passwordlength<8 || typesCount==0){
        reliability=2;
        cout<<reliability<<" - Cлабкий"<<endl;
    }
    else if (typesCount==1){
        reliability=3;
        cout<<reliability<<" - Середній"<<endl;
    }
    else if (passwordlength>=12 && typesCount==3){
        reliability=5;
        cout<<reliability<<" - Дуже надійний"<<endl;
    }
    else{
        reliability=4;
        cout<<reliability<<" - Надійний"<<endl;
    }

    cout<<"Рекомендація: ";
    //За допомогаю конструкції switch case виводимо рекомендації залежно від значення змінної, яка відповідає за рівень надійності 
    switch(reliability){
        case 1:
        cout<<"Пароль надто короткий. Мінімум 8 символів."<<endl;
        break;
        case 2:
        cout<<"Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи."<<endl;
        break;
        case 3:
        cout<<"Додайте ще один тип символів або збільште довжину до 12."<<endl;
        break;
        case 4:
        cout<<"Хороший пароль. Для максимуму 12+ символів і всі три типи символів."<<endl;
        break;
        case 5:
        cout<<"Відмінно. Змінювати нічого не потрібно."<<endl;
        break;
        default:
        cout<<"Невідомий рівень."<<endl;
        break;
    }
    //Якщо у паролі немає ні цифр, ні спеціальних символів, виводимо попередження
    if(!(numbers=='y' || symbols=='y')){
        cout<<"Попередження: пароль тільки з літер підбирається швидше."<<endl;
    }
    return 0;
}