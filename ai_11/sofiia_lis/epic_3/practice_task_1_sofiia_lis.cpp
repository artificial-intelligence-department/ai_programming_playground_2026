/* 
Епік 3. practice_task_1_sofiia_lis.cpp
Авторка: Софія Ліс
Група: ші-11
*/
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// функція для виведення витрат по днях
void spnd_per_day(double spending[], int n) {
    cout << "День   Витрати, грн" << endl;
    for(int i = 0; i < n; i++) {
        cout << right << setw(4) << i + 1 << "   " << fixed << setprecision(2) << right << setw(12) << spending[i] << endl;
    }

}

// функція для обрахунку мінімальних та максимальних витрат
void min_max(double spending[], int n, double &min, double &max) {

    min = spending[0];
    max = spending[0];

    for(int i = 0; i < n; i++) {
        if(min > spending[i]) {
            min = spending[i];
        }
        if(max < spending[i]) {
            max = spending[i];
        }
    }
}

// рекурсивна сума перших n елементів
double sum_recursive(double spending[], int n) {
    if(n == 0) {
        return 0;
    }
    return spending[n - 1] + sum_recursive(spending, n - 1);
}

// функція для статистики витрат
void statistics(double spending[],int n, double budget) {

    double min, max;
    min_max(spending, n, min, max);

    cout << fixed << setprecision(2);

    cout << "Мінімальні витрати за день:   " << setw(8) << min << " грн" << endl;
    cout << "Максимальні витрати за день:  " << setw(8) << max << " грн" << endl;
    
    double sum = sum_recursive(spending, n);

    cout << "Сумарні витрати:              " << setw(8) << sum << " грн" << endl;

    double balance = budget - sum;
    if(balance < 0) {
        cout << "Перевитрата понад бюджет:     " << setw(8) << fabs(balance) << " грн" << endl;
    
    }
    else {
        cout << "Залишковий бюджет:            " << setw(8) << balance << " грн" << endl;
    }

    double sum_purchases = 0;
    int purchase_days = 0;

    for(int i = 0; i < n; i++) {
        if(spending[i] == 0) {
            continue;
        }
        sum_purchases += spending[i];
        purchase_days += 1;
    }

    cout << "Днів з покупками:             " << setw(8) << purchase_days << endl;

    if(purchase_days > 0) {
        cout << "Середні витрати за такий день:" << setw(8) << sum_purchases / purchase_days << " грн" << endl;
    }
    else {
        cout << "Середні витрати за такий день: покупок не було" << endl;
    }

    double sum_over = 0;
    int i = 0;

    while(sum_over <= budget) {
        if(i >= n) {
            cout << "Залишок: " << budget - sum_over << " грн" << endl;
            break;
        }
        sum_over += spending[i];
        
        if(sum_over > budget) {
            cout << "Бюджет вичерпано на дні " << i + 1 << ", накопичено " << sum_over << " грн." << endl;
            break;
        }
        i++;
    }
}

// функція для виведення днів з перевищенням денного ліміту
void overlimit(double spending[], int n, double limit = 1000) {
    double cinlimit;
    cout << fixed << setprecision(2);
    cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
    cin >> cinlimit;
    while(cin.fail() || cinlimit < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Некоректне значення. Введіть ліміт ще раз: ";
        cin >> cinlimit;
    }
    if(cinlimit == 0) {
        cinlimit = limit;
    }
    cout << "Ліміт: " << cinlimit << " грн" << endl;
    int overdays = 0;
    for(int i = 0; i < n; i++) {
        if (spending[i] > cinlimit) {
            overdays += 1;
            cout << "  день " << i + 1 << ": " << spending[i] << " грн" << endl;
        }

    }
    cout << "Разом днів з перевищенням: " << overdays << endl;
}

// функція для виведення трьох найдорожчих днів
void topspendings(double spending[], int n) {
    cout << setprecision(2) << fixed;
    double spending_copy[31];
    for (int i = 0; i < n; i++) {
        spending_copy[i] = spending[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (spending_copy[j] > spending_copy[i]) {
                double temp = spending_copy[i];
                spending_copy[i] = spending_copy[j];
                spending_copy[j] = temp;
            }
        }
    }
    int limit = 3;
    if (n < 3) {
        limit = n;
    }

    cout << "Топ-" << limit << " витрат: ";
    for(int i = 0; i < limit; i++) {
        cout << spending_copy[i];
        if (i != limit - 1) {
            cout << ", ";
        }
    }
    cout << " грн" << endl;
}

int main() {

    double budget;
    int n;
    double spending[31];

    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    while(cin.fail() || budget <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Некоректне значення. Введіть бюджет ще раз: ";
        cin >> budget;
    }

    cout << "Кількість днів обліку: ";
    cin >> n;
    while(cin.fail() || n < 1 || n > 31) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Некоректне значення (ціле число від 1 до 31). Введіть ще раз: ";
        cin >> n;
    }

    cout << "Витрати по днях: ";

    for (int i = 0; i < n; i++) {
        cin >> spending[i];
        while(cin.fail() || spending[i] < 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Некоректне значення для дня " << i + 1 << ". Введіть ще раз: ";
            cin >> spending[i];
        }
    }

    // меню

    int action;
    do {
        menu:
        cout << "Пункт  Операція" << endl;
        cout << "1      Показати витрати по днях" << endl;
        cout << "2      Статистика витрат" << endl;
        cout << "3      Дні з перевищенням денного ліміту" << endl;
        cout << "4      Три найдорожчі дні" << endl;
        cout << "0      Вийти" << endl;
        cout << "Оберіть операцію: ";
        cin >> action;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Некоректний пункт меню. Введіть число від 0 до 4." << endl;
            goto menu;
        }
        switch(action) {
            case 1: 
                spnd_per_day(spending, n);
            break;
            case 2: 
                statistics(spending, n, budget);
            break;
            case 3: 
                overlimit(spending, n);
            break;
            case 4: 
                topspendings(spending, n);
            break;
            case 0: 
                cout << "Вихід " << endl;
                break;
            default:
                cout << "Некоректний пункт меню. Введіть число від 0 до 4." << endl;
                goto menu;
        }
    }
    while(action != 0);


    return 0;
}