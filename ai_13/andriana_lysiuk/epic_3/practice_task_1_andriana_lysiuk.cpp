/*
Назва задачі: Аналізатор місячного бюджету
Автор: Лисюк Андріана
Група: ШІ-13
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double budget = 0;
int N = 0;
const int max_days = 31;
double spending[max_days];

void get_min_max(double array_1[], int days, double &arr_min, double &arr_max) {
    arr_min = array_1[0];
    arr_max = array_1[0];
    for (int i = 0; i < days; i++) {
        if (array_1[i] < arr_min) arr_min = array_1[i];
        if (array_1[i] > arr_max) arr_max = array_1[i];
    }
}

void top3(double spending[], int days) {
    double copy_spending[max_days];
    for (int i = 0; i < days; i++) {
        copy_spending[i] = spending[i];
    }

    for (int i = 0; i < days - 1; i++) {
        for (int j = 0; j < days - i - 1; j++) {
            if (copy_spending[j] < copy_spending[j + 1]) {
                double temp = copy_spending[j];
                copy_spending[j] = copy_spending[j + 1];
                copy_spending[j + 1] = temp;
            }
        }
    }

    int count = (days < 3) ? days : 3;
    cout << "Топ-3 витрат: ";
    for (int k = 0; k < count; k++) {
        cout << fixed << setprecision(2) << copy_spending[k] << (k < count - 1 ? ", " : "");
    }
    cout << " грн" << endl;
}

void count_days(double spending[], int days, double budget) {
    double sum = 0;
    int number_day = 0;

    while (number_day < days) {
        sum += spending[number_day];
        number_day++;

        if (sum > budget) {
            break;
        }
    }
    if (sum > budget) {
        cout << "Бюджет вичерпано на дні " << number_day
             << ", накопичено " << fixed << setprecision(2) <<  sum << " грн" << endl;
    } else {
        cout << "Бюджету вистачило на всі дні. Залишок: "
             << fixed << setprecision(2) <<  budget - sum << " грн" << endl;
    }
}

void avg_spending(double array_1[], int number_days) {
    double sum = 0;
    int count = 0;

    for (int i = 0; i < number_days; i++) {
        if (array_1[i] == 0) {
            continue;
        }
        sum += array_1[i];
        count++;
    }
    cout << "Днів з покупками: " << count << endl;
    if (count > 0) {
        cout << "Середні витрати за такий день: " << fixed << setprecision(2) <<  sum / count << " грн" << endl;
    }
}

void limit_usage_days(double spending[], int days, double limit = 1000) {
    cout << "Ліміт: " << fixed << setprecision(2) <<  limit << " грн" << endl;
    int count = 0;

    for (int i = 0; i < days; i++) {
        if (spending[i] > limit) {
            cout << "  день " << i + 1 << ": " << fixed << setprecision(2) << spending[i] << " грн" << endl;
            count++;
        }
    }

    if (count == 0) {
        cout << "Днів з перевищенням немає" << endl;
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}

void remainder_budget(double current_budget, double used_budget) {
    if (current_budget > used_budget) {
        cout << "Залишок бюджету: " << fixed << setprecision(2) << current_budget - used_budget << " грн" << endl;
    } else if (used_budget > current_budget) {
        cout << "Перевитрата понад бюджет: " << fixed << setprecision(2) << abs(current_budget - used_budget) << " грн" << endl;
    }
}

double sum_spending(double array_1[], int days) {
    if (days == 0) return 0;
    return array_1[days - 1] + sum_spending(array_1, days - 1);
}

int main() {
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    cout << "Кількість днів обліку: ";
    cin >> N;
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < N; i++) {
        cin >> spending[i];
    }

    int choice = 7;
    do {
        menu_label:
        cout << "\n1. Показати витрати по днях" << endl;
        cout << "2. Статистика витрат" << endl;
        cout << "3. Дні з перевищенням денного ліміту" << endl;
        cout << "4. Три найдорожчі дні" << endl;
        cout << "0. Вийти" << endl;
        cout << "Ваш вибір: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nПомилка! Введіть число від 0 до 4\n";
            goto menu_label;
        }
        switch (choice) {
            case 1:
                cout << "День     Витрати, грн" << endl;
                for (int i = 0; i < N; i++) {
                    cout << "   " << i + 1 << "        " << fixed << setprecision(2) << spending[i] << endl;
                }
                break;
            case 2: {
                double min_val, max_val;
                get_min_max(spending, N, min_val, max_val);
                cout << "Мінімальні витрати за день: " << fixed << setprecision(2) << min_val << " грн" << endl;
                cout << "Максимальні витрати за день: " << fixed << setprecision(2) << max_val << " грн" << endl;
                cout << "Сумарні витрати: " << fixed << setprecision(2) << sum_spending(spending, N) << " грн" << endl;
                remainder_budget(budget, sum_spending(spending, N));
                avg_spending(spending, N);
                count_days(spending, N, budget);
                break;
            }
            case 3: {
                double user_limit;
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                cin >> user_limit;
                if (user_limit == 0) {
                    limit_usage_days(spending, N);
                } else {
                    limit_usage_days(spending, N, user_limit);
                }
                break;
            }
            case 4:
                top3(spending, N);
                break;
            case 0:
                return 0;
            default:
                cout << "\nНеіснуючий пункт меню!\n";
                goto menu_label;
        }
    } while (choice != 0);
}