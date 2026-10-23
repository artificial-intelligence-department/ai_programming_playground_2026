/*
Назва: Аналізатор місячного бюджету
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
#include <clocale>
#include <iomanip>
#include <cmath>
using namespace std;

void DailySpending(const double spending[], int N){//Витрати по днях
    cout << fixed << setprecision(2)<< endl;
    cout << setw(5)  << "\nДень" << setw(30) << "Витрати, грн" << endl;
    for(int i=0; i<N; i++){
        cout << setw(4) << i+1 << setw(20) << spending[i] << endl;
    }
}

void MinMax(const double spending[], int N, double &minVal, double &maxVal){// Знаходимо мін. та макс. значення
    minVal = maxVal = spending[0];
    for(int i=1; i<N; i++){
        if (spending[i] < minVal){
            minVal = spending[i];
        }
        if (spending[i] > maxVal){
           maxVal = spending[i];
        }
    }
}
double findsum(const double spending[], int N){//Обчисленя загальних витрат за допомогою рекурсивної функції
    if (N <= 0) {
        return 0;
    }
    return spending[N - 1] + findsum(spending, N - 1);
}
void Statistic(const double spending[], int N, double budget){//Вивід статистики
    cout << fixed << setprecision(2)<< endl;

    double minVal = 0;
    double maxVal = 0;
    //Виклик функції MinMax
    MinMax(spending, N, minVal, maxVal);
    cout << "Мінімальні витрати за день: " << setw(14) << minVal << " грн." << endl;
    cout << "Максимальні витрати за день: " << setw(13)<< maxVal << " грн." <<  endl;

    double sum = findsum(spending, N);

    cout << "Сумарні витрати: " << setw(25) << sum <<" грн." << endl;
    double resultSpending = abs(budget - sum);
    if(sum > budget){
        cout << "Перевитрата понад бюджет: " << setw(16) << resultSpending <<" грн." << endl;
    }
    else {
        cout << "Залишок бюджету: " << setw(25) << resultSpending <<" грн." << endl;
    }
    
    
    
    int spendingDays = 0;
    for(int k = 0; k < N; k++){
        if(spending[k] == 0){
            continue;
        }
        spendingDays++;
    }
    cout << "Днів з покупками" << setw(25) << spendingDays << endl;
    double average = 0;
    if(sum == 0){
        average = 0;
    }
    else{
        average = sum/spendingDays;
    }
    cout << "Середні витрати за такий день: " << setw(12) << average <<" грн." << endl;

    double spendingSum = 0;
    int i=0;
    while (i < N){
        spendingSum += spending[i];
        
        if(budget <= spendingSum){
            cout << "Бюджет вичерпано на дні " << i+1 <<", накопичено " << spendingSum <<" грн." << endl;
            break;
        }
        i++;
    }

}
void checkLimit(const double spending[], int N, double limit = 1000){
    cout << fixed << setprecision(2);
    int TotalDays=0;
    cout << "Ліміт: " << limit << endl;
    for (int i = 0; i < N; i++) {
        if(spending[i] >= limit){
            cout << "  день " << i+1 <<": " << spending[i] << " грн" << endl;
            TotalDays++;
        }
    }
    cout << "Разом днів з перевищенням: " << TotalDays << endl;
}
void Top3(const double spending[], int N){
    cout << fixed << setprecision(2)<< endl;
    double copyArr[N];
    for (int i = 0; i < N; i++) {
        copyArr[i] = spending[i];
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (copyArr[j] > copyArr[i]) { 
                double temp = copyArr[i];
                copyArr[i] = copyArr[j];
                copyArr[j] = temp;
            }
        }
    }
    cout << "Топ-3 витрат: " << copyArr[0];
    for(int i = 1; i < 3 && i < N; i++){
        if(copyArr[i] == 0.0){
            break;
        }
        cout << ", " << copyArr[i];
    }
    cout << " " << "грн" << endl;
}

int main(){
    double budget;
    cout << "Бюджет на місяць (грн): ";
    while(!(cin >> budget) or budget < 1 ){
        cout << "Введіть число більше або рівне 1: ";
        cin.clear();
        cin.ignore(100, '\n');
    }
    int N;
    cout << "Кількість днів обліку: ";
    while(!(cin >> N) || N < 1 || N > 31){
        cout << "Введіть число менше 31 або більше 0: ";
        cin.clear();
        cin.ignore(100, '\n');
    }
    
    
    double spending[N];
    cout << "Витрати по днях (грн): ";
    for (int i=0; i < N; i++){
        while(!(cin >> spending[i]) || spending[i] < 0){
        cout << "Введіть числа більші за 0: ";
        cin.clear();
        cin.ignore(100, '\n');
        i = 0;
        }
    }
    int choise=0;
    do{
        MENU:
        cout << fixed << setprecision(2);
        cout << "\n---------- МЕНЮ ------------" << endl;
        cout << "1 - Показати витрати по днях" << endl;
        cout << "2 - Статистика витрат" << endl;
        cout << "3 - Дні з перевищенням денного ліміту" << endl;
        cout << "4 - Три найдорожчі дні" << endl;
        cout << "0 - Вийти" << endl;
        cout << "Ваш вибір: ";
        
        if(!(cin >> choise) || choise < 0 || choise > 4){
        cout << "Введіть коректне значення: ";
        cin.clear();
        cin.ignore(100, '\n');
        goto MENU;
        }
        switch (choise) {
            case 1: 
                DailySpending(spending, N); 
                break;
            case 2: 
                Statistic(spending, N, budget);
                break;
            case 3: {
                double limit;
                cout << "\nДенний ліміт (грн, 0 = за замовчуванням): ";
                if(!(cin >> limit) || limit < 0){
                    cout << "Введіть число більше 0: ";
                    cin.clear();
                    cin.ignore(100, '\n');
                    goto MENU;
                }
                 if (limit == 0) {
                    checkLimit(spending, N);
                } else {
                    checkLimit(spending, N, limit);
                }
                break;
            } 
            case 4: 
                Top3(spending, N);
                break;
            case 0:
                break;
            default: goto MENU;
        }
    } while (choise!=0);
    cout << endl;
    
}
