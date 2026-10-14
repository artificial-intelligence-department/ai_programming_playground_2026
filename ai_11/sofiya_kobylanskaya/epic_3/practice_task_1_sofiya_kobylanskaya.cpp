/*
Epic 3
Practice Task Кобилянська Софія ШІ-11
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

void showSpending(double spending[], int n)
{
    cout << "Витрати по днях" << endl;
    cout << "День     " << "Витрати, грн" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << (i + 1) << "        " << spending[i] << endl;
    }
}

void findMinMax(double spending[], int n, double &minimum, double &maximum)
{
    minimum = spending[0];
    maximum = spending[0];

    for (int i = 0; i < n; i++)
    {
        if (spending[i] < minimum)
        {
            minimum = spending[i];
        }

        if (spending[i] > maximum)
        {
            maximum = spending[i];
        }
    }
}

double calculateSum(double spending[], int n)
{
    if (n == 0)
    {
        return 0;
    }

    return spending[n - 1] + calculateSum(spending, n - 1);
}

void showStatistics(double spending[], int n, double budget)
{
    double minimum;
    double maximum;
    double sum = 0;
    double totalSum = 0;
    double overspending = 0;
    int shoppingDays = 0;
    double averageSpending = 0;
    int spentDay = 0;

    findMinMax(spending, n, minimum, maximum);

    sum = calculateSum(spending, n);

    overspending = fmax(sum - budget, 0.0);

    for (int i = 0; i < n; i++)
    {
        if (spending[i] == 0)
        {
            continue;
        }

        shoppingDays++;
    }

    if (shoppingDays > 0)
    {
        averageSpending = sum / shoppingDays;
    }

    int i = 0;

    while (i < n && totalSum < budget)
    {
        totalSum = totalSum + spending[i];

        if (totalSum > budget)
        {
            spentDay = i + 1;
            break;
        }

        i++;
    }

    cout << "                 Статистика витрат" << endl;
    cout << "Мінімальні витрати за день:           " << minimum << " грн" << endl;
    cout << "Максимальні витрати за день:          " << maximum << " грн" << endl;
    cout << "Сумарні витрати:                      " << sum << " грн" << endl;
    cout << "Перевитрата понад бюджет:             " << overspending << " грн" << endl;
    cout << "Днів з покупками:                     " << shoppingDays << endl;
    cout << "Середні витрати за такий день:        " << averageSpending << " грн" << endl;

    if (spentDay > 0)
    {
        cout << "Бюджет вичерпано на дні " << spentDay
             << ", накопичено " << totalSum << " грн." << endl;
    }
    else
    {
        double remainingBudget = budget - totalSum;
        cout << "Бюджет не було вичерпано." << endl;
        cout << "Залишок бюджету: " << remainingBudget << " грн." << endl;
    }
}

void checkLimit(double spending[], int n, double limit = 1000)
{
    int countLimit = 0;
    int daysLimit[31];

    for (int i = 0; i < n; i++)
    {
        if (spending[i] > limit)
        {
            daysLimit[countLimit] = i + 1;
            countLimit++;
        }
    }
    cout << "Ліміт: " << limit << " грн" << endl;
    for (int i = 0; i < countLimit; i++)
    {
        int day = daysLimit[i];

        cout << "день " << day << ": " << spending[day - 1] << " грн" << endl;
    }
    cout << "Разом днів з перевищенням: " << countLimit << endl;
}

void showLimit(double spending[], int n)
{
    double limit;

    cout << "Денний ліміт (грн, 0 = за замовчуванням): " << endl;

    while (!(cin >> limit) || limit < 0)
    {
        cout << "Помилка! Введіть ліміт 0 або більше: " << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if (limit == 0)
    {
        checkLimit(spending, n);
    }
    else
    {
        checkLimit(spending, n, limit);
    }
}

void showTopThree(double spending[], int n)
{
    double sortedSpending[31];

    for (int i = 0; i < n; i++)
    {
        sortedSpending[i] = spending[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (sortedSpending[i] < sortedSpending[j])
            {
                double temp = sortedSpending[i];
                sortedSpending[i] = sortedSpending[j];
                sortedSpending[j] = temp;
            }
        }
    }

    if (n >= 3)
    {
        cout << "Топ-3 витрат: "
             << sortedSpending[0] << ", "
             << sortedSpending[1] << ", "
             << sortedSpending[2] << " грн" << endl;
    }
    else if (n == 2)
    {
        cout << "Топ-2 витрат: "
             << sortedSpending[0] << ", "
             << sortedSpending[1] << " грн" << endl;
    }
    else
    {
        cout << "Топ-1 витрат: "
             << sortedSpending[0] << " грн" << endl;
    }
}

int main()
{
    cout << fixed << setprecision(2);
    double budget;
    int n;

    cout << "Введіть бюджет на місяць (грн): " << endl;
    while (!(cin >> budget) || budget <= 0)
    {
        cout << "Помилка! Введіть додатне число для бюджету: " << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cout << "Введіть кількість днів обліку: " << endl;
    while (!(cin >> n) || n > 31 || n <= 0)
    {
        cout << "Помилка! Введіть кількість днів від 1 до 31: " << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
    double spending[31];
    cout << "Введіть витрати по днях (грн): " << endl;
    for (int i = 0; i < n; i++)
    {
        while (!(cin >> spending[i]) || spending[i] < 0)
        {
            cout << "Помилка для дня " << (i + 1) << "! Введіть число >= 0: " << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int choice;
    string menu;

    do
    {
    menuStart:
        cout << "Введіть 'menu', щоб побачити меню, або '0', щоб вийти: " << endl;
        cin >> menu;

        if (menu == "0")
        {
            break;
        }

        if (menu != "menu")
        {
            cout << "Помилка! Такої команди не існує." << endl;
            goto menuStart;
        }
        cout << "              Меню" << endl;
        cout << "1. Показати витрати по днях" << endl;
        cout << "2. Статистика витрат" << endl;
        cout << "3. Дні з перевищенням денного ліміту" << endl;
        cout << "4. Три найдорожчі дні" << endl;
        cout << "0. Вийти" << endl;

        cout << "Введіть число: " << endl;
        if (!(cin >> choice) || choice < 0 || choice > 4)
        {
            cout << "Помилка! Повернення до меню." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto menuStart;
        }

        if (choice == 0)
        {
            break;
        }
        switch (choice)
        {
        case 1:
        {
            showSpending(spending, n);
            break;
        }
        case 2:
        {
            showStatistics(spending, n, budget);
            break;
        }
        case 3:
        {
            showLimit(spending, n);
            break;
        }
        case 4:
        {
            showTopThree(spending, n);
            break;
        }
        }
    } while (choice != 0);
    return 0;
}