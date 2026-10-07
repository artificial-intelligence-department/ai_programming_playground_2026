/*
    Задача: Аналізатор надійності пароля
    Автор: Стецюк Петро
    Група: ШІ-12
*/
#include <iostream>

using namespace std;

int main()
{
    // Ініціалізація змінних
    int passlength,types=0,level=0; // Довжина пароля, кількість типів символів, рівень надійності
    char Number, Bigletter,Special; // Чи є цифри, великі літери, спеціальні символи
    bool Minrec=0, Warning =0; // Чи пройдені мінімальні вимоги, чи є попередження

    // блок введення даних та валідації
    cout<<"Довжина пароля: ";
    cin>>passlength;
    if(!cin||passlength<1||passlength>64)
    {
        cout<<"Помилка: довжина мусить бути від 1 до 64"<<endl;
        return 1;
    }
    cout<<"Чи є цифри (y/n): ";
    cin>>Number;
    if(!cin||Number!='n'&&Number!='y')
    {
        cout<<"Помилка: введіть y або n!"<<endl;
        return 1;
    }
    cout<<"Чи є великі літери (y/n): ";
    cin>>Bigletter;
    if(!cin||Bigletter!='n'&&Bigletter!='y')
    {
        cout<<"Помилка: введіть y або n!"<<endl;
        return 1;
    }
    cout<<"Чи є спеціальні символи (y/n): ";
    cin>>Special;
    if(!cin||Special!='n'&&Special!='y')
    {
        cout<<"Помилка: введіть y або n!"<<endl;
        return 1;
    }

    // обчислення кількості типів символів які є в паролі
    if(Number == 'y') types++;
    if(Bigletter == 'y') types++;
    if(Special == 'y') types++;

    // обчислення мінімальних вимог
    if(passlength>=8&&types>=2)Minrec = 1;

    // обчислення чи потрібне попередження
    if(Number == 'n'&&Bigletter=='y'&&Special=='n')Warning = 1;
     else if(Number == 'n'&&Bigletter=='n'&&Special=='n')Warning = 1;

    // обчислення рівня надійності
    if(passlength<6)level=1;
     else if(passlength<8||types==0)level=2;
      else if(types==1)level=3;
       else if(passlength>=12&&types==3)level=5;

    // вивід результатів
    cout<<"Мінімальні вимоги: ";
    if(Minrec==1)cout<<"ПРОЙДЕНО"<<endl;
     else cout<<"НЕ ПРОЙДЕНО"<<endl;

    // вивід рівня надійності та рекомендацій 
    switch (level)
    {
    case 1:
        cout<<"Рівень надійності: 1 - Дуже слабкий"<<endl;
        cout<<"Рекомендація: Пароль надто короткий. Мінімум 8 символів."<<endl;
        break;
    case 2:
        cout<<"Рівень надійності: 2 - Cлабкий"<<endl;
        cout<<"Рекомендація: Збільште довжину до 8+ символів і додайте цифри, великі літери або спеціальні символи."<<endl;
        break;
    case 3:
        cout<<"Рівень надійності: 3 - Середній"<<endl;
        cout<<"Рекомендація: Пароль надто короткий. Мінімум 8 символів."<<endl;
        break;
    case 5:
        cout<<"Рівень надійності: 5 - Дуже надійний"<<endl;
        cout<<"Рекомендація: Відмінно. Змінювати нічого не потрібно."<<endl;
        break;
    
    default:
        cout<<"Рівень надійності: 4 - Надійний"<<endl;
        cout<<"Рекомендація: Хороший пароль. Для максимуму 12+ символів і всі три типи символів."<<endl;
        break;
    }
    // Перевірка чи потрібно виводити попередження
    if(Warning==1)
    {
        cout<<"Попередження: пароль тільки з літер підбирається швидше."<<endl;
    }
    return 0;
}
