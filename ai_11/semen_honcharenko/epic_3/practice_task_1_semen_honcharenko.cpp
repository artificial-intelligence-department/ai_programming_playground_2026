/*
    Практичне завдання "Аналізатор місячного бюджету"
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
// spendings summary
void spendSumDay(float arr[], int n) {
    cout << right << setw(10) << "День" << setw(37) << "Витрати, грн" << endl;
            cout << fixed << setprecision(2);
            for (int i = 0; i < n; i++) {
                cout << right << setw(6) << (i+1) << setw(27) << arr[i] << endl;
            }
}
// finding min in array
float minSpent(float arr[], int size) {
    float min = arr[0];
            for (int i = 0; i < size; i++) {
                if (arr[i] < min) {
                    min = arr[i];
                }
            }
            return min;
}
// finding max in array
float maxSpent(float arr[], int size) {
    float max = arr[0];
            for (int i = 0; i < size; i++) {
                if (arr[i] > max) {
                    max = arr[i];
                }
            }
            return max;
}
float sumSpent(float arr[], int size) {
    if (size <= 0) {
        return 0;
    }
    return arr[size - 1] + sumSpent(arr, size - 1);
}
int daysSpent(float arr[], int size) {
    int days = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] != 0) {
            days++;
        }
    }
    return days;
}
void dayEnd(float arr[], int size, float money) {
    int day = 0;
    float spent = 0;
    while (day < size) {
        money -= arr[day];
        spent += arr[day];
        day++;
        if (money <= 0) {
            break;
        }
    }
    if (money > 0) {
        cout << "Бюджет не вичерпано" << endl;
    }
    else {
        cout << "Бюджет вичерпано на дні " << day << ", накопичено " << spent << " грн.";
    }
    }
float overSpent(float arr[], int size, float money) {
    float total = sumSpent(arr, size);
    if (total > money) {
        return fabs(total - money);
    }
    return 0;
}
float averSpent(float arr[], int size) {
    float sum = 0;
    int total = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            continue;
        }
        sum += arr[i];
        total++;
    }
    if (total == 0) {
        return 0;
    }
    return sum / total;
}
void overLimit(float arr[], int size, float limit) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > limit) {
            sum++;
            cout << "\tдень " << i+1 << ": " << arr[i] << " грн" << endl;
        }
    }
    cout << "Разом днів з перевищенням: " << sum << endl;
}
void arrCopy(float arr[], float arr_copy[], int size) {
    for (int i = 0; i < size; i++) {
        arr_copy[i] = arr[i];
    }
}
void sortSpent(float arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (arr[j+1] > arr[j]) {
                float a = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = a;
            }
        }
    }
}
void topSpent(float arr[], int size) {
    cout << "Топ-3 витрат: ";
    for (int i = 0; i < size; i++) {
        cout << fixed << setprecision(2) << arr[i] << ", ";
        if (i == 2) {
            break;
        }
    }
    cout << "грн.";
}
int main () {
    float budget = 0.0f; //  budget for a month
    int N = 0; // days count (31 max)
    float spending[31] = {}; // money spent each day
budget_input:
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    if (budget < 0 or cin.fail()) {
        cout << "Помилка. Бюджет повинен бути числом більшим або рівним 0" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        goto budget_input;
    }
    cin.clear();
    cin.ignore(1000, '\n');
days_count:
    cout << "Кількість днів обліку: ";
    cin >> N;
    if (N <= 0 or N > 31 or cin.fail()) {
        cout << "Помилка. Кількість днів повинна бути цілим натуральним числом меншим за 32" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        goto days_count;
    }
    cin.clear();
    cin.ignore(1000, '\n');
spendings:
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < N; i++) {
        cin >> spending[i];
        if (spending[i] < 0 or cin.fail()) {
            cout << "Помилка. Витрата в день повинна бути числом більшим або рівним 0" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        goto spendings;
    }
}
    cin.clear();
    cin.ignore(1000, '\n');
    
    int choice = 5;
    float daily_limit = 0;
    float arr_copy[31] = {};
    menu:
    do {
        cout << endl << endl
        << "1 - Показати витрати по днях" << endl 
        << "2 - Статистика витрат" <<  endl 
        << "3 - Дні з перевищенням денного ліміту" << endl
        << "4 - Три найдорожчі дні" << endl 
        << "0 - Вийти" << endl << endl;

    cout << "Пункт: ";
    cin >> choice;
    if (cin.fail()) {
        cout << "Помилка. Треба ввести число від 0 до 4" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        goto menu;
    }
    cin.clear();
    cin.ignore(1000, '\n');
    switch (choice) {
        case 1:
            spendSumDay(spending, N);
            break;
        case 2:
            cout << fixed << setprecision(2);
            cout << "Мінімальні витрати за день:   " << right << setw(10) << minSpent(spending, N) << " грн" << endl;
            cout << "Максимальні витрати за день:  " << right << setw(10) << maxSpent(spending, N) << " грн" << endl;
            cout << "Сумарні витрати:              " << right << setw(10) << sumSpent(spending, N) << " грн" << endl;
            cout << "Перевитрата понад бюджет:     " << right << setw(10) << overSpent(spending, N, budget) << " грн" << endl;
            cout << "Днів з покупками:             " << right << setw(10) << daysSpent(spending, N) << endl;
            cout << "Середні витрати за такий день:" << right << setw(10) << averSpent(spending, N) << " грн" << endl;
            dayEnd(spending, N, budget);
            break;
        case 3:
        limit:
            cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
            cin >> daily_limit;
            if (daily_limit < 0 or cin.fail()) {
                cout << "Помилка. Ліміт має бути числом не меншим за 0" << endl << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                goto limit;
            }
            if (daily_limit == 0) {
                daily_limit = 1000;
            }
            cout << "Ліміт: " << daily_limit << endl;
            overLimit(spending, N, daily_limit);
            break;
        case 4:
            arrCopy(spending, arr_copy, N);
            sortSpent(arr_copy, N);
            topSpent(arr_copy, N);
            break;
        case 0:
            cout << "Завершення програми..." << endl;
            return 0;
        default:
            cout << "Помилка. Число повинно бути від 0 до 4" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            break;
        }
    } while (choice != 0);
}