/*
Практичне завдання: Аналізатор місячного бюджету
група ШІ-12
Козій Василь Іванович
*/
#include <iostream>
#include <cmath>
#include <array>
#include <iomanip>
using namespace std;
//Функція виводить номери днів в стовпчик і скільки за ці дні було витрат
void show_spending_by_day(double* x, int N)
{
    cout <<right <<setw(10) <<"День     ";
    cout <<setw(20) <<"Витрати, грн" <<endl;
    cout <<fixed <<setprecision(2);
    for(int i=1; i<=N; i++)
    {
        cout <<setw(5) <<i;
        cout <<setw(15) <<x[i-1] <<endl;
    }
}
//Функція шукає максимальне і мінімальне значення витрат
void min_and_max(double* x, int N, double &min_value, double &max_value)
{
    min_value=1000000000;
    max_value=0;
    for(int i=0; i<N; i++)
    {
        if(x[i]>max_value)
        {
            max_value=x[i];
        }
        if(x[i]<min_value)
        {
            min_value=x[i];
        }
    }
}
//Рекурсивна функція шукає сумарну кількість витрат за вказані дні
double sum_spending(double* x, int n, int N)
{
    if(n==N)
    {
        return 0;
    }
    return sum_spending(x, n+1, N)+x[n];
}
//Функція рахує кількість днів, коли були витрати
int days_with_spending(double* x, int N)
{
    int n=0;
    for(int i=0; i<N; i++)
    {
        if(x[i]==0)
        {
            continue;
        }
        n++;
    }
    return n;
}
//Функція рахує залишок або перевитрату
double remainder_spending(double budget, double* x, int N)
{
    double sum=0;
    for(int i=0; i<N; i++)
    {
        sum+=x[i];
    }
    return budget-sum;
}
//Рахує середню кількість витрачених грошей за кожен день, коли були витрати
double avarage_spending(double* x, int N)
{
    double sum=0;
    for(int i=0; i<N; i++)
    {
        if(x[i]==0)
        {
            continue;
        }
        sum+=x[i];
    }
    return sum/days_with_spending(x, N);
}
//Функція визначає день коли сумарні витрати перевищили бюджет, якщо такого немає, то видає скільки грошей залишилося
double spending_run_up_day(double budget, double* x, int N)
{
    int i=0;
    double sum=0;
    while(i<N)
    {
        sum+=x[i];
        if(sum>budget)
        {
            return int(i+1);
            break;
        }
        i++;
        if(i==N)
        {
            return budget-sum;
            break;
        }
    }
}
//Функція визначає скільки сумарно було витрачено грошей від початку обліку до дня коли витрати перевищили бюджет, або коли облік закінчився, якщо витрати не перевищили бюджет
double spending_run_up(double budget, double* x, int N)
{
    double sum=0;
    for(int i=0; i<spending_run_up_day(budget, x, N); i++)
    {
        sum+=x[i];
    }
    return sum;
}
//Функція виводить номери днів коли витрати перевищили ліміт(ліміт питає, ліміт за замовчуванням 1000 грн, якщо ввдено 0)
void days_where_limit_exceeded(double* x, int N)
{
    limit1:
    double limit;
    int number=0;
    cout<<"Денний ліміт (грн, 0 = за замовчуванням): ";
    if(cin >>limit){}
    else{
        cout <<"Будь ласка, тут введіть число від 0 і більше" <<endl; 
        cin.clear();
        while(cin.get()!='\n');
        limit=0;
        goto limit1;
    }
    if(limit<0){
        cout <<"Будь ласка, тут введіть число від 0 і більше" <<endl; 
        goto limit1;
    }
    if(limit==0)
    {
        limit=1000;
    }
    cout <<fixed <<setprecision(2);
    cout <<"Ліміт: " <<limit <<" грн" <<endl;
    for(int i=0; i<N; i++)
    {
        if(x[i]>limit)
        {
            cout <<right <<setw(5) <<"день " <<setw(3) <<i+1 <<": " <<setw(5) <<x[i] <<" грн" <<endl;
            number++;
        }
    }
    cout <<"Разом днів з перевищенням: " <<number <<endl;
}
//Функція сортує масив
double* sort(double* x, int N)
{
    double* y = new double[N];
    double* z = new double[N];
    for(int i=0; i<N; i++)
    {
        y[i]=x[i];
        z[i]=0;
    }
    double m;
    int index;
    for(int i=0; i<N; i++)
    {
        m=0;
        index=0;
        for(int j=0; j<N; j++)
        {
            if(y[j]>m)
            {
                m=y[j];
                index=j;
            }
        }
        z[i]=m;
        y[index]=-1;
    }
    return z;
}
//Функція видає топ-3 найбільші витрати за час обліку
void top_3_spendings(double* x, int N)
{
    cout <<fixed <<setprecision(2);
    cout <<"Топ-3 витрат: ";
    cout <<sort(x, N)[0] <<", ";
    cout <<sort(x, N)[1] <<", ";
    cout <<sort(x, N)[2] <<" грн" <<endl;
}
int main()
{
    start:
    //Введення всіх змінних і перевірки чи введені правильні дані
    double min_value=0;
    double max_value=0;
    double budget;
    cout <<"Бюджет на місяць (грн): ";
    if(cin >>budget){}
    else
    {
        cout <<"Будь ласка, тут введіть число більше за нуль" <<endl;
        cin.clear();
        while(cin.get()!='\n');
        goto start;
    }
    if(budget<=0)
    {
        cout <<"Будь ласка, тут введіть число більше за нуль" <<endl;
        cin.clear();
        while(cin.get()!='\n');
        goto start;
    }
    int N;
    cout <<"Кількість днів обліку: ";
    if(cin >>N){}
    else
    {
        cout <<"Будь ласка, тут введіть ціле число від 1 до 31" <<endl;
        cin.clear();
        while(cin.get()!='\n');
        goto start;
    }
    if(N<=0 || N>31)
    {
        cout <<"Будь ласка, тут введіть ціле число від 1 до 31" <<endl;
        cin.clear();
        while(cin.get()!='\n');
        goto start;
    }
    cout <<"Витрати по днях (грн): ";
    //Створення масиву і введення в нього даних(також перевірка даних)
    double* spending= new double[N];
    double day_spending;
    int choice;
    double x;
    int q=0;
    for(int i=0; i<N; i++){spending[i]=0;}
    for(int i=0; i<N; i++)
    {
        if(cin >>x)
        {
            q++;
            spending[i]=x;
            if (cin.peek()=='\n' && q<N) {
                cout <<"Будь ласка, тут введіть " <<N <<" чисел від 0 і більше" <<endl;
                goto start;
                break;
            }
            continue;
        }
        {
            cout <<"Будь ласка, тут введіть " <<N <<" чисел від 0 і більше" <<endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto start;
            break;
        }
    }
    choice1:
    choice=0;
    do
    {
        //Меню вибору дії
        cout <<"Оберіть дію" <<endl;
        cout <<"1-Показати витрати по днях" <<endl;
        cout <<"2-Статистика витрат" <<endl;
        cout <<"3-Дні з перевищенням денного ліміту" <<endl;
        cout <<"4-Три найдорожчі дні" <<endl;
        cout <<"0-Вийти" <<endl;
        cout <<"Виберіть дію: ";
        //Перевірка чи введено один із можливих виборів дії
        if(cin >>choice){}
        else
        {
            cout <<"Будь ласка, тут введіть ціле число від 0 до 4" <<endl;
            cin.clear();
            while(cin.get()!='\n');
            goto choice1;
        }
        switch(choice)
        {
            case 1: {show_spending_by_day(spending, N); break;}
            case 2:
            {
                min_and_max(spending, N, min_value, max_value);
                cout <<fixed <<setprecision(2);
                cout <<"Мінімальні витрати за день:    ";
                cout <<right <<setw(6) <<min_value <<" грн" <<endl;
                cout <<"Максимальні витрати за день:  ";
                cout <<right <<setw(6) <<max_value <<" грн" <<endl;
                cout <<"Сумарні витрати:              " <<sum_spending(spending, 0, N) <<" грн" <<endl;
                if(remainder_spending(budget, spending, N)>0)
                {
                    cout <<"Залишок бюджету:              ";
                    cout <<right <<setw(6) <<remainder_spending(budget, spending, N) <<" грн" <<endl;
                }
                else
                {
                    cout <<"Перевитрата понад бюджет:     ";
                    cout <<right <<setw(6) <<abs(remainder_spending(budget, spending, N)) <<" грн" <<endl;
                }
                cout <<"Днів з покупками:             ";
                cout <<right <<setw(6) <<days_with_spending(spending, N) <<endl;
                cout <<"Середні витрати за такий день: ";
                cout <<right <<setw(6) <<avarage_spending(spending, N) <<" грн" <<endl;
                if(sum_spending(spending, 0, N)>budget)
                {
                    cout <<"Бюджет вичерпано на дні " <<int(spending_run_up_day(budget, spending, N)) <<", накопичено " <<spending_run_up(budget, spending, N) <<" грн" <<endl;
                    break;
                }
                else
                {
                    cout <<fixed <<setprecision(2) <<"Бюджет не вичерпано, ось кількість залишку грошей з бюджету: " <<spending_run_up_day(budget, spending, N) <<" грн" <<endl;
                }
            }
            case 3: {days_where_limit_exceeded(spending, N); break;}
            case 4: {top_3_spendings(spending, N); break;}
            default : 
            {
                if(choice!=0)
                {
                    cout <<"Будь ласка, тут введіть ціле число від 0 до 4" <<endl;
                    cin.clear();
                    while(cin.get()!='\n');
                    goto choice1;
                }
                break;
            }
        }
    } while(choice!=0);

}