/*Practice Task 1 - Аналізатор Місячного Бюджету
Максімко Павло - СШІ-13*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void show_spending(double spending[], int N);
void max_min_spending(double spending[], int N, double &max_spent, double &min_spent);
double sum_spending(double spending[], int N, double sum, int i);
void spending_remains(double spending_sum, double budget);
void avg_spending(double spending[], int N);
void everything_spent_day(double spending[], int N, double budget);
void stats_spendings(double spending[], int N, double budget);
void day_limit(double spending[], int N, double day_lim = 1000);
void sorting(double spending_copy[], int N);
void top3(double spending_copy[], int N);

int main()
{
    double budget;
    bdg:cout << "Введіть бюджет на місяць (грн): ";
    cin >> budget;
    if(cin.fail())
    {
        cout << "Бюджет повинен бути числом! Спробуйте знову: " << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto bdg;
    }
    else if(budget <= 0)
    {
        cout << "Бюджет повинен бути більше 0! Спробуйте знову: " << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto bdg;
    }
    int N;
    const int MAX_DAYS = 30;
    const int MIN_DAYS = 1;
    n:cout << "Введіть кількість днів обліку: ";
    cin >> N;
    if(cin.fail())
    {
        cout << "Кількість днів обліку повинна бути цілим числом! Спробуйте знову: " << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto n;
    }
    else if(N > MAX_DAYS || N < MIN_DAYS)
    {
        cout << "Облік ведеться не менше " << MIN_DAYS << " дня і не довше " << MAX_DAYS << " днів!" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto n;
    }
    //В ідеалі задаючи розмір масиву, розмір має бути константою, адже деякі компілятори не пропускають звичайних змінних
    //Тому використовуємо константну змінну, щоб задати розмір масивам
    //Також ініціалізуємо одразу масив задля безпеки
    double spending[MAX_DAYS] = {0}, spending_copy[MAX_DAYS] = {0};

    for(int i = 0; i < N; i++)
    {
        cout << "Введіть витрату за день " << i + 1 << "(грн): ";
        sp:cin >> spending[i];
        if(cin.fail() || spending[i] < 0)
        {
            cout << "Витрата за день повинна бути додатнім числом! Спробуйте знову: " << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto sp;
        }
        spending_copy[i] = spending[i];
    }
    
    int action;
    double day_lim;
    //Цикл do-while, щоб меню мінімум 1 раз виводилося
    do {
        act:cout << "Операції:" << endl;
        cout << "1 - Показати витрати по днях" << endl;
        cout << "2 - Статистика витрат" << endl;
        cout << "3 - Дні з перевищенням денного ліміту" << endl;
        cout << "4 - Три найдорожчі дні" << endl;
        cout << "0 - Вийти" << endl;
        cout << "Введіть операцію:";
        cin >> action;
        if(cin.fail())
        {
            cout << "Операція повинна бути числом!" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto act;
        }
        switch(action)
        {
            case 1:
                cout << "Ви вибрали операцію 1: " << endl;
                show_spending(spending, N);
                break;
            case 2:
                cout << "Ви вибрали операцію 2: " << endl;
                stats_spendings(spending, N, budget);
                break;
            case 3:
                cout << "Ви вибрали операцію 3: " << endl;
                lim:cout << "Введіть денний ліміт (грн, 0 = за замовчуванням): ";
                cin >> day_lim;
                if(cin.fail() || day_lim < 0)
                {
                    cout << "Ліміт повинен бути додатнім числом!" << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    goto lim;
                }
                //Перевірка для значення за замовчуванням ліміту на день
                if(day_lim == 0) day_limit(spending, N);
                else day_limit(spending, N, day_lim);
                break;
            case 4:
                cout << "Ви вибрали операцію 4: " << endl;
                top3(spending_copy, N);
                break;
            case 0:
                cout << "Ви вибрали операцію 0: До побачення!" << endl;
                break;
            default:
                cout << "Такої операції не існує! Спробуйте знову." << endl;
                goto act;
        }

    }
    while(action != 0);

    return 0;
}

void show_spending(double spending[], int N)
{
    cout << "День " << '\t' << " Витрати, грн" << endl;
    for(int i = 0; i < N; i++)
    {
        cout << i + 1 << '\t' << fixed << setprecision(2) << spending[i] << endl;
    }
    return;
}

void max_min_spending(double spending[], int N, double &max_spent, double &min_spent)
{
    //Присвоюємо значення першого елемента для максимуму та мінімуму, щоб пізніше мати з чим порівнювати
    max_spent = min_spent = spending[0];
    for(int i = 1; i < N; i++)
    {
        if(min_spent > spending[i]) min_spent = spending[i];
        if(max_spent < spending[i]) max_spent = spending[i];
    } 
}

double sum_spending(double spending[], int N, double sum, int i)
{
    sum += spending[i];
    //Створюємо умову для виходу з рекурсії, щоб не відбулося зациклення
    if(i == N - 1) return sum;
    else return sum_spending(spending, N, sum, i + 1);
}

void spending_remains(double spending_sum, double budget)
{
    //Оскільки залишок - неціле число, то викорисвуємо функцію fabs, щоб заокруглення до цілих не відбулося
    double remains = fabs(budget - spending_sum);
    if(budget > spending_sum)
    {
        cout << "Залишок бюджету: " << fixed << setprecision(2) << remains << " грн" << endl;
    }
    else if(budget < spending_sum)
    {
        cout << "Перевитрата понад бюджет: " << fixed << setprecision(2) << remains << " грн" << endl;
    }
    else 
    {
        cout << "Усі кошти в наданому бюджеті використано! Залишок: " << fixed << setprecision(2) << remains << " грн" << endl;
    }
    return;
}

void avg_spending(double spending[], int N)
{
    double spending_avg, sum = 0;
    int day = 0;
    for(int i = 0; i < N; i++)
    {
        //Пропускаємо дні, які не мають у собі витрат, щоб не додавати зайвий раз день і до суми 0
        if(spending[i] == 0) continue;
        sum += spending[i];
        day++;
    }
    spending_avg = (sum > 0) ? sum / day : 0;
    cout << "Днів з покупками: " << day << endl;
    cout << "Середні витрати за такий день: " << fixed << setprecision(2) << spending_avg << " грн" << endl;
    return;
}

void everything_spent_day(double spending[], int N, double budget)
{
    double sum = 0;
    int i = 0;
    while(i < N)
    {
        sum += spending[i];
        //Використовуємо break, щоб завчасно закінчити цикл, коли сума буде більше від бюджету
        if(sum > budget)
        {
            break;
        }
        i++;
    }
    if(i < N) cout << "Бюджет вичерпано на дні " << i + 1 << ". Накопичено: " << fixed << setprecision(2) << sum << " грн." << endl; 
    else cout << "Бюджету вистачило на всі дні. Залишок: " << fixed << setprecision(2) << budget - sum << " грн." << endl;
    return;
}

void stats_spendings(double spending[], int N, double budget)
{
    //Присвоюємо значення рекурсивної функції
    double spending_sum = sum_spending(spending, N, 0, 0);
    double max_spent, min_spent;
    //Завдяки параметрам посиланням, значення max_spent і min_spent зберігається після виклику їх у функції
    //Таким чином не приходиться створювати дві окремі функції для обрахунку максимуму і мінімуму
    max_min_spending(spending, N, max_spent, min_spent);
    cout << "Мінімальні витрати за день: " << fixed << setprecision(2) << min_spent << " грн" << endl;
    cout << "Максимальні витрати за день: " << fixed << setprecision(2) << max_spent << " грн" << endl;
    cout << "Сумарні витрати: " << fixed << setprecision(2) << spending_sum << " грн" << endl;
    spending_remains(spending_sum, budget);
    avg_spending(spending, N);
    everything_spent_day(spending, N, budget);  
}

void day_limit(double spending[], int N, double day_lim)
{
    //Оскільки ліміту присвоєне значення у фукції, 
    //то якщо не вводити дану змінну при виклику функції, значення ліміту буде за замовчуванням 1000
    cout << "Ліміт: " << fixed << setprecision(2) << day_lim << endl;

    int days = 0;
    for(int i = 0; i < N; i++)
    {
        if(spending[i] <= day_lim) continue;
        cout << "День " << i + 1 << ":" << fixed << setprecision(2) << spending[i] << " грн" << endl;
        days++;
    }
    cout << "Разом днів з перевищенням: " << days << endl;
}

void sorting(double spending_copy[], int N)
{
    double copy;
    //Сортуємо вкладеними циклами (бульбашкою), порівнюємо сусідні елементи
    //Міняємо місцями завдяки додатковій змінній у напрямку спадання
    for(int i = 0; i < N - 1; i++)
    {
        for(int j = 0; j < N - i - 1; j++)
        {
            if(spending_copy[j] < spending_copy[j + 1])
            {
                copy = spending_copy[j];
                spending_copy[j] = spending_copy[j + 1];
                spending_copy[j + 1] = copy;
            }
        }
    }
    return;
}

void top3(double spending_copy[], int N)
{
    sorting(spending_copy, N);
    int top = (N < 3) ? N : 3;
    cout << "Топ " << top << " витрат: ";
    for(int i = 0; i < top; i++)
    {
        cout << fixed << setprecision(2) << spending_copy[i];
        if(i < top - 1) cout << ", ";
    }
    cout << " грн" << endl;
}