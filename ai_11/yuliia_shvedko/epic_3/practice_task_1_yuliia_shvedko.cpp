/*Аналізатор місячного бюджету
Група: ШІ-11
Автор: Юлія Шведько*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

void dailySpend(int n, double arr[]);
void minMax(int n, double arr[], double &min, double &max);
double sum(double arr[], int n);
void limits(int n, double arr[], int d, double limit = 1000);
void sort(double arr[], int n);

int main()
{
    double budget; // бюджет на місяць
    int N; // кількість днів обліку
    double spending[100]; // витрати по днях
    double spending2[100]; // копія масиву spending 
    int f; // номер пункту меню
    double min; // мінімальне значення
    double max; // максимальне значення
    int days = 0; // кількість днів з покупками
    int day = 0; // день на якому вичерпано бюджет
    double avg; // середнє значення витрачених коштів за дні з покупками
    double sum2 = 0; // скільки витрачено на момент перевищення ліміту
    int d = 0; // кількість днів з превищенням ліміту
    double limit; // ліміт на день
    int n = 0; // використовувалась в циклі який шукає день коли перевищено ліміт 

    cout << "Бюджет на місяць (грн): "; // задання бюджету
    cin >> budget;
    if(budget <= 0 || cin.fail()) // перевірка на коректні значення
    {
        cout << "Введено некоректне значення, бюджет має бути числом більше 0!" << endl;
        return 1;
    }
    cout << "Кількість днів обліку: "; // задання кількості днів
    cin >> N;
    if(N <= 0 || N > 31 || cin.fail()) // перевірка на коректні значення
    {
        cout << "Введено некоректне значення, кількість днів має бути від 0 до 31!" << endl;
        return 1;
    }
    cout << "Витрати по днях (грн): "; // задання витрат по днях
    for (int i = 0; i < N; i++)
    {
        cin >> spending[i];
        if(spending[i] < 0 || cin.fail()) // перевірка на коректні значення
    {
        cout << "Введено некоректне значення, витрати за день мають бути 0 або більше!" << endl;
        return 1;
    }
    }
    for (int i = 0; i < N; i++) // копіювання масиву spending
    {
        spending2[i] = spending[i];
    }
    cout << endl;



    do 
    {
        menu: // мітка для goto

        cout << "Меню: " << endl;
        cout << "1 - показати витрати по днях" << endl;
        cout << "2 - статистика витрат" << endl;
        cout << "3 - дні з перевищенням денного ліміту" << endl;
        cout << "4 - три найдорожчі дні" << endl;
        cout << "0 - вийти" << endl;
        cout << endl;

        cout << "Ваш вибір: "; // вибір пункту меню
        cin >> f;
        if(cin.fail())
    {
        cin.clear();
        cin.ignore();
        cout << "Введіть число!" << endl;
        goto menu;
    }

        switch(f)
        {
            case 1:
            cout << endl;
            cout << fixed << setprecision(2);
            dailySpend(N, spending); // виводить таблицю витрат по днях
            cout << endl;
            break;

            case 2:
            cout << endl;
            cout << fixed << setprecision(2);

            minMax(N, spending, min, max);
            cout << "Мінімальні витрати за день: " << min << " грн" << endl;
            cout << "Максимальні витрати за день: " << max << " грн" << endl;
            cout << "Сумарні витрати: " << sum(spending, N) << " грн" << endl;
            if(sum(spending, N) > budget) // обрахунок залишку або перевитрати
            cout << "Перевитрата понад бюджет: " << abs(budget - sum(spending, N)) << " грн" << endl;
            else
            cout << "Залишок бюджету: " << budget - sum(spending, N) << " грн" << endl;

            for(int i = 0; i < N; i++) // обрахунок кількості днів з покупками
            {
                if(spending[i] == 0) continue;
                days++;
            }

            cout << "Днів з покупками: " << days << endl;

            if(days == 0) // обрахунок середнього значення, якщо це можливо
            cout << "Днів з покупками було 0, порахувати середні витрати за такий день неможливо!" << endl;
            else
            {
                avg = sum(spending, N)/days;
                cout << "Середні витрати за такий день: " << avg << " грн" << endl;
            }

            while(day <= N) // обраховує коли бюджет вичерпано та скільки накопичено на цей момент
            {
                sum2 += spending[n];
                day++;
                n++;
                if (sum2 > budget) break;
            }

            if (sum2 > budget)
            cout << "Бюджет вичерпано на дні " << day << ", накоричено " << sum2 << " грн" << endl;
            else
            cout << "Залишок бюджету: " << budget - sum(spending, N) << " грн" << endl;
            cout << endl;
            break;

            case 3:
            cout << endl;
            cout << fixed << setprecision(2);
            cout << "Денний ліміт (грн, 0 = за замовчуванням): "; // задання денного ліміту
            cin >> limit;
            if (limit <= 0 || cin.fail())
            limits(N, spending, d); // якщо ліміт задано не коректно або вказано 0
            else
            limits(N, spending, d, limit); // якщо ліміт задано правильно
            cout << endl;
            break;

            case 4:
            cout << endl;
            cout << fixed << setprecision(2);
            sort(spending2, N); // сортує копію масиву і виписує найбільші елементи
            cout << endl;
            break;

            case 0:
            break;

            default:
            cout << "Введіть число від 0 до 4!" << endl;
            goto menu; // якщо введено некоректне значення повернути в меню
            break;
        }

    }
    while (f != 0); // повторювати цикл доки не буде вибрано 0

    return 0;
}

void dailySpend(int n, double arr[]) // виводить таблицю з витратами по днях
{
    cout << "День  Витрати, грн" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << setw(5) << left << (i + 1) << " " << arr[i] << endl;
    }

}

void minMax(int n, double arr[], double &min, double &max) // знаходить наймкнше та найбільше значення
{
    min = arr[0];
    max = arr[0];
    for(int i = 0; i < n; i++)
    {
        if(arr[i] < min)
        min = arr[i];
        if(arr[i] > max)
        max = arr[i];
    }
}

double sum(double arr[], int n) // обраховує суму елементів масиву за допомогою рекурсії
{
    if (n == 0) return 0;
    return arr[n-1] + sum(arr, n-1);
}

void limits(int n, double arr[], int d, double limit) // встановлює ліміт та перевіряє дні що його перевищують
{
    cout << "Ліміт: " << limit << " грн" << endl;
    for(int i = 0; i < n; i++)
    {
        if(arr[i] > limit)
        {
            cout << "день " << i + 1 << ": " << arr[i] << " грн" << endl;
            d++;
        }
    }
    cout << "Разом днів з перевищенням: " << d << endl;
}

void sort(double arr[], int n) // сортує масив та вибирає найбільші значення
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
    if(n == 1)
    cout << "Топ найбільших витрат: " << arr[n - 1] << " грн" << endl;
    else if(n == 2)
    cout << "Топ найбільших витрат: " << arr[n - 1] << ", " << arr[n - 2] << " грн" << endl;
    else
    cout << "Топ найбільших витрат: " << arr[n - 1] << ", " << arr[n - 2] << ", " << arr[n - 3] << " грн" << endl;
}