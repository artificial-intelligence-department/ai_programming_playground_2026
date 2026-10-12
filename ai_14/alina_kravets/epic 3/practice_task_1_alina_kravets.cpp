/*Аналізатор місячного бюджету
ШІ-14
Кравець Аліна*/
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void dailySpending(double spending[], int n) //створюємо функцію, яка виведе таблицю витрат
{
    cout << fixed << setprecision(2);
    cout << "День\t Витрати, грн" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i+1 << "\t " << spending[i] << endl;
    }
}

double spentSum(double spending[], int n) //створюємо рекурсивну функцію для розрахунку суми
{
    if (n==0) return 0;
    return spending[n-1] + spentSum(spending, n-1);
}

void spendingStats(double spending[], int n, double &mn, double &mx, double budget) //створюємо функцію, яка виведе статистику
{
    cout << fixed << setprecision(2);
    for(int i = 0; i < n; i++)
    {
        if(spending[i] > mx) mx = spending[i];
        if(spending[i] < mn) mn = spending[i];
    }
    cout << "Мінімальні витрати за день: " << mn << " грн" << endl;
    cout << "Максимальні витрати за день: " << mx << " грн" << endl;

    double sum = spentSum(spending, n);
    cout << "Сумарні витрати: " << sum << " грн" << endl;

    if (sum > budget)
    {
        cout << "Перевитрата понад бюджет: " << abs(budget - sum) << " грн" << endl;
    }

    int days = 0;
    for (int i = 0; i < n; i++)
    {
        if(spending[i] == 0) continue;
        days++;
    }
    cout << "Днів з покупками: " << days << endl;
    cout << "Середні витрати за такий день: " << sum/days << " грн" << endl;

    int i = 0;
    double spent = 0;
    while (i < n)
    {
        spent += spending[i];
        if (spent > budget)
        {
            cout << "Бюджет вичерпано на дні " << i+1 << ", накопичено " << spent << " грн" << endl;
            break;
        }
        i++;
    }
    if (spent < budget) cout << "Бюджет не вичерпано, залишок - " << budget - spent << " грн" << endl;
}

void dailyLimit(double spending[], int n, double limit = 1000) //створюємо функцію, яка виведе дні з перевищенням ліміту
{
    cout << fixed << setprecision(2);
    int count = 0;
    cout << "Ліміт: " << limit << " грн" << endl;
    for (int i = 0; i < n; i++)
    {
        if(spending[i] > limit)
        {
            cout << "День " << i+1 << ": " << spending[i] << " грн" << endl;
            count++;
        }
    }
    cout << "Разом днів з перевищенням ліміту: " << count << endl;
}

void top3Days(double spending[], int n) //створюємо функцію, яка посортує копію масиву за спаданням і виведе топ-3 елементи
{
    cout << fixed << setprecision(2);
    double copy[n] = {0};
    for (int i = 0; i < n; i++)
    {
        copy[i] = spending[i];
    }
    for (int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if (copy[j] < copy[j+1])
            {
            double x = copy[j];
            copy[j] = copy[j+1];
            copy[j+1] = x;
            }
        }
    }
    if (n == 1) cout << "Топ-1 витрата: " << copy[0] << " грн" << endl;
    else if (n == 2) cout << "Топ-2 витрати: " << copy[0] << " грн, " << copy[1] << " грн" << endl;
    else cout << "Топ-3 витрати: " << copy[0] << " грн, " << copy[1] << " грн, " << copy[2] << " грн" << endl; 
}

int main()
{
    double budget = 0; //створюємо змінні
    int n = 0;
    int choice = 0;
    double limit = 0;

    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    if (budget <= 0) //бюджет на місяць не може бути від'ємним
    {
        cout << "Помилка: введіть бюджет" << endl;
        return 1;
    }

    cout << "Кількість днів обліку: ";
    cin >> n;
    if (n <= 0 || n > 31) //кількість днів має бути додатньою і <= ніж кількість днів у місяці
    {
        cout << "Помилка: введіть кількість днів" << endl;
        return 1;
    }

    double spending[n] = {0}; //створюємо масив для витрат

    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < n; i++)
    {
        cin >> spending[i];
        if (spending[i] < 0) //витрати не можуть бути від'ємними
        {
            cout << "Помилка: введіть витрати" << endl;
            return 1;
        }
    }

    double min = spending[0]; //створюємо змінні для мінімуму і максимуму, присвоюємо їм значення першого елементу
    double max = spending[0]; //наступні елементи будемо порівнювати з ним

    do{
        menu:
        cout << "----Меню----" << endl;
        cout << "1 - показати витрати по днях" << endl;
        cout << "2 - статистика витрат" << endl;
        cout << "3 - дні з перевищенням денного ліміту" << endl;
        cout << "4 - три найдорожчі дні" << endl;
        cout << "0 - вийти" << endl;
        cout << "Оберіть дію: ";
        cin >> choice;
        if(cin.fail()) //якщо введено букву, ми повернемось до меню
        {
            cin.clear();
            cin.ignore();
            cout << "Помилка: введіть дію" << endl;
            goto menu;
        }

        switch(choice) //перевіряємо обрану дію
        {
            case 0:
            break;
            case 1:
            dailySpending(spending, n);
            break;
            case 2:
            spendingStats(spending, n, min, max, budget);
            break;
            case 3:
            cout << "Денний ліміт (грн, 0 - за замовчуванням): ";
            cin >> limit;
            if (limit < 0) //ліміт витрат не може бути від'ємним
            {
                cout << "Помилка: введіть ліміт денних витрат" << endl;
            }
            else if (limit == 0) dailyLimit(spending, n);
            else dailyLimit(spending, n, limit);
            break;
            case 4:
            top3Days(spending, n);
            break;
            default:
            cout << "Помилка: введіть дію" << endl;
            break;
        }
    }while (choice != 0); //якщо ми обираємо 0, цикл завершується

    return 0;
}
