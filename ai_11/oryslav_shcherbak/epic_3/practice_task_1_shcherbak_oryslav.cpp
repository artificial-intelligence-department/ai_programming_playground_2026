#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
using namespace std;

/* Задача: Practice task 1
* Щербак Орислав
* Група ШІ - 11
*/

void findminmax(double spending[], int n, double &min_spending, double &max_spending){
    min_spending = spending[0];
    max_spending = spending[0];
    for (int i = 1; i < n; ++i){
        if (spending[i] < min_spending){
            min_spending = spending[i];
        }
        if (spending[i] > max_spending){
            max_spending = spending[i];
        }
    }
}
void totalspending(double spending[], int n, double &total_spending){
    total_spending = 0;
    for (int i = 0; i < n; i++){
        total_spending += spending[i];
    }
}
void countdays(double spending[], int n, int &count){
    count = 0;
    for (int i = 0; i < n; ++i){
        if (spending[i] > 0){
            count++;
        }
    }
}

const int max_days = 31;
int main(){
    double budget;
    int n;
    double spending[max_days];
    while(true){
        cout << "Бюджет на місяць (грн): ";
        if(cin >> budget && budget >= 0){
            break;
        }
        cout << "Помилка: бюджет не може бути від'ємним.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    while(true){
        cout << "Кількість днів в обліку (1-" << max_days << "): ";
        if(cin >> n && n >= 1 && n <= max_days){
            break;
        }
        cout << "Помилка: введіть ціле число від 1 до " << max_days << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    for (int i = 0; i < n; ++i){
        while(true){    
            cout << "Витрати за день " << (i + 1) << " (грн): ";
            if(cin >> spending[i] && spending[i] >= 0){
                break;
            }
            cout << "Помилка: витрати не можуть бути від'ємними.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    int choice;
    do {
        menu:
        cout << "1. Показати витрати по днях" << endl;
        cout << "2. Статистика витрат" << endl;
        cout << "3. Дні з перевищенням денного ліміту" << endl;
        cout << "4. Три найдорожчі дні" << endl;
        cout << "0. Вихід" << endl;
        if (!(cin >> choice)) {
            cout << "Помилка: введіть номер пункту." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto menu;
        }

        switch (choice){
        case 1:
            for(int i = 0; i < n; ++i){
                cout << "День " << (i + 1) << ": " << spending[i] << " грн" << endl;
            }
            break;
        case 2: {
            // Статистика витрат
            double min_spending, max_spending;
            findminmax(spending, n, min_spending, max_spending);
            cout << "Мінімальні витрати: " << min_spending << " грн" << endl;
            cout << "Максимальні витрати: " << max_spending << " грн" << endl;

            double total_spending = 0;
            totalspending(spending, n, total_spending);
            cout << "Сумарні витрати: " << total_spending << " грн" << endl;
            if (total_spending > budget) {
                cout << "Перевитрата понад бюджет: " << (total_spending - budget) << " грн" << endl;
            } else {
                cout << "Залишок бюджету: " << (budget - total_spending) << " грн" << endl;
            }   
            int count = 0;
            countdays(spending, n, count);
            cout << "Кількість днів з витратами: " << count << endl;
            if (count > 0) {
                cout << "Середні витрати за такий день: " << (total_spending / count) << " грн" << endl;
            } else {
                cout << "Середні витрати за такий день: 0 грн" << endl;
            }

            double accumulated = 0;
            int day = 0;
            bool exceeded = false;
            while (day < n) {
                accumulated += spending[day];
                if (accumulated > budget) {
                    cout << "Бюджет вичерпано на дні " << (day + 1) << ", накопичено " << accumulated << " грн" << endl;
                    exceeded = true;
                    break;
                }
                ++day;
            }
            if (!exceeded) {
                cout << "Бюджет не перевищено протягом усього періоду. Залишок бюджету: " << (budget - accumulated) << " грн" << endl;
            }
            break;
        }
        case 3: {
            double daybudget;
            int countlimit = 0;
            cout << "Денний ліміт (грн, 1000 = за замовчуванням): ";
            cin >> daybudget;
            if(daybudget == 0){
                daybudget = 1000;
            }
            cout << "Ліміт: " << daybudget << " грн" << endl;
            for (int i = 0; i < n; ++i) {
                if (spending[i] > daybudget) {
                    countlimit++;
                    cout << "День " << (i + 1) << ": " << spending[i] << " грн" << endl;
                }
            }
            cout << "Кількість днів з перевищенням денного ліміту: " << countlimit << endl;
            break;
        }
        case 4: {
            double copy[max_days];
            for (int i = 0; i < n; ++i){
                copy[i] = spending[i];
            }
            cout << "Три найдорожчі дні: " << endl;
            for (int i = 0; i < 3 && i < n; ++i) {
                int max_index = 0;
                for (int j = 1; j < n; ++j) {
                    if (copy[j] > copy[max_index]) {
                        max_index = j;
                    }
                }
                cout << "День " << (max_index + 1) << ": " << copy[max_index] << " грн" << endl;
                copy[max_index] = -1;
            }
            break;
        }
        case 0:
            cout << "Роботу завершено." << endl;
            break;
        default:
            cout << "Помилка: введіть номер пункту." << endl;
            goto menu;
        }
    } while (choice != 0);
    return 0;
}