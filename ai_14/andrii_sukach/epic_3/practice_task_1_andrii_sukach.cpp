/*
Задача: Аналізатор місячного бюджету
Виконав: Сукач Андрій (ШІ-14)
*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Фунції(прототипи)
void showMenu();
void daySpent(int n,float spending[]);
void minMax(int n, int &dayMin, int &dayMax,float &valueMin, float &valueMax, float spending[]);
float spentSum(int n, float spending[]);
void remBudget(float budget, int n, float spending[]);
void avgSpent(int n, float spending[]);
void lastDay(int n,float budget, float spending[]);
void overLim(int n, float spending[], float dayLim = 1000.0f);
void topThreeSpending(int n, float spending[]);

int main(){

      cout << fixed << setprecision(2); // Виведення у форматі 2 цифр після коми

float budget;
int n;
float spending[31];
int choice;

//введення базових данних і перевірка
 cout << "Введіть ваш бюджет: ";
while(!(cin >> budget) || budget < 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введіть додатнє число" << endl;
        cout << "Введіть ваш бюджет: ";
    }

    cout << "Введіть Кількість днів обліку(ціле число 1-31):";
while(!(cin >> n) || n < 0 || n > 31)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введіть ціле число(1-31)" << endl;
        cout << "Введіть Кількість днів обліку(ціле число 1-31):";
    }

cout << "Введіть витрати по днях(грн):";
for (int i = 0; i < n; i++){
    while(!(cin >> spending[i]))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введіть число" << endl;
        cout << "Введіть витрати по днях(грн):";
    }
}
// дані для деяких функцій
int dayMin, dayMax;
float valueMin, valueMax;

menu: // точка куда піде goto
//цикл вибору пунктів
do {
    showMenu();
    cout << "Введіть ваш вибір" << endl;

    while(!(cin >> choice) || choice < 0 || choice > 4)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка! Введіть ціле число" << endl;
        showMenu();
        cout << "Введіть ваш вибір" << endl;
    }

    switch (choice)
    {
        case 1:
        daySpent(n, spending);
        break;

        case 2:
        minMax(n, dayMin, dayMax, valueMin, valueMax, spending);
        cout << "Сумарні витрати: " << spentSum(n, spending) << endl;
        remBudget(budget, n, spending);
        avgSpent(n, spending);
        lastDay(n, budget, spending);
        break;

        case 3:
        float dayLim;
        cout << "Введіть денний ліміт(якщо 0, то за замовчуванням 1000 грн.):" << endl;
         while(!(cin >> dayLim) || dayLim < 0)
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Помилка! Введіть додатнє число" << endl;
                    cout <<"Введіть денний ліміт(якщо 0, то за замовчуванням 1000 грн.):" << endl;
                }
                if (dayLim == 0) {
    
                    overLim(n, spending); 
                     } else {
                            overLim(n, spending, dayLim); 
                                }
                break;
        case 4:
        topThreeSpending(n, spending);
        break;

         case 0:
                cout << "Вихід з програми" <<endl;
                break;
        default:
        cout << "Невідомий вибір";
                goto menu;
    }

} while (!(choice ==0 ));

return 0;
}

//функція яка виводить меню
void showMenu(){
    cout << endl;
    cout << "Меню" << endl;
    cout << "1 - Показати витрати по днях" << endl;
    cout << "2 - Статистика витрат" << endl;
    cout << "3 - Дні з перевищенням денного ліміту" << endl;
    cout << "4 - Три найдорожчі дні" << endl;
    cout << "0 - Вийти" << endl;
}
//функція яка рахує витрати по днях
void daySpent(int n, float spending[]){
    cout << endl;
    cout << "Витрати по днях:" << endl;
    for (int i = 0; i < n; i++){
         cout << "день " << i + 1 << "  Витрати: "<< spending[i] << endl;
    }
   
}
//функція яка рахує мінімальні/максимальні витрати за день
void minMax(int n, int &dayMin, int &dayMax,float &valueMin, float &valueMax, float spending[]){
    dayMin = 1; // день з максимальними витратами
    dayMax = 1;// день з мінімальними витратами
    valueMin = spending[0]; // максимальна витрата
    valueMax = spending[0]; // мінімальна витрата
    for (int i = 0; i < n; i++){
        if (spending[i] > valueMax){
            dayMax = (i + 1);
            valueMax = spending[i];
    }
}
    cout << " Найбільші витрати за день " <<  " : " << valueMax << endl;
    for (int i = 0; i < n; i++){
        if (spending[i] < valueMin){
            dayMin = (i + 1);
            valueMin = spending[i];
    }
}
    cout << " Найменші витрати за день " <<  " : " << valueMin << endl;
}
// рекурсивна функція яка рахує суму витрат
float spentSum(int n, float spending[]){
    if (n <=0 ) return 0;// якщо 0 днів то сума 0
//Повертаю витрату за поточний день (n-1) ПЛЮС суму всіх попередніх днів
    return spending [n-1] + spentSum(n-1, spending);

}
// Залишок або перевитрати бюджету
void remBudget(float budget,int n, float spending[]){
    float total = spentSum(n, spending); // сума
    if (budget >= total){
        cout << "Залишок бюджету: " << budget - total << endl;
 } else cout << "перевитрати бюджету: " << abs(total - budget) << endl;
}
//середнє значення
void avgSpent(int n, float spending[]){
    int daySum = 0; // сума днів з покупками
    for (int i = 0; i < n; i++){
        if (spending[i] == 0) continue;// пропуск днів в яких 0 витрат
        daySum++;
    }
    cout << "Днів з покупками: " << daySum << endl;
    if (daySum > 0){
        float avg = (spentSum(n, spending) / daySum);
        cout << "Середні витрати = "  << avg << endl;
    } else cout << "Середні витрати = 0" << endl;
}
// день на якому вичерпався бюджет
void lastDay(int n,float budget, float spending[]){
    int daysLeft = 0;
    float sum = 0; // кастомна сума для провірки
    while (daysLeft < n){
        sum += spending[daysLeft];
        
        if (sum > budget) {
            cout << "Бюджет було вичерпано на дні №" <<  (daysLeft + 1) << ", накопичено суму: " << sum << " грн." << endl;
        break;
       }
       daysLeft++;
    }
}
// кількість днів з перевищенням ліміту
void overLim(int n, float spending[], float dayLim){
    cout << "Дні з перевищенням ліміту (" << dayLim << " грн):" << endl;
    int overLimDaySum = 0; //сума таких днів
    for (int i = 0; i < n; i++){
        if (spending[i] > dayLim){
            cout << "День " << (i + 1) << ": " << spending[i] << " грн" << endl; 
            overLimDaySum++;
        }
    }
    cout << "Загалом днів які перевищили ліміт = " <<  overLimDaySum << endl;
}

void topThreeSpending(int n, float spending[]){
    float A[31];
    cout << "Топ 3 витрат: ";
    for (int i = 0; i < n; i++){ // перезапис в новий масив
        A[i] = spending[i];
    }

    int limit = (n < 3) ? n : 3; //якщо днів менше 3, + змінна ліміта на n

    for (int i = 0; i < limit; i++) {
        float maxVal = -1.0;
        int maxDay = -1;     

        for (int j = 0; j < n; j++) {
            if (A[j] > maxVal) {
                maxVal = A[j];
                maxDay = j;
            }
        }
        cout << maxVal << "; ";
        A[maxDay] = -1.0; // стираю цей елемент і повторюю цикл щоб знайти другий
    }
    
}