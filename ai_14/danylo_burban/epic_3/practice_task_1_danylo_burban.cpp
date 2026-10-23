
/* Epic 3 - Аналізатор місячного бюджету
   Бурбан Данило
   ШІ - 14
*/

#include <iostream>
#include <cmath>
#include <limits>
#include <utility>
#include <iomanip>
using namespace std;

void showSpendings(int spendings[], int length_of_array);
void minMax(int spendings[], int length_of_array, int &min, int &max);
void calculateSum(int spendings[], int N, int iter, int &sum);
void spendingDifference(int budget, int sum);
void spendingStats(int spendings[], int N);
void fullySpended(int spendings[], int N, int budget);
void limitBreaks(int spendings[], int N, int limit = 1000);
void threeDays(int spendings[], int N);

int main() {
    int iter = 0;
    int budget;
    int sum = 0;
    int N;
    int choice;
    int min_val;
    int max_val;
    int limit = 0;
    int spending[31];

basic_inputs:
    cout << "Введіть бюджет: ";
    if (!(cin >> budget) || budget < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Некоректне значення бюджету!" << endl;
        goto basic_inputs;
    }

    cout << "Введіть кількість днів (1-31): ";
    if (!(cin >> N) || N <= 0 || N > 31) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Некоректне значення N (має бути від 1 до 31)!" << endl;
        goto basic_inputs;
    }

    cout << "Введіть витрати за " << N << " днів: ";
    for (int i = 0; i < N; i++) {
        if (!(cin >> spending[i]) || spending[i] < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Помилка вводу елемента масиву!" << endl;
            goto basic_inputs;
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
menu_inputs:
        cout << "\n1 Показати витрати по днях" << endl;
        cout << "2 Статистика витрат" << endl;
        cout << "3 Дні з перевищенням денного ліміту" << endl;
        cout << "4 Три найдорожчі дні" << endl;
        cout << "0 Вийти" << endl;
        cout << "Виберіть пункт меню: ";

        if (!(cin >> choice) || choice < 0 || choice > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некоректний ввід пункту меню, спробуйте ще раз"
                 << endl;
            goto menu_inputs;
        }

        switch (choice) {
        case 1:
            showSpendings(spending, N);
            break;

        case 2:
            minMax(spending, N, min_val, max_val);

            sum = 0;
            calculateSum(spending, N, iter, sum);

            cout << "Мінімальні витрати за день:\t"
                 << min_val << endl;
            cout << "Максимальні витрати за день:\t"
                 << max_val << endl;
            cout << "Сумарні витрати:\t\t"
                 << sum << endl;

            spendingDifference(budget, sum);
            spendingStats(spending, N);
            fullySpended(spending, N, budget);
            break;

        case 3:
        case_3_input:
            cout << "Введіть денний ліміт (0 = 1000 грн): ";
            if (!(cin >> limit) || limit < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Некоректне значення денного ліміту!"
                     << endl;
                goto case_3_input;
            }

            limitBreaks(spending, N, limit);
            break;

        case 4:
            threeDays(spending, N);
            break;

        default:
            break;
        }

    } while (choice != 0);

    return 0;
}

void showSpendings(int spendings[], int length_of_array) {
    cout << fixed << setprecision(2);
    cout << "День\t\tВитрати (грн)" << endl;

    for (int i = 0; i < length_of_array; i++) {
        cout << i + 1 << "\t\t" << spendings[i] << endl;
    }
}

void minMax(int spendings[], int length_of_array,
            int &min, int &max) {
    max = spendings[0];
    min = spendings[0];

    for (int i = 0; i < length_of_array; i++) {
        if (max < spendings[i]) {
            max = spendings[i];
        }

        if (min > spendings[i]) {
            min = spendings[i];
        }
    }
}

void calculateSum(int spendings[], int N, int iter, int &sum) {
    if (iter >= N) {
        return;
    }

    sum += spendings[iter];

    calculateSum(spendings, N, iter + 1, sum);
}

void spendingDifference(int budget, int sum) {
    if (budget >= sum) {
        cout << "Залишок бюджету:\t\t"
             << budget - sum << endl;
    } else {
        cout << "Перевитрата понад бюджет:\t"
             << abs(budget - sum) << endl;
    }
}

void spendingStats(int spendings[], int N) {
    int number_of_spends = 0;
    int sum = 0;

    for (int i = 0; i < N; i++) {
        if (spendings[i] == 0) {
            continue;
        }

        number_of_spends++;
        sum += spendings[i];
    }

    cout << "Днів з покупками:\t\t"
         << number_of_spends << endl;

    if (number_of_spends == 0) {
        cout << "Середні витрати за такий день: немає даних"
             << endl;
        return;
    }

    cout << "Середні витрати за такий день:\t"
         << static_cast<double>(sum) / number_of_spends
         << endl;
}

void fullySpended(int spendings[], int N, int budget) {
    int sum = 0;
    int day = 0;

    while (day < N) {
        sum += spendings[day];
        day++;

        if (sum > budget) {
            cout << "Бюджет вичерпано на дні\t"
                 << day << endl;
            cout << "Накопичено:\t" << sum << endl;
            break;
        }
    }

    if (sum <= budget) {
        cout << "Бюджет не вичерпано" << endl;
        cout << "Залишок:\t\t"
             << budget - sum << endl;
    }
}

void limitBreaks(int spendings[], int N, int limit) {
    if (limit == 0) {
        limit = 1000;
    }

    int day_sum = 0;

    cout << "Ваш ліміт складає: "
         << limit << " грн" << endl;

    for (int i = 0; i < N; i++) {
        if (spendings[i] > limit) {
            day_sum++;
            cout << "День " << i + 1 << ": "
                 << spendings[i] << " грн" << endl;
        }
    }

    cout << "Разом днів з перевищенням: "
         << day_sum << endl;
}

void threeDays(int spendings[], int N) {
    bool swapped;
    int* alt_spendings = new int[N];

    for (int i = 0; i < N; i++) {
        alt_spendings[i] = spendings[i];
    }

    for (int i = 0; i < N - 1; i++) {
        swapped = false;

        for (int j = 0; j < N - i - 1; j++) {
            if (alt_spendings[j] > alt_spendings[j + 1]) {
                swap(alt_spendings[j], alt_spendings[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }

    cout << "Топ-3 витрат: ";

    for (int i = 0; i < N && i < 3; i++) {
        cout << alt_spendings[N - i - 1];

        if (i < N - 1 && i < 2) {
            cout << ", ";
        }
    }

    cout << " грн" << endl;

    delete[] alt_spendings;
}
