/*
Аналізатор місячного бюджету
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
void costs(float *arr, int x, float &max, float &min)
{
    float mn = arr[0], mx = arr[0];
    for (int i = 1; i < x; i++)
    {
        if (arr[i] < mn)
            mn = arr[i];
        if (arr[i] > mx)
            mx = arr[i];
    }
    max = mx;
    min = mn;
}

float sumSpending(float *arr, int x)
{
    if (x == 0)
        return 0;
    return arr[x - 1] + sumSpending(arr, x - 1);
}

float perevitrati(int x, float totalSpending)
{
    if (x >= totalSpending)
    {
        return 0;
    }
    else
    {
        return fabs(x - totalSpending);
    }
}

int shoppingDays(float *arr, int x)
{
    int s = 0;
    for (int a = 0; a < x; a++)
    {
        if (arr[a] == 0)
            continue;
        s++;
    }
    return s;
}

void budgetEnd(float *arr, int x, int y)
{
    float sum = 0;
    int days = 0;
    int budgetFinish = 0;
    while (days < y && sum <= x)
    {
        sum += arr[days];
        if (sum > x)
        {
            cout << "Бюджет вичерпано на дні " << days + 1
                 << ", накопичено " << sum << " грн." << endl;
            budgetFinish = 1;
            break;
        }

        days++;
    }

    if (budgetFinish == 0)
    {
        cout << "Бюджет не вичерпано, залишок " << x - sum << " грн" << endl;
    }
}

void dayWithOverspending(float *arr, int x, int lim)
{
    int days = 0;
    int sumDays = 0;
    for (int a = 0; a < x; a++)
    {
        days++;
        if (arr[a] > lim)
        {
            cout << "День " << days << ": " << fixed << setprecision(2) << arr[a] << " грн" << endl;
            sumDays++;
        }
    }
    cout << "Разом днів з перевищенням:  " << sumDays << endl;
}

void maxSpending(const float *arr, int x)
{
    if (x <= 0)
        return;
    float copy[x];
    for (int i = 0; i < x; ++i)
    {
        copy[i] = arr[i];
    }

    for (int i = 0; i < x - 1; ++i)
    {
        for (int j = 0; j < x - i - 1; ++j)
        {
            if (copy[j] < copy[j + 1])
            {
                float temp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp;
            }
        }
    }

    int count_to_print = (x < 3) ? x : 3;

    cout << "Підбірка з " << count_to_print << " найбільших витрат: ";
    for (int i = 0; i < count_to_print; ++i)
    {
        cout << fixed << setprecision(2) << copy[i] << " грн ";
    }
    cout << endl;
}

int main()
{
    int budget = 0;
    cout << "Введіть ваш місячний бюджет (грн): ";
    cin >> budget;
    if (budget < 0 || cin.fail()){
        cout << "Неправильний ввід даних." << endl;
        return 1;
    }
    int n = 0;
    cout << "Введіть кількість днів обліку: ";
    cin >> n;
    if (n < 0 || cin.fail()){
        cout << "Неправильний ввід даних." << endl;
        return 1;
    }

    int i = 0;
    float spending[n] = {0};
    cout << "Введіть витрати по днях (грн): ";
    for (i = 0; i < n; i++)
    {
        cin >> spending[i];
        if (spending [i] < 0 || cin.fail()){
        cout << "Неправильний ввід даних." << endl;
        return 1;
        }
    }


    cout << endl;
    cout << endl;

    cout << "Бюджет на місяць (грн): " << budget << endl;
    cout << "Кількість днів обліку: " << n << endl;
    cout << "Витрати по днях (грн): ";
    for (i = 0; i < n; i++)
    {
        cout << spending[i] << " ";
    }

    cout << endl;
    cout << endl;

    int choice;
menu: // лейбл, який використовує goto
    cout << "Меню: " << endl;
    cout << " 1 - Показати витрати по днях" << endl;
    cout << " 2 - Статистика витрат" << endl;
    cout << " 3 - Дні з перевищенням денного ліміту" << endl;
    cout << " 4 - Три найдорожчі дні" << endl;
    cout << " 0 - Вийти" << endl;
    cout << " > ";
    cin >> choice;
    if ( cin.fail() || choice < 0 || choice > 4){
        cin.clear();
        cin.ignore(1000, '\n');
        goto menu;

    }
    cout << endl;

    int doWhile = 0;
    do
    {
        switch (choice)
        {
        case 1:
        {
            cout << "День          Витрати, грн" << endl;
            i = 0;
            for (int day = 1; day <= n; day++)
            {
                cout << day << "                  " << fixed << setprecision(2) << spending[i] << endl;
                i++;
            }
            cout << endl;
            goto menu;
        }

        case 2:
        {
            float max_costs = 0;
            float min_costs = 0;
            costs(spending, n, max_costs, min_costs);
            cout << "Мінімальні витрати за день:              " << fixed << setprecision(2) << min_costs << " грн" << endl;
            cout << "Максимальні витрати за день:             " << fixed << setprecision(2) << max_costs << " грн" << endl;
            cout << "Сумарні витрати:                         " << fixed << setprecision(2) << sumSpending(spending, n) << " грн" << endl;
            cout << "Перевитрата понад бюджет:                " << fixed << setprecision(2) << perevitrati(budget, sumSpending(spending, n)) << " грн" << endl;
            cout << "Днів з покупками:                        " << shoppingDays(spending, n) << endl;
            cout << "Середні витрати за дні з покупками:      " << sumSpending(spending, n) / shoppingDays(spending, n) << " грн" << endl;
            budgetEnd(spending, budget, n);
            cout << endl;
            goto menu;
        }

        case 3:
        {
            float limitByDay = 0;
            float limit = 0;
            cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
            cin >> limitByDay;
            if (limitByDay < 0 || cin.fail()){
                cout << "Неправильний ввід даних." << endl;
                return 1;
            }
            if (limitByDay == 0)
            {
                limit = 1000;
            }
            else
            {
                limit = limitByDay;
            }
            cout << "Ліміт: " << fixed << setprecision(2) << limit << " грн" << endl;
            dayWithOverspending(spending, n, limit);
            cout << endl;
            goto menu;
        }

        case 4:
        {
            maxSpending(spending, n);
            cout << endl;
            goto menu;
        }

        case 0:
        {
            doWhile = 1;
            return 0;
        }
        }
    } while (doWhile == 0);

    return 0;
}