/*
    Задача: Аналізатор місячного бюджету
    Автор: Гайдук Маргарита
    Група: ШІ-12
*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
// Виведення таблиці витрат по днях
void showDailySpending (double spending[], int days)
{
    cout << "День        Витрати, грн"<< endl;
    cout << fixed << setprecision(2);
    for (int i = 0; i < days; i++) 
    {
        cout << setw(3) << i + 1 << setw(15) << spending[i] << endl;
    }
}
// Пошук мінімальних і максимальних витрат
void findMinMax(double spending[], int days, double& minV, double& maxV) 
{
    minV = spending[0];
    maxV = spending[0];
    for (int i = 1; i < days; i++)
    {
        if (spending[i] < minV)
        {
            minV = spending[i];
        }
        if (spending[i] > maxV)
        {
            maxV = spending[i];
        }
    }
}
// Рекурсивний підрахунок суми витрат
double summarySpendings(double spending[], int days)
{
    if (days == 0)
    {
        return 0;
    }
    return spending[days - 1] + summarySpendings(spending, days - 1);
}
// Статистика витрат і перевірка місячного бюджету
void showStatistics(double spending[], int days, double budget)
{
    cout << fixed << setprecision(2);
    // Мінімум і максимум за день
    double minV;
    double maxV;
    findMinMax(spending, days, minV, maxV);
    cout << "Мінімальні витрати за день: "<< minV << " грн" << endl;
    cout << "Максимальні витрати за день: "<< maxV << " грн" << endl;
    // Сумарні витрати 
    double total;
    total = summarySpendings(spending, days);
    cout << "Сумарні витрати: " << total << " грн" << endl;
    // Залишок бюджету або перевитрата (модуль від'ємного залишку)
    double rest = budget - total;
    if (rest >= 0) 
    {
        cout << "Залишок бюджету: " << rest << " грн" <<  endl;
    }
    else 
    {
        cout << "Перевитрата понад бюджет: " << fabs(rest) << " грн" << endl;
    }
     // Підрахунок днів з покупками
    int shoppingDays = 0;
    for (int i = 0; i < days; i++)
        {
            if (spending[i] == 0)
            {
                continue;
            }
            shoppingDays++;
        }
    cout << "Днів з покупками: " << shoppingDays << endl;
    // Середні витрати лише за дні з покупками
    double average;
    if (shoppingDays > 0)
    {
        average = total / shoppingDays;
        cout << "Середні витрати за такий день: " << average << " грн" << endl;
    }
    else
    {
        cout << "Днів з покупками немає."<< endl;
    }
    // Пошук дня, коли бюджет вичерпано
    double currentSum = 0;
    int day = 0;
    while (day < days)
    {
        currentSum += spending[day];
        if (currentSum > budget)
        {
            cout << "Бюджет вичерпано на дні " << day + 1 << ", накопичено " << currentSum << " грн." << endl;
            break;
        }
        day++;
    }
    if (currentSum <= budget)
    {
        cout << "Бюджету вистачило на всі дні. Залишок: " << budget - currentSum << " грн." << endl;
    }
// Виведення днів, у які витрати перевищили ліміт
}
void limitDays(double spending[],int days, double limit = 1000)
{
    int count = 0;
    cout << fixed << setprecision(2);
    cout << "Ліміт: " << limit << " грн" << endl;
    for (int i = 0; i < days; i++)
    {
        if (spending[i] > limit)
        {
            cout << "  день " << i + 1 << ": " << spending[i] << " грн" << endl;
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}
// Введення денного ліміту 
void showLimitDays(double spending[], int days)
{
    double limit;
    cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
    cin >> limit;
    if (cin.fail() || limit < 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Помилка: ліміт має бути невід'ємним числом." << endl;
    }
    else if (limit == 0)
    {
        limitDays(spending, days);
    }
    else
    {
        limitDays(spending, days, limit);
    }
}
// Виведення трьох найбільших витрат
void showTopThree(double spending[],int days)
{
    double copy[31];
    for (int i = 0; i < days; i++)
    {
        copy[i] = spending [i];
    }
    for (int i = 0; i < days; i++)
    {
        for (int j = i + 1; j < days; j++)
        {
            if (copy[j] > copy[i])
            {
                double temp = copy[i];
                copy[i] = copy[j];
                copy[j] = temp;
            }
        }
    }
    int count = 3;
    if (days < 3)
    {
        count = days;
    }

    cout << fixed << setprecision(2);
    cout << "Топ-3 витрат: ";
    for (int i = 0; i < count; i++)
    {
        cout << copy[i];
        if (i < count - 1)
        {
            cout << ", ";
        }
    }
    cout << " грн" << endl;
}
int main() {
    // Введення і перевірка бюджету
    double budget;
    cout << "Бюджет на місяць(грн): ";
    cin >> budget;
    if (cin.fail() || budget <= 0) 
    {
        cout << "Помилка: бюджет повинен бути додатним числом." << endl;
        return 1;
    }
    // Введення і перевірка кількості днів
    int days;
    cout << "Кількість днів обліку: ";
    cin >> days;
    if (cin.fail() || days < 1 || days > 31) 
    {
        cout << "Помилка: кількість днів має бути числом від 1 до 31." << endl;
        return 1;
    }
    // Введення витрат по днях
    double spending[31];
    cout << "Витрати по днях(грн): ";
    for (int i = 0; i < days; i++)
    {
        cin >> spending[i];
        if (cin.fail() || spending[i] < 0)
        {
            cout << "Помилка: витрати по днях повинні бути невід'ємним числом." << endl;
            return 1;
        }
    }
    // Головне меню
    int choice;
    do 
    {
    menu:
        cout << endl;
        cout << "1 - Показати витрати по днях"<< endl;
        cout << "2 - Статистика витрат" << endl;
        cout << "3 - Дні з перевищенням денного ліміту" << endl;
        cout << "4 - Три найдорожчі дні" << endl;
        cout << "0 - Вийти" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;
        if (cin.fail() || choice < 0 || choice > 4)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка: потрібно ввести число від 0 до 4." << endl;
            goto menu;
        }
        // Виклик функції вибраного пункту
        switch (choice) 
        {
            case 1: showDailySpending(spending, days); break;
            case 2: showStatistics(spending, days, budget); break;
            case 3: showLimitDays(spending, days); break;
            case 4: showTopThree(spending, days); break;
        }
    }
    while (choice != 0);
    
    return 0;
}