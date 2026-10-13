/* 
Епік 3. Практичне завдання: Аналізатор місячного бюджету.
Авторка: Дячок Маргарита.
Група: ШІ-14.
*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
void ShowDailySpending(double spending[], int N) {
     cout << "День      " << "Витрати, грн" << endl;
    for (int i = 1; i <= N; i++) {//вивід таблиці денних витрат
       cout << i << "          " << fixed << setprecision(2) << spending[i - 1] << endl;
    }
}
void MIN_AND_MAX(double spending[], int N, double &min, double &max) { 
    min = spending[0];
    max = spending[0];
    for (int i = 1; i < N; i++) {//шукаємо мінімум та максимум з витрат за день
            if (spending[i] < min) {min = spending[i];}
            else if (spending[i] > max) {max = spending[i];}
    }
    
}

double TotalSpending (double spending[], int N) {
 if (N <= 0) return 0;//знаходимо загальні витрати за допомогою рекурсії
 if (N == 1) return spending[0];
 return spending[N - 1] + TotalSpending(spending, N - 1);
}

void BudgetLeftover (double spending[], double budget, int N) {
  if (TotalSpending(spending, N) > budget) {cout << "Перевитрата понад бюджет: " << fixed << setprecision(2) << fabs(budget - TotalSpending(spending, N)) << "грн." << endl;} 
  else {cout << "Залишок бюджету: " << fixed << setprecision(2) << budget - TotalSpending(spending, N) << "грн." << endl;}
}

double AvarageSpending (double spending[], int N, int &days_z_pokupkamu) {
 double avarage = 0;
 days_z_pokupkamu = 0;
 for (int i = 0; i < N; i++) { 
    if (spending[i] == 0) continue;
    days_z_pokupkamu++;
    avarage += spending[i]; }
if (days_z_pokupkamu == 0) return 0;

 return avarage / days_z_pokupkamu;
}

void BudgetRunOutDay (double spending[], int N, double budget) {
    double current_spending = 0;
    int runout_day = 0;
    int i = 0;
     while (i < N) {
        current_spending += spending[i];
        i++;
        if (current_spending > budget && runout_day == 0) {
        runout_day = i;}
    }

    if (current_spending < budget) cout << "Залишок бюджету: " << fixed << setprecision(2) << budget - current_spending << "грн." << endl;
    if (current_spending > budget) {cout << "Перевитрата понад бюджет: " << fixed << setprecision(2) << fabs(budget - current_spending) << "грн." << endl;
    cout << "День " << runout_day << ": бюджет вичерпано. " << "Накопичено: " << fixed << setprecision(2) << current_spending - spending[N - 1] << " грн.\n";}
}

void SpendingStatistics(double spending[], int N, double budget) {
    double MIN = 0; 
    double MAX = 0;
   MIN_AND_MAX (spending, N, MIN, MAX);
cout << "Мінімальні витрати за день: " << fixed << setprecision(2) << MIN << "грн." << endl;
cout << "Максимальні витрати за день: " << fixed << setprecision(2) << MAX << "грн." << endl;

cout << "Сумарні витрати: " << fixed << setprecision(2) << TotalSpending(spending, N) << "грн." << endl;

int dni_z_pokupkamu = 0;
double avarage_spending = AvarageSpending (spending, N, dni_z_pokupkamu);
cout << "Днів з покупками: " << dni_z_pokupkamu << endl;
cout << "Середні витрати за такий день: " << fixed << setprecision(2) << avarage_spending << "грн." << endl;

BudgetRunOutDay (spending, N, budget);
}

void DailyLimit(double spending[], int N) {
int limit = 0;
int days_z_perevushennyam = 0;
cout << "Денний ліміт (грн, 0 = за замовчуванням): " << endl;
cin >> limit;
//cout << endl;
if (limit == 0) limit = 1000;
cout << "Ліміт: " << limit << endl;
for (int i = 0; i < N; i++) {
    if (spending[i] > limit) {
        cout << "День " << i + 1 << ": " << fixed << setprecision(2) << spending [i] << "грн." << endl;
        days_z_perevushennyam++; }
} 
cout << "Разом днів з перевищенням: " << days_z_perevushennyam << endl;
}

void Top3HighestSpending(double spending[], int N) {
    double first = 0;
    double second = 0;
    double third = 0;
    for (int i = 0; i < N; i++) {
       if (spending[i] >= first) {
        third = second;
        second = first;
        first = spending[i]; }
       else if (spending[i] >= second) {
        third = second;
        second = spending[i]; }
       else if (spending[i] > third) {
        third = spending[i];
       }
}
cout << "Топ-3 витрат: " << fixed << setprecision(2) << first << ", " << fixed << setprecision(2) << second << ", " << fixed << setprecision(2) << third << " грн." << endl;
}

int main() {
double budget = 0;
int N = 0;
double spending[32] = {0};
cout << "Бюджет на місяць (грн): " << endl;
cin >> budget;
if (budget < 0) return 0;
cout << "Кількість днів обліку: " << endl;
cin >> N;
if (N <= 0 || N > 31) {return 0;}
cout << "Витрати по днях (грн): " << endl;
//int er = 0;
for (int i = 0; i < N; i++) {
    cin >> spending[i];
    if (spending[i] < 0) return 0;
}

int menu = 0;
menu:
cout << "Меню: \n" << "1 - Показати витрати по днях.\n" << "2 - Статистика витрат.\n" << "3 - Дні з перевищенням денного ліміту.\n" << "4 - Три найдорожчі дні.\n" << "0 - Вийти.\n" << endl;

do {
cin >> menu;
cout << endl;
if (menu > 5 || menu < 0) {goto menu;}
    switch (menu) {
        case 1:
            ShowDailySpending(spending, N);
            break;
        case 2: 
            SpendingStatistics(spending, N, budget);
            break;
        case 3: 
            DailyLimit(spending, N);
            break;
        case 4: 
            Top3HighestSpending(spending, N);
            break;
    } 
    cout << endl;
    //goto menu;
    
}

while (menu != 0);

   return 0; }