/* 
Задача: Аналізатор місячного бюджету
Автор: Троян Владислав
Група: AI-11
*/
#include <iostream>
#include <iomanip>
using namespace std;

double budget = 0;
int N = 0;
double sum = 0; //сума витрат

void spending_per_day(double spendings[])
{
    cout << "> Таблиця витрат" << endl;
    cout << setw(10) << left << "День" << setw(15) << right << "Сума, грн" << endl;
    int day = 1;
    for (int i = 0; i < N; i++){
        cout << setw(5) << left << day++ << setw(10) << right << setw(10) << fixed << setprecision(2) << spendings[i] << endl;
    }
}

void spending_max_min(double spendings[])
{
    double min_spendings = 0;
    double max_spendings = 0;
    double copy_spendings[N] = {0};
    for (int i = 0; i < N; i++){
        copy_spendings[i] = spendings[i];
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (j+1 < N && copy_spendings[j] > copy_spendings[j+1]){
                swap(copy_spendings[j], copy_spendings[j+1]);
            }
        }
    }
    min_spendings = copy_spendings[0];
    max_spendings = copy_spendings[N-1];
    cout << "Мінімальна витрачена сума за день: " << fixed << setprecision(2) << min_spendings << "грн" << endl;
    cout << "Максимальна витрачена сума за день: " << fixed << setprecision(2) << max_spendings << "грн" << endl;
}

void spendings_sum(double spendings[], int count)
{
    if (count <= 0){
        cout << "Сумарні витрати: " << fixed << setprecision(2) << sum << "грн" << endl;
        return;
    }
    sum += spendings[count-1];
    count--;
    spendings_sum(spendings, count);
}

void remaining(double budget)
{
    budget -= sum;
    if (budget < 0){
        cout << "ПЕРЕВИТРАТИ: " << fixed << setprecision(2) << abs(budget) << "грн" << endl;
    } else cout << "ЗАЛИШОК: " << fixed << setprecision(2) << budget << "грн" << endl;
}

void average_spendings(double spendings[], int days)
{
    for (int i = 0; i < N; i++){
        if (spendings[i] == 0){
            continue;
        } else days++;
    }
    double average = 0;
    if (days != 0){
        average = sum/days;
    } else average = 0;
    cout << "Днів з покупками: " << days << endl;
    cout << "Середні витрати за дні з покупками: " << fixed << setprecision(2) << average << "грн" << endl;
    sum = 0;
}

void zero_budget(double spendings[])
{
    double sum_to_zero = budget;
    int index = 0;
    int days = 0;
    do {
        sum_to_zero -= spendings[index];
        index++;
        days++;
        if (sum_to_zero < 0){
            cout << "> Бюджет вичерпано за " << days << " дні" << ", перевищена сума становила: " << fixed << setprecision(2) << abs(sum_to_zero) << "грн" << endl;
            break;
        }
    } while (days != N);
    if (sum_to_zero >= 0){
        cout << "Бюджет не вичерпано! Залишок: " << fixed << setprecision(2) << sum_to_zero << "грн" << endl;
    }
}

void days_exeeding_limits(double spendings[])
{
    int day = 0;
    cout << "Уведіть денний ліміт (0 за замовчуванням 1000 грн): ";
    double limit = 0;
    cin >> limit;
    if (limit == 0){
        limit = 1000;
    }
    cout << "Ліміт: " << fixed << setprecision(2) << limit << "грн" << endl;
    for (int i = 0; i < N; i++){
        day++;
        if (limit - spendings[i] < 0){
            cout << "> День " << day << ": " << fixed << setprecision(2) << spendings[i] << "грн" << endl;
        }
    }
}

void expensive_days(double spendings[])
{
    double copy_spendings[N] = {0};
    for (int i = 0; i < N; i++){
        copy_spendings[i] = spendings[i];
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (j+1 < N && copy_spendings[j] < copy_spendings[j+1]){
                swap(copy_spendings[j], copy_spendings[j+1]);
            }
        }
    }
    if (N >= 3){
        cout << "Топ 3 витрат: " << copy_spendings[0] << "грн, " << copy_spendings[1] << "грн, " << copy_spendings[2] << "грн" << endl;
    } else if (N == 2){
        cout << "Топ 3 витрат: " << copy_spendings[0] << "грн, " << copy_spendings[1] << endl;
    } else if (N == 1){
        cout << "Топ 3 витрат: " << copy_spendings[0] << "грн" << endl;
    }
}

int main()
{
    bool fail;
    do {
        cout << "Ваш бюджет, грн: ";
        cin >> budget;
        fail = cin.fail();
        if (fail){
            cout << "Бюджет не може складатися з букв." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        } else if (budget < 0){
            cout << "Бюджет не може бути меншим 0." << endl;
        }
    } while (budget <= 0 || fail);
    do {
        cout << "Кількість днів обліку: ";
        cin >> N;
        fail = cin.fail();
        if (N > 31 || N < 1){
            cout << "НЕПРИПУСТИМЕ ЗНАЧЕННЯ ОБЛІКУ" << endl;
        } else if (fail){
            cout << "Облік днів не може складатися з букв." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    } while ((N > 31 || N < 1) || fail);

    cout << "Витрати по днях, грн: ";
    double spendings[N] = {0};
    int minus = 0;
    do {
    for (int i = 0; i < N; i++){
        cin >> spendings[i];
        fail = cin.fail();
        if (fail){
            cout << "Витрати не можуть складатися з букв." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            minus = i;
            cout << "Витрати по днях, грн: " << endl;
            break;
        } else if (spendings[i] < 0){
            minus = i;
            cout << "Витрати не потрібно записувати як від'ємне." << endl;
            cout << "Витрати по днях, грн: " << endl;
            break;
        }
    }
    } while (spendings[minus] < 0 || fail);
MENU:
    cout << "МЕНЮ <" << endl;
    cout << "1 > Показати витрати по днях" << endl;
    cout << "2 > Статистика витрат" << endl;
    cout << "3 > Дні з перевищення денного ліміту" << endl;
    cout << "4 > Три найдорощі дні" << endl;
    cout << "0 > Вийти" << endl;
    int action = 0;
    cin >> action;
    switch (action){
        case 0:
        return 0;
        case 1:
        spending_per_day(spendings);
        break;
        case 2:
        spending_max_min(spendings);
        spendings_sum(spendings, N);
        remaining(budget);
        average_spendings(spendings, 0);
        zero_budget(spendings);
        break;
        case 3:
        days_exeeding_limits(spendings);
        break;
        case 4:
        expensive_days(spendings);
        break;
    }
    char answer;
    cout << "Повернутися в МЕНЮ? (y/n): ";
    cin >> answer;
    if (answer == 'y'){
        goto MENU;
    } else return 0;
}