#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void outSpending(double a[], int n){
    cout << endl << "День     Витрати, грн" << endl;
    for(int i = 0; i < n; i++){
        cout << setw(4) << (i + 1) << setw(15) << fixed << setprecision(2) << a[i] << endl;
    }
} 
void getMinMax(const double a[], int n, double &min, double &max) {
    min = max = a[0];
    for(int i = 1; i < n; i++){
        min = (min > a[i])? a[i] : min;
        max = (max < a[i])? a[i] : max;
    }
}
double getSum(const double a[], int n) {
    return n <= 0 ? 0.0 : a[n - 1] + getSum(a, n - 1);
}
void stats( double spending[], int n, int budget){

    cout << fixed << setprecision(2) << endl;
    double min = 0;
    double max = 0;
    getMinMax(spending, n, min, max);
    cout << "Мінімальні витрати за день: " << min << " грн" << endl
         << "Максимальні витрати за день: " << max << " грн" << endl;

    double total = getSum(spending, n);
    cout << "Сумарні витрати:" << total << " грн" << endl;

    double overdraft = budget - total; 
        cout << "Залишок бюджету: " << fabs(overdraft)  << " грн" << endl;

    int purchaseDays = 0;
    double sumPurchase = 0;
    for(int i = 0; i < n; i++){
        if(spending[i] == 0){
            continue;
        }
        purchaseDays++;
        sumPurchase += spending[i];
    }

    cout << "Днів з покупками: " << purchaseDays << endl
        << "Середні витрати за такий день: " << (purchaseDays ? sumPurchase / purchaseDays : 0.0) << " грн" << endl;

    double accum = 0;
    int day = 0, exhaustedDay = -1;
    while (day < n) {
        accum += spending[day];
        if (accum > budget) {
            exhaustedDay = day + 1;
            break;
        }
        day++;
    }

    if (exhaustedDay != -1) 
        cout << "Бюджет вичерпано на дні: " << exhaustedDay << ", накопичено " << accum << " грн." << endl;
    else 
        cout << "Бюджету вистачило на всі дні." << endl;
}
void exceedLimit(double a[], int n, double limit = 1000){
    if(limit == 0) limit = 1000; 
    cout << fixed << setprecision(2) << endl;
    cout << "Ліміт: " << limit << " грн" << endl;

    int daysCount = 0;
    for( int i = 0; i < n; i++){
        if( a[i] > limit){
            daysCount++;
            cout << "  день " << (i + 1) << ": " << a[i] << " грн" << endl;
        }
    }
    
    cout << "Разом днів з перевищенням: " << daysCount << endl;

}
void top3(double a[], int n){
    double arrTmp[n];
    for( int i = 0; i < n; i++){
        arrTmp[i] = a[i];
    }
    for( int i = 0; i < n; i++){//bubble sort
        bool swapped = false;
        for( int j = 0; j < n - 1 - i; j++){
            if(arrTmp[j] < arrTmp[j+1]){
                double tmp = arrTmp[j];
                arrTmp[j] = arrTmp[j+1];
                arrTmp[j+1] = tmp;
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
    }
    int count = (n < 3) ? n : 3;
    cout << fixed << setprecision(2) << endl << "Топ-" << count << " витрат: ";
    for (int i = 0; i < count; ++i) {
        cout << arrTmp[i] << (i < count - 1 ? ", " : "");
    }
    cout << " грн\n";
}
int main() {

    double budget = 0;
    cout << "Бюджет на місяць (грн): ";
    while(!(cin>>budget) || budget < 1){
        cout<<"err";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    int N = 0;
    cout << "Кількість днів обліку: ";
    while(!(cin >> N) || N < 1 || N > 31){
        cout<<"err";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    
    double spendings[N];
    cout << "Витрати по днях (грн): ";
    for(int i = 0; i < N; i++){
        while(!(cin >> spendings[i]) || spendings[i] < 0){
            cout<<"err";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int input_option = 0;
    do{
        menu:
        cout << endl << "Меню:" << endl;
        cout << "1. Показати витрати по днях" << endl;
        cout << "2. Статистика витрат" << endl;
        cout << "3. Дні з перевищенням денного ліміту" << endl;
        cout << "4. Три найдорожчі дні" << endl;
        cout << "0. Вийти" << endl;
        cout << "Виберіть пункт: ";
        cin >> input_option;
        if(cin.fail() || input_option > 4 || input_option < 0){
            cout << "Неправильний пункт меню! Спробуйте ще раз." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto menu;
        }
        switch(input_option){
            case 1:
                outSpending(spendings, N);
                break;
            case 2:
                stats(spendings, N, budget);
                break;
            case 3:
                double limit;
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                if (!(cin >> limit) || limit < 0) {
                    cout << "Некоректне значення ліміту! Повернення до меню...\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    goto menu;
                }
                exceedLimit(spendings, N, limit);
                break;
            case 4:
                top3(spendings, N);
                break;
            case 0:
                cout << "Завершення роботи програми." << endl;
                break;
            default:
                break;
        }
    }
    while( input_option != 0 );
    
    return 0;
} 