/* Sofiia Chovhan AI 14
   Pracrice task: Budget control
   */
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
using namespace std;

void eachday(float spending[], int N);

void MaxMin(float spending[], int N, float &Max, float &Min);
float Sum(float spending[], int N);
void control(float spending[], float budget, int N);
void avarage(float spending[], int N);
void limit(float spending[], float budget, int N);

void dayLimit(float spending[], int N, double limit = 1000);

void top(float spending[], int N);

int main()
{

    float budget;
    int N;
    float Max, Min;
    cout << "Enter your budget: ";
    while (!(cin >> budget))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Something went wrong! Enter the budget again: ";
    }
    while (budget < 0)
    {
        cout << "Something went wrong! Your budget cannot be definded with the negative meaning! " << endl
             << "Enter budget again: ";
        cin >> budget;
    }
    // days
    cout << "Enter the number of days you are interested in: ";
    cin >> N;
    while (N <= 0 || N > 31)
    {
        cout << "The program control your budget only over mounth maximum!" << endl
             << "Enter the number of days again: ";
        cin >> N;
    }
    // each day
    cout << "Enter your spendings for each day: " << endl;
    float spending[N];
    for (int i = 0; i < N; i++)
    {
        cout << "Day" << i + 1 << ": ";
        while (!(cin >> spending[i]) || spending[i] < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Something went wrong! Enter the number again: " << endl;
            cout << "Day" << i + 1 << ": ";
        }
    }

    // menu
    int option;
    do
    {
    menu:
        cout << "     === Menu ===" << endl;
        cout << " 1 - Show spendings for each day " << endl;
        cout << " 2 - Statistics of spendings " << endl;
        cout << " 3 - Days with overdone limit " << endl;
        cout << " 4 - Top 3 the most expensive days " << endl;
        cout << " 0 - Leave the Menu " << endl;
        cout << "Choose Your option: ";
        if (!(cin >> option))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Something went wrong! Try again." << endl;
            goto menu;
        }
        if (option > 4 || option < 0)
        {
            cout << "Incorrect option! Try againg" << endl;
            goto menu;
        }

        switch (option)
        {
        case 1:
            eachday(spending, N);
            break;
        case 2:
            MaxMin(spending, N, Max, Min);
            cout << "Your Maximum: " << fixed << setprecision(2) << Max << " UAH" << endl;
            cout << "Your Minimum: " << fixed << setprecision(2) << Min << " UAH" << endl;
            cout << "\nYour total Sum: " << Sum(spending, N) << "UAH" << endl;
            avarage(spending, N);
            control(spending, budget, N);
            limit(spending, budget, N);
            break;
        case 3:
            dayLimit(spending, N);
            break;
        case 4:
            top(spending, N);
            break;
        }
    } while (!(option == 0));

    return 0;
}

// option 1
void eachday(float spending[], int N)
{
    cout << "Your spendings per day" << endl;
    cout << "Day №" << setw(20) << "Spending (UAH)" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "Day " << i + 1 << setw(15) << spending[i] << endl;
    }
}
// option 2
void MaxMin(float spending[], int N, float &Max, float &Min)
{
    Max = spending[0];
    Min = spending[0];
    for (int i = 0; i < N; i++)
    {
        if (spending[i] > Max)
            Max = spending[i];
        if (spending[i] < Min)
            Min = spending[i];
    }
}
float Sum(float spending[], int N)
{
    if (N == 0)
        return 0;
    return spending[N - 1] + Sum(spending, N - 1);
}
void control(float spending[], float budget, int N)
{
    double remainder = budget - Sum(spending, N);
    if (remainder < 0)
    {
        cout << "\nYou exceeded your budget by " << abs(remainder) << " UAH" << endl;
    }
    else
        cout << "Your remainder: " << remainder << " UAH" << endl;
}
void avarage(float spending[], int N)
{
    double av = 0;
    int purchased = 0;
    for (int i = 0; i < N; i++)
    {
        if (spending[i] <= 0)
            continue;
        av += spending[i];
        purchased += 1;
    }
    if (purchased > 0)
        av = av / purchased;
    else
        av = 0;
    cout << "Days with purshase: " << purchased << endl;
    cout << "Avarage amount per day for " << purchased << " days: " << av << "UAH" << endl;
}
void limit(float spending[], float budget, int N)
{
    int day = 0;
    float total = 0;
    while (day < N)
    {

        total += spending[day];
        if (total > budget)
        {
            cout << "You ecxeeded your budget on day " << day + 1 << endl;
            break;
        } day++;
    }
            if(total < budget ){
            cout << "Your remainder: " << abs(total - budget) << endl;
        }
}
// option 3
void dayLimit(float spending[], int N, double limit)
{
    int daysNumber = 0;
    cout << "Enter your day limit: ";
    while (!(cin >> limit))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << " Something went wrong! " << endl;
        cout << "Enter daily limit again: ";
    }
    while(limit < 0){
        cout << "Something went wrong! Your limit cannot be definded with the negative meaning!" << endl;
        cout << "Enter limit again: ";
        cin >> limit;
    }
    if (limit == 0)
        limit = 1000;
    for (int i = 0; i < N; i++)
    {
        if (spending[i] > limit)
        {
            daysNumber += 1;
            cout << "Day" << i + 1 << ": " << spending[i] << endl;
        }
    }
    cout << "Totally days with ecxeeded limit: " << daysNumber << endl;
}
// option 4
void top(float spending[], int N)
{
    float soart[N];
    for (int i = 0; i < N; i++)
    {
        soart[i] = spending[i];
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N - 1 - i; j++)
        {
            if (soart[j] < soart[j + 1])
            {
                float temp = soart[j];
                soart[j] = soart[j + 1];
                soart[j + 1] = temp;
            }
        }
    }
    cout << "Top 3 day for spending: ";
    for (int i = 0; i < 3 && i < N; i++)
    {
        cout << soart[i] << " ";
    }
    cout << "UAH" << endl;
}