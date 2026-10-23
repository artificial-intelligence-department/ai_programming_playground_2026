/*
Назва задачі: Аналізатор місячного бюджету
Автор: Петро Стецюк
Група: ШІ-12
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Функція для виведення витрат по днях
void punct1(double spending[], int days)
{
    cout<<"День          Витрати, грн"<<endl;
    for(int i=0;i<days;i++)
    {
        cout<<fixed<<i+1<<setw(25)<<setprecision(2)<<spending[i]<<endl;
    }
}

// Функція для знаходження мінімальних та максимальних витрат
void minmax(double spending[], int days, double &mins, double &maxs)
{
    mins = spending[0];
    maxs = spending[0];
    for(int i=1;i<days;i++)
    {
        if(spending[i]<mins)
            mins = spending[i];
        if(spending[i]>maxs)
            maxs = spending[i];
    }
    cout<<"============ Статистика витрат ============="<<endl;
    cout<<fixed<<"Мінімальні витрати за день: "<<setw(11)<<setprecision(2)<<mins<<" грн"<<endl;
    cout<<fixed<<"Максимальні витрати за день: "<<setw(10)<<setprecision(2)<<maxs<<" грн"<<endl;
}

// Функція для обчислення сумарних витрат за місяць
double summary(double spending[], int days,int i)
{   
    if(i==days) return 0;
    return spending[i] + summary(spending, days, i + 1);
}

// Функція для обчислення різниці між бюджетом та сумарними витратами
void budgetdif(double budget, double sum)
{
    double dif =abs(budget-sum);
    if(sum>budget) cout<<"Перевитрата понад бюджет:"<<fixed<<setw(14)<<dif<<" грн"<<endl;//cout<<"Залишок бюджету:"<<setw(23)<<dif<<" грн"<<endl;
}

// Функція для обчислення кількості днів з витратами та середніх витрат за день
void dayswithspend(double spending[], int days, double sum)
{
    int dayswithspend=0;
    double average;
    for(int i=0;i<days;i++)
    {
        if(spending[i]>0)dayswithspend++;
         else continue;
    }
    average=sum/days;
    cout<<"Днів з покупками:"<<setw(22)<<dayswithspend<<endl;
    cout<<"Середні витрати за такий день:"<<fixed<<setw(9)<<setprecision(2)<<average<<" грн"<<endl;
}

// Функція для обчислення днів, коли витрати перевищили бюджет та виведення залишку бюджету, якщо витрати не перевищили бюджет
void budgetout(double spending[], int days, double budget)
{
    double total=0;
    int i=0;
    while(i!=-1)
    {
        total+=spending[i];
        if(total>budget){cout<<"Бюджет вичерпано на дні "<<i+1<<", накопичено "<<total<<" грн"<<endl;break;}
         else if(i==days-1){cout<<"Залишок бюджету:"<<setw(23)<<budget-total<<" грн"<<endl;break;}
            else i++;
    }
}

// Функція для обчислення днів, коли витрати перевищили денний ліміт
void limitout(double spending[], int days, double limit=1000)
{
    cout<<"Ліміт:"<<fixed<<setw(8)<<setprecision(2)<<limit<<" грн"<<endl;
    int countdays=0;
    for(int i=0;i<days;i++)
    {
        if(spending[i]>limit) {cout<<"  день "<<fixed<<setprecision(2)<<i+1<<":"<<setw(8)<<spending[i]<<" грн"<<endl;countdays++;}
    }
    cout<<"Разом днів з перевищенням: "<<countdays<<endl;
}

// Функція для сортування витрат за спаданням та виведення трьох найбільших витрат
void sort(double spending[], int days)
{
    double copy[100],temp;
    for(int i=0;i<days;i++)
    {
        copy[i]=spending[i];
    }
    for(int i=0;i<days-1;i++)
    {
        for(int j=i+1;j<days;j++)
        {
            if(copy[i]<copy[j])
            {
                temp=copy[i];
                copy[i]=copy[j];
                copy[j]=temp;
            }
        }
    }
    if(days<3)
    {
        cout<<"Топ-"<<days<<" витрат: ";
        for(int i=0;i<days;i++)
        {
            if(i!=0) cout<<", ";
            cout<<fixed<<setprecision(2)<<copy[i];
        }
    }
     else
     {
        cout<<"Топ-3 витрат: ";
         for(int i=0;i<3;i++)
         {
            if(i!=0) cout<<", ";
             cout<<fixed<<setprecision(2)<<copy[i];
         }
     }
     cout<<" грн"<<endl;
}
int main()
{
    double budget,spending[100],mins,maxs,sum,limit; // ініціалізація змінних: бюджет, витрати по днях, мінімальні та максимальні витрати, сумарні витрати, денний ліміт
    int days,choice,i=1; // ініціалізація змінних: кількість днів обліку, вибір операції, змінна для виходу з циклу

    // Введення бюджету та перевірка на коректність введення
    input_budget:
    cout << "Бюджет на місяць (грн): ";
    cin>>budget;
    if(cin.fail()||budget<0)
    {
        cout<<"Помилка введення! Спробуйте ще раз.(Бюджет повинен бути додатним числом)"<<endl;
        cin.clear();
        cin.ignore(10000,'\n');
        goto input_budget;
    }
    input_days:
    cout<<"Кількість днів обліку: ";
    cin>>days;
    if(cin.fail()||days<=0||days>31)
    {
        cout<<"Помилка введення! Спробуйте ще раз.(Кількість днів повинна бути додатним числом від 1 до 31)"<<endl;
        cin.clear();
        cin.ignore(10000,'\n');
        goto input_days;
    }
    input_spending:
    cout<<"Витрати по днях (грн): ";
    for(int i=0;i<days;i++)
    {
        cin>>spending[i];
        if(cin.fail()||spending[i]<0)
        {
            cout<<"Помилка введення! Спробуйте ще раз.(Витрати повинні бути додатним числом)"<<endl;
            cin.clear();
            cin.ignore(10000,'\n');
            goto input_spending;
            break;
        }
    }

    // Присвоєння значення сумарних витрат за місяць
    sum = summary(spending,days,0);

    // Блок меню для вибору операцій
    do
    {
        cout<<"======== Меню ========"<<endl;
        cout<<"Пункт    Операція"<<endl;
        cout<<"1        Показати витрати по днях"<<endl;
        cout<<"2        Статистика витрат"<<endl;
        cout<<"3        Дні з перевищенням денного ліміту"<<endl;
        cout<<"4        Три найдорожчі дні"<<endl;
        cout<<"0        Вийти"<<endl;
        cin>>choice;
        if(cin.fail()||choice<0) 
            {
                cin.clear();
                cin.ignore(10000,'\n');
                cout<<"Помилка введення! Спробуйте ще раз."<<endl;
                continue;
            }
        // Виведення результатів відповідно до вибору користувача
        switch(choice)
        {
            case 1:
            cout<<"====== Витрати по днях ======"<<endl;
            punct1(spending,days); // виклик функції для виведення витрат по днях
            break;
            case 2:
            minmax(spending,days,mins,maxs);   
            cout<<"Сумарні витрати:"<<setw(23)<<setprecision(2)<<sum<<" грн"<<endl; 

            // Виклик функцій для виведення обчислення різниці між бюджетом та сумарними витратами, кількість днів з витратами, коли перевищено бюджет і залишок
            budgetdif(budget,sum);
            dayswithspend(spending,days,sum);
            budgetout(spending,days,budget);
            break;
            case 3:
            cout<<"====== Дні з перевищенням денного ліміту ======"<<endl;
            // Перевірка на коректність введеня та виклик функції для перевірки днів перевищення ліміту
            input_limit:
            cout<<"Денний ліміт (грн, 0 = за замовчуванням): ";
            cin>>limit;
            if(cin.fail()||limit<0) 
            {
                cin.clear();
                cin.ignore(10000,'\n');
                cout<<"Помилка введення! Спробуйте ще раз.( Ліміт повинен бути додатним числом)"<<endl;
                goto input_limit;
            }
            if(limit==0)limitout(spending,days);
             else limitout(spending,days,limit);
            break;
            case 4:
            // виклик функції для виводу найбільших витрат
            sort(spending,days);
            break;
            case 0:
            i=0;
            break;
            default:
                cout<<"Помилка введення! Спробуйте ще раз."<<endl;
                break;
        }
    }while(i!=0);
    return 0;
}