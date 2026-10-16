/*
Назва задачі: Аналізатор місячного бюджету
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_DAYS = 31;

// Виводить витрати за кожен день.
void showSpending(const double spending[], int N)
{
    cout << endl;
    cout << "День       Витрати, грн" << endl;

    for (int i = 0; i < N; i++)
    {
        cout << setw(4) << i + 1 << setw(19) << spending[i] << endl;
    }
}

// Знаходить мінімум і максимум та передає їх через параметри-посилання.
void findMinMax(const double spending[], int N, double& minSpending, double& maxSpending)
{
    minSpending = maxSpending = spending[0];

    for (int i = 1; i < N; i++)
    {
        if (spending[i] < minSpending)
            minSpending = spending[i];

        if (spending[i] > maxSpending)
            maxSpending = spending[i];
    }
}

// Рекурсивно обчислює суму витрат за N днів.
double calculateTotal(const double spending[], int N)
{
    if (N == 0)
        return 0;

    return spending[N - 1] + calculateTotal(spending, N - 1);
}

// Виводить статистику витрат і перевіряє, чи вистачило бюджету.
void showStatistics(const double spending[], int N, double budget)
{
    double minSpending, maxSpending;
    findMinMax(spending, N, minSpending, maxSpending);

    double total = calculateTotal(spending, N);
    double remainder = budget - total;

    cout << endl;
    cout << "Мінімальні витрати за день:       " << minSpending << " грн" << endl;
    cout << "Максимальні витрати за день:      " << maxSpending << " грн" << endl;
    cout << "Сумарні витрати:                  " << total << " грн" << endl;

    if (remainder >= 0)
        cout << "Залишок бюджету:                  " << remainder << " грн" << endl;
    else
        cout << "Перевитрата понад бюджет:         " << fabs(remainder) << " грн" << endl;

    double purchaseSum = 0;
    int purchaseDays = 0;

    // Обчислюємо суму витрат і кількість днів лише з покупками.
    for (int i = 0; i < N; i++)
    {
        if (spending[i] == 0)
            continue;

        purchaseSum += spending[i];
        purchaseDays++;
    }

    cout << "Днів з покупками:                 " << purchaseDays << endl;

    if (purchaseDays > 0)
        cout << "Середні витрати за такий день:    " << purchaseSum / purchaseDays << " грн" << endl;
    else
        cout << "Середні витрати за такий день:    0 грн" << endl;

    double accumulated = 0;
    int day = 0;

    // Шукаємо перший день, коли накопичені витрати перевищили бюджет.
    while (day < N)
    {
        accumulated += spending[day];

        if (accumulated > budget)
            break;

        day++;
    }

    if (day < N)
        cout << "Бюджет вичерпано на дні " << day + 1 << ", накопичено " << accumulated << " грн." << endl;
    else
    {
        cout << "Бюджету вистачило на всі дні." << endl;
        cout << "Залишок: " << budget - accumulated << " грн." << endl;
    }
}

// Виводить дні з витратами понад ліміт.
void showDaysOverLimit(const double spending[], int N, double limit = 1000.0)
{
    int count = 0;

    cout << endl << "Ліміт: " << limit << " грн" << endl;

    for (int i = 0; i < N; i++)
    {
        if (spending[i] > limit)
        {
            cout << "  день " << i + 1 << ": " << spending[i] << " грн" << endl;
            count++;
        }
    }

    cout << "Разом днів з перевищенням: " << count << endl;
}

// Виводить три найбільші суми денних витрат.
void showTopThree(const double spending[], int N)
{
    double copy[MAX_DAYS];

    for (int i = 0; i < N; i++)
        copy[i] = spending[i];

    // Сортуємо копію за спаданням методом бульбашки.
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j < N - i; j++)
        {
            if (copy[j] < copy[j + 1])
            {
                double temp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp;
            }
        }
    }

    // Якщо днів менше трьох, виводимо всі наявні витрати.
    int topCount;

    if (N < 3)
        topCount = N;
    else
        topCount = 3;

    cout << endl << "Топ-" << topCount << " витрат: ";

    for (int i = 0; i < topCount; i++)
    {
        cout << copy[i];

        if (i < topCount - 1)
            cout << ", ";
    }

    cout << " грн" << endl;
}

int main()
{
    double budget;
    int N;
    double spending[MAX_DAYS];

    cout << "Бюджет на місяць (грн): ";
    cin >> budget;

    if (cin.fail() || budget < 0)
    {
        cout << "Помилка: бюджет має бути невід'ємним числом." << endl;
        return 1;
    }

    cout << "Кількість днів обліку: ";
    cin >> N;

    if (cin.fail() || N < 1 || N > MAX_DAYS)
    {
        cout << "Помилка: кількість днів має бути від 1 до 31." << endl;
        return 1;
    }

    cout << "Витрати по днях (грн): ";

    for (int i = 0; i < N; i++)
    {
        cin >> spending[i];

        if (cin.fail() || spending[i] < 0)
        {
            cout << "Помилка: витрати мають бути невід'ємними числами." << endl;
            return 1;
        }
    }

    cout << fixed << setprecision(2);

    // Зчитуємо вибір як рядок, щоб перевіряти також введені символи.
    string choice;

    do
    {
    mainMenu:
        cout << endl << "========== МЕНЮ ==========" << endl;
        cout << "1 - Показати витрати по днях" << endl;
        cout << "2 - Статистика витрат" << endl;
        cout << "3 - Дні з перевищенням денного ліміту" << endl;
        cout << "4 - Три найдорожчі дні" << endl;
        cout << "0 - Вийти" << endl;
        cout << "Ваш вибір: ";

        cin >> choice;

        // Пункт меню має складатися з одного символу.
        if (choice.length() != 1)
        {
            cout << "Помилка: введіть число від 0 до 4." << endl;
            goto mainMenu;
        }

        switch (choice[0])
        {
            case '1':
                showSpending(spending, N);
                break;

            case '2':
                showStatistics(spending, N, budget);
                break;

            case '3':
            {
                double limit;

                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                cin >> limit;

                if (cin.fail() || limit < 0)
                {
                    cout << "Помилка: ліміт має бути невід'ємним числом." << endl;
                    return 1;
                }

                if (limit == 0)
                    showDaysOverLimit(spending, N);
                else
                    showDaysOverLimit(spending, N, limit);

                break;
            }

            case '4':
                showTopThree(spending, N);
                break;

            case '0':
                cout << "Програму завершено." << endl;
                break;

            default:
                cout << "Помилка: введіть число від 0 до 4." << endl;
                goto mainMenu;
        }

    } while (choice != "0");

    return 0;
}