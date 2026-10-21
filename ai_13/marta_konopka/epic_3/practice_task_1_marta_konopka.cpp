/*
Аналізатор місячного бюджету
Конопка Марта ШІ-13
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int MAX = 31; // максимально можлива кількість днів у місяці

//Витрати по днях
void expenses (double spending[], int N){
     cout << "День " << setw(20)<< "Витрати, грн" << endl;
        int days = 0;
        for (int i = 0; i < N; i++) {
            days++;
            cout << days << setw(10) << fixed << setprecision(2) << spending[i] << endl;
}
}

// Мінімальні та максимальні витрати
void minMax( double spending[], int N, double &mn, double &mx){
    mn = spending[0];
    mx = spending[0];

    for(int i = 0; i < N; i++) {
        if(spending[i] < mn){
            mn = spending[i];
        }
        if(spending[i] > mx){
            mx = spending[i];
        

        }
    }
    cout << "Мінімальні витрати: " << fixed << setprecision(2) << mn << " грн" << endl;
    cout << "Максимальні витрати: " << fixed << setprecision(2) << mx << " грн" << endl;
}

// Сумарні витрати
double total(double spending[], int N){
    if(N == 0 ){
    return 0;
}
    return spending[N - 1] + total(spending, N - 1);
    
} 

// Залишок або перевитрати бюджету
void remainBudget(double budget, double spending[], int N){
    double remain = 0;
    double overspending = 0;
    remain =  budget - total(spending, N);
    cout << "Сумарні витрати: " << total(spending, N) << " грн" << endl;

         if(budget < total(spending, N)){
         overspending = fabs(remain); 
         cout << "Перевитрати: " << overspending << " грн" <<  endl; 
         }
         else {
          cout << "Залишок бюджету: " << remain << " грн" << endl;
         }
    
}

// Середні витрати за дні з покупками 
void averageExp(double spending[], int& N){
           int valid = 0;
           double sum = 0;
           int days = 0;
           double average = 0 ;

           for(int i = 0; i < N; i++){
            if(spending[i] == 0)
            continue;
            sum += spending[i]; 
            days ++;
            valid++ ;
           }
              if(valid > 0){
                average = sum / valid; 
              }
              else average = 0; 
            
            cout << "Днів з покупками: " << days << endl;
            cout << "Середні витрати: " << fixed << setprecision(2) << average << " грн" << endl; 
           

}

// День вичерпання бюджету
void exhaustedBud(double spending[], int N, double budget){
            int i = 0;
            double totalexp = 0;
            int day = 0; 
            while(i < N){
            totalexp += spending[i]; 
            i++ ; 
             if(totalexp > budget){
                day = i;
                   break;    
              }
            }
            if (totalexp > budget){
                cout << "Бюджет вичерпано на дні " << day << ", накопичено " << totalexp << " грн" << endl;
            }
            else{
                double balance = budget - totalexp;
                cout << "Бюджету вистачило на всі дні. Залишок: " << fixed << setprecision(2) << balance << " грн" << endl;
            }

}

// Дні з перевищенням денного ліміту
void exceedLimit(double spending[], int N, double limit = 1000) {
    cout << "Ліміт: " << limit << " грн" << endl;
    int exceed = 0; 
     int day = 0; 
    for(int i = 0; i < N; i++){
        if(spending[i] > limit){
            day = i + 1;
            exceed++;
             cout << "день " << day << ": " << fixed << setprecision(2) << spending[i] << " грн" << endl;
        }

    } 
    cout << "Разом днів із перевищенням: " << exceed << endl;

}

// Три найдорожчі дні
void costlyDays( double spending[], int N) {
    double copy[MAX] ;
     for(int i = 0; i < N; i++){
        copy[i] = spending[i];
    }
        for(int i = 0; i < N - 1; i++){
        for(int j = 0; j < N - i - 1; j++){
    if (copy[j] < copy[j + 1] ) {
        double t = copy[j];
        copy[j] = copy[j +1];
        copy[j + 1] = t;
    }

        }
}
int limit ;
if (N < 3) {
    limit = N;
} 
else{
    limit = 3;
}
    cout << "Топ-" << limit << " витрат: ";
    for(int i = 0; i < limit ; i++){
        cout << fixed << setprecision(2) << copy[i];
        if (i < limit - 1){
            cout << ", ";
        }
    }
 cout << " грн" << endl; 
}

int main() { 

double spending[MAX]; 
double budget;
int N;
int choice;
double remain;
double overspending;
double average;
int day = 0;
double limit;
double mx;
double mn;

// Ввід та валідація бюджету
budget:
cout << "Бюджет на місяць (грн): "; 
cin >> budget;
if (cin.fail() || budget <= 0 ){
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введіть додатнє ціле або дробове число" << endl; 
    goto budget; 

    
}
// Ввід та валідація кількості днів обліку
N: 
cout << "Кількість днів обліку: ";
cin >> N; 
if(cin.fail() || N <= 0 || N > MAX) { 
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введіть ціле число (1 - 31)" << endl; 
    goto N; 
}

// Ввід та валідація витрат за кожен день
spending:
cout << "Витрати по днях (грн): ";

for (int i = 0; i < N; i++) {
    cin >> spending[i];
if(cin.fail() || spending[i] < 0){
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введіть додатнє ціле або дробове число" << endl; 
    goto spending; 
}
}

do{
    menu: 
    cout << "Оберіть операцію із списку меню: " << endl;
    cout << "1 - Показати витрати по днях " << endl;
    cout << "2 - Статистика витрат" << endl;
    cout << "3 - Дні з перевищенням денного ліміту" << endl;
    cout << "4 - Три надорожчі дні" << endl;
    cout << "0 - вийти" << endl;

    // Перевірка некоректного введення пунктів меню
    cin >> choice;
    if (cin.fail()){
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ви ввели некоректне значення" << endl;
        goto menu; 
    }
    // Обробка пунктів меню
    switch(choice){
     
     case 1: {
        expenses(spending, N);
        break;
     }
     case 2: {
        minMax(spending, N, mn, mx); 
        remainBudget(budget, spending, N);
        averageExp(spending, N);
        exhaustedBud(spending, N, budget);
        break;
    }
    case 3: {
    limit:
    cout << "Введіть денний ліміт(грн, 0 = за замовчуванням): ";
    cin >> limit;
    if(cin.fail() || limit < 0) {
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введіть додатнє ціле або дробове число" << endl; 
    goto limit; 
    }

    if(limit == 0){
    exceedLimit(spending, N); 
    }
    else{
     exceedLimit(spending, N, limit);
    }
    break;
}
 case 4: {
    costlyDays(spending, N);
    break;
}
case 0: {
    cout << "Завершення роботи програми" << endl;
    break;
}
default : 
cout << "Ви ввели некоректне значення " << endl;
goto menu; 
    }
}

while(choice != 0);

return 0;
}