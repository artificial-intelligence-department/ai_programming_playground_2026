/*
Практичне завдання №1
Станіслав Коваль
ШІ-12
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

void spending_day(int N, double *spending) {
    cout << "День " << "Витрати, грн" << endl;
    for (int i = 0; i < N; i++) {
        cout <<" " << i + 1 << "    " << spending[i] << endl;
    }
}

void min_max_spending(int N, double *spending,double &min, double &max){
    min = *min_element(spending, spending + N);
    max = *max_element(spending, spending + N);
}

double spending_sum(int N, double *spending) {
    if (N == 0) {
        return 0;
    }
    else {
        return spending[N - 1] + spending_sum(N - 1, spending); 
    }
}

void spending_statistics(int N, double *spending, double budget){
    double min = 0, max = 0;
    min_max_spending(N, spending, min, max);
    cout << "Мінімальні витрати: " << min << " грн" << endl;
    cout << "Максимальні витрати: " << max << " грн" << endl;

    double sum =spending_sum(N, spending);
    cout << "Сумарні витрати за місяць: " << sum << " грн" << endl;
    
    if (sum > budget) {
        cout << "Перевитрата понад бюджет: " << fabs(budget - sum) << "грн" << endl;
    }
    else {
        cout << "Залишок бюджету: " << budget - sum << "грн" << endl;
    }

    int count = 0;
    for (int i = 0; i < N; i++) {
        if (spending[i]==0) {
            continue;
        }
        else{
            count++;
        }
    }
    cout << "Днів з покупками: " << count << endl;
    cout << "Середні витрати за такий день: " << sum / count << " грн" << endl;

    double Budget = budget;
    int day = 0;
    while (day < N) {
        Budget -= spending[day];
        day++;
        if (Budget < 0) {
            break;
        }
    }
    if (Budget < 0) {
        cout << "Бюджет закінчився на: " << day << " день, " << "накопичено " << sum << " грн" << endl;
    }
    else{
        cout << "Залишок : " << Budget << " грн" << endl; 
    }
}

void daily_limit (double *spending, int N, double limit=1000) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (spending[i] > limit) {
            cout << "Перевищення ліміту на день " << i + 1 << ": " << spending[i] << " грн" << endl;
            count++;
        }
    }
    cout << "Разом днів з превищеням: " << count << endl;
}

void the_most_expensive_days(double *spending, int N) {
    double cspending[N];
    for (int i = 0; i < N; i++) {
        cspending[i] = spending[i];
    }
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (cspending[j] < cspending[j + 1]) {
                swap(cspending[j], cspending[j + 1]);
            }
        }
    }
    if (N < 3) {
        for (int i = 0; i < N; i++) {
            cout << "День " << i + 1 << ": " << cspending[i] << " грн" << endl;
        }
    }
    else {
        cout << "Топ 3 дні з найбільшими витратами: " << cspending[0] << ", " << cspending[1] << ", " << cspending[2] << " грн" << endl;
    }
    
}

int main () {
    cout << fixed << setprecision(2);
    double budget;
    cout << "Бюджет на місяць, грн: ";
    cin >> budget;
    int N;
    cout << "Кількість днів обліку: ";
    cin >> N;
    if (N <= 0 || N > 31) {
        cout << "Помилка: кількість днів має бути в межах від 1 до 31" << endl;
        return 1;
    }
    
    double spending[N];
    cout << "Витрати по днях, грн: ";
    for (int i = 0; i < N; i++) {
        cin >> spending[i];
        if (spending[i] < 0) {
            cout << "Помилка: витрати не можуть бути від'ємними" << endl;
            return 1;
        }
    }

    double limit;
    do {
        cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
        cin >> limit;
        if (limit == 0) {
            limit = 1000;
            break;
        }
        else if (limit < 0) {
            cout << "Помилка: денний ліміт не може бути від'ємним" << endl;
        }   
    } while (limit < 0);
    cout << "Денний ліміт: " << limit << " грн" << endl;

    int choice=0;
    do {
        cout << "=== МЕНЮ ===" << endl;
        cout << "1. Показати витрати по днях" << endl;
        cout << "2. Статистика витрат" << endl;
        cout << "3. Дні з перевищенням денного ліміту" << endl;
        cout << "4. Три найдорожчі дні" << endl;
        cout << "0. Вихід" << endl;
        
        input:
            cout << "Виберіть опцію: ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(1000, '\n');
                choice = -1;
            }

        switch (choice)
        {
        case 1:
            spending_day(N, spending);
            break;
        case 2:
            spending_statistics(N, spending, budget);
            break;
        case 3:
            daily_limit(spending, N, limit);
            break;
        case 4:
            the_most_expensive_days(spending, N);
            break;
        case 0:
            cout << "Вихід з програми." << endl;
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз." << endl;
            goto input;
        }
    } while (choice != 0);
    return 0;
}