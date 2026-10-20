/*
Задача: Аналізатор місячного бюджету
Виконав: Афанасьєв Олексій (ШІ-14)
*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Прототипи функцій
void showMenu();
void showExpenses(float A[], int N);
void findMinMax(float A[], int N, float &max_day, float &min_day);
float sumExpenses(float A[], int N);
void showAverageExpenses(float A[], int N);
void showBudgetLastDay(float A[], int N, float budget);
void showStats(float A[], int N, float budget, float &min_day, float &max_day);
void showOverLimitDays(float A[], int N, float limit = 1000.0f);
void showThreeDays(float A[], int N);
void bubbleSort(float A[], int N);


int main()
{
    cout << fixed << setprecision(2); // Виведення у форматі 2 цифр після коми
    
    // Задаємо необхідні змінні
    float budget;
    int N;
    float spending[31];
    int choice = -1;

    // Введення і валідація бюджету
    cout << "Enter your budget: ";
    while(!(cin >> budget) || budget < 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Error: you must enter a non-negative number" << endl;
        cout << "Enter your budget: ";
    }

    // Введення і валідація кількості днів
    cout << "Enter days number: ";
    while(!(cin >> N) || N <= 0 || N > 31)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Error: you must enter a number in the range from 1 to 31" << endl;
        cout << "Enter days number: ";
    }

    // Введення і валідація значень масиву spending
    cout << "Expenses by day (uah): ";

    for(int i = 0; i < N; i++)
    {
        if(!(cin >> spending[i]) || spending[i] < 0)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Error: you must enter non-negative numbers only" << endl;

            i = -1;
            cout << "Expenses by day (uah): ";
        }
    }

    menu: // мітка menu

    // Показ інтерфейсу меню
    do
    {
        showMenu();
        // Введення бажаної операції, її валідація
        cout << "Enter your operation: ";
        if(!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Error: wrong operation selected";

            goto menu;
        }

        cout << endl;

        switch (choice)
        {
            case 1: // Показ витрат по днях
                showExpenses(spending, N);
                break;
            case 2: // Статистика витрат
                float max_day;
                float min_day;
                showStats(spending, N, budget, min_day, max_day);
                break;
            case 3: // Дні з перевищенням денного ліміту
                float day_limit;
                cout << "Day limit (uah, 0 = by default): ";

                while(!(cin >> day_limit) || day_limit < 0)
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Error: you must enter a non-negative number" << endl;
                    cout << "Day limit (uah, 0 = by default): ";
                }

                if(day_limit == 0.0f) showOverLimitDays(spending, N);
                else showOverLimitDays(spending, N, day_limit);
                break;
            case 4: //Три найдорожчі дні
                float spending_copy[31];
                for(int i = 0; i < N; i++)
                {
                    spending_copy[i] = spending[i];
                }
                showThreeDays(spending_copy, N);
                break;
            case 0:
                cout << "Exit..." << endl;
                break;
            default:
                cout << "Unknown operation selected";
                goto menu;
        }
    }
    while(choice != 0);

    return 0;
}

// Сортування бульбашкою
void bubbleSort(float A[], int N)
{
    for(int i = 0; i < N - 1; i++)
    {
        for(int j = 0; j < N - 1 - i; j++)
        {
            if(A[j] < A[j+1])
            {
                float t = A[j];
                A[j] = A[j+1];
                A[j+1] = t;
            }
        }
    }
}

// Виведення інтерфейсу меню в термінал
void showMenu()
{
    cout << endl;
    cout << left << setw(3) << "1" << right << setw(60) << "Show expenses by day" << endl;
    cout << left << setw(3) << "2" << right << setw(60) << "Expenses statistics" << endl;
    cout << left << setw(3) << "3" << right << setw(60) << "Days on which the daily limit was exceeded" << endl;
    cout << left << setw(3) << "4" << right << setw(60) << "The Three Most Expensive Days" << endl;
    cout << left << setw(3) << "0" << right << setw(60) << "Exit" << endl;
}

// Показ витрат по днях
void showExpenses(float A[], int N)
{
    cout << right << setw(3) << "Day" << right << setw(20) << "Expenses, uah" << endl;
    for(int i = 0; i < N; i++)
    {
        cout << right << setw(3) << i+1 << right << setw(20) << A[i] << endl;
    }
}

// Знаходження мінімальних та максимальних витрат
void findMinMax(float A[], int N, float &max_day, float &min_day)
{
    max_day = A[0];
    min_day = A[0];
    for(int i = 1; i < N; i++)
    {
        if(A[i] > max_day) max_day = A[i];
        if(A[i] < min_day) min_day = A[i];
    }
}

// Сумарні витрати
float sumExpenses(float A[], int N)
{
    if(N == 0) return 0.0f;
    return A[N-1] + sumExpenses(A, N-1);
}

// Показ середніх витрат
void showAverageExpenses(float A[], int N)
{
    int days = 0;
    float total = 0.0f;
    for(int i = 0; i < N; i++)
    {
        if(A[i] == 0.0f) continue;
        total += A[i];
        days++;
    }

    cout << left << setw(30) << "Days with expenses: " << right << setw(15) << days << endl;

    if(days == 0)
    {
        return;
    }

    float average = total / days;

    cout << left << setw(30) << "Their average per day: " << right << setw(15) << average << " uah" << endl;
}

// Показ дня закінчення бюджету
void showBudgetLastDay(float A[], int N, float budget)
{
    float total_expenses = 0.0f;
    int day = 0;
    while(day < N)
    {
        total_expenses += A[day];
        if(total_expenses > budget)
        {
            cout << "Budget ends on day " << day+1 << ", accumulated: " << total_expenses << " uah" << endl;
            break;
        }
        day++;
    }

    if(day == N) cout << "Budget left: " << budget - total_expenses << " uah" << endl;

}


// Показ статистики витрат
void showStats(float A[], int N, float budget, float &min_day, float &max_day)
{
    findMinMax(A, N, max_day, min_day);
    float total_expenses = sumExpenses(A, N);

    cout << left << setw(30) << "Minimal expenses day: " << right << setw(15) << min_day << " uah" << endl;
    cout << left << setw(30) << "Maximum expenses day: " << right << setw(15) << max_day << " uah" << endl;
    cout << left << setw(30) << "Total expenses: " << right << setw(15) << total_expenses << " uah" << endl;

    if(budget < total_expenses)
    {
        cout << left << setw(30) << "Over budget expenses:  " << right << setw(15) << abs(budget - total_expenses) << " uah" << endl;
    }
    else
    {
        cout << left << setw(30) << "Money left:  " << right << setw(15) << budget - total_expenses << " uah" << endl;
    }

    showAverageExpenses(A, N);
    showBudgetLastDay(A, N, budget);
}


// Показ днів з перевищенням денного ліміту
void showOverLimitDays(float A[], int N, float limit)
{
    int count = 0;
    for(int i = 0; i < N; i++)
    {
        if(A[i] > limit)
        {
            cout << right << setw(10) << "day " << i+1 << ":" << setw(15) << A[i] << " uah" << endl;
            count++;
        }
    }
    cout << "Day-limit: " << limit << " uah" << endl;
    cout << "Over-limit days: " << count << endl;
}

// Показ трьох днів з найбільшими витратами
void showThreeDays(float A[], int N)
{
   bubbleSort(A, N);

   int b;
   if(N < 3) b = N;
   else b = 3;

   cout << "Top-3 expenses: ";

   for(int i = 0; i < b; i++)
   {
        if(i > 0) cout << ", ";
        cout << A[i];
   }

   cout << " uah" << endl;
}
