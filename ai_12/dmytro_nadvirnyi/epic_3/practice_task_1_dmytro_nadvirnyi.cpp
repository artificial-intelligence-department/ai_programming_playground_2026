/*
    Аналізатор місячного бюджету
    Автор: Дмитро Надвірний
    Група: 12
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void showSpending(const double arr[], int n) {
    cout << "\nВитрати по днях:\n";
    for (int i = 0; i < n; i++) {
        cout << "День " << i + 1 << ": "
             << fixed << setprecision(2) << arr[i] << " грн\n";
    }
}

void getMinMax(const double arr[], int n, double &minVal, double &maxVal) {
    minVal = maxVal = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
}

double averageSpending(const double arr[], int n) {
    double total = 0;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) continue;
        total += arr[i];
        count++;
    }

    return (count > 0) ? total / count : 0.0;
}

double getTotalSumRecursive(const double arr[], int n) {
    if (n <= 0) return 0;
    return arr[n - 1] + getTotalSumRecursive(arr, n - 1);
}

void showStatistics(const double arr[], int n, double budget) {
    double minVal, maxVal;
    getMinMax(arr, n, minVal, maxVal);

    double average = averageSpending(arr, n);
    double totalSum = getTotalSumRecursive(arr, n);
    double remainingBudget = budget - totalSum;

    int daysWithPurchase = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) daysWithPurchase++;
    }

    cout << "\nСтатистика витрат:\n";
    cout << "Мінімальна витрата: " << fixed << setprecision(2) << minVal << " грн\n";
    cout << "Максимальна витрата: " << maxVal << " грн\n";
    cout << "Загальна сума витрат: " << totalSum << " грн\n";

    if (remainingBudget < 0)
        cout << "Перевитрата понад бюджет: " << abs(remainingBudget) << " грн\n";
    else
        cout << "Залишок бюджету: " << remainingBudget << " грн\n";

    cout << "Днів із покупками: " << daysWithPurchase << "\n";
    cout << "Середня витрата без урахування днів без покупок: "
         << average << " грн\n";

    double accumulated = 0;
    int dayExhausted = -1;
    double accumulatedAtExhausted = 0;
    int i = 0;

    while (i < n) {
        accumulated += arr[i];

        if (accumulated > budget) {
            dayExhausted = i + 1;
            accumulatedAtExhausted = accumulated;
            break;
        }
        i++;
    }

    if (dayExhausted != -1) {
        cout << "Бюджет перевищено на " << dayExhausted
             << "-й день, накопичені витрати: "
             << accumulatedAtExhausted << " грн.\n";
    } else {
        cout << "Бюджету вистачило на всі дні.\n";
    }
}

void checkLimitExceeded(const double arr[], int n, double limit = 1000.0) {
    cout << "Денний ліміт: " << fixed << setprecision(2) << limit << " грн\n";

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > limit) {
            cout << "День " << i + 1 << ": " << arr[i] << " грн\n";
            count++;
        }
    }

    cout << "Кількість днів із перевищенням: " << count << "\n";
}

void showTopThreeDays(const double arr[], int n) {
    double temp[31];

    for (int i = 0; i < n; i++) {
        temp[i] = arr[i];
    }

    // Сортування копії масиву за спаданням (бульбашкою)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (temp[j] < temp[j + 1]) {
                double t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    int count = (n < 3) ? n : 3;
    cout << "\nТоп-" << count << " найбільших витрат: ";

    for (int i = 0; i < count; i++) {
        cout << fixed << setprecision(2) << temp[i];
        if (i < count - 1) cout << ", ";
        else cout << " грн\n";
    }
}

int main() {
    double budget;
    int N;
    double spending[31];

    cout << "Введіть бюджет: ";
    while (!(cin >> budget) || budget < 0) {
        cout << "Помилка! Введіть невід'ємне число: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Введіть кількість днів: ";
    while (!(cin >> N) || N <= 0 || N > 31) {
        cout << "Помилка! Кількість днів має бути від 1 до 31: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    for (int i = 0; i < N; i++) {
        cout << "Введіть витрати за день " << i + 1 << ": ";
        while (!(cin >> spending[i]) || spending[i] < 0) {
            cout << "Помилка! Введіть невід'ємне число: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int choice;

    do {
    menu_start:
        cout << "\n--- МЕНЮ ---\n";
        cout << "1. Показати витрати по днях\n";
        cout << "2. Показати статистику витрат\n";
        cout << "3. Показати дні з перевищенням денного ліміту\n";
        cout << "4. Показати три найбільші витрати\n";
        cout << "0. Вийти\n";
        cout << "Виберіть пункт: ";

        if (!(cin >> choice) || choice < 0 || choice > 4) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка! Виберіть число від 0 до 4.\n";
            goto menu_start;
        }

        switch (choice) {
            case 1:
                showSpending(spending, N);
                break;

            case 2:
                showStatistics(spending, N, budget);
                break;

            case 3: {
                double limit;
                cout << "Введіть денний ліміт (0 — стандартний, 1000 грн): ";

                while (!(cin >> limit) || limit < 0) {
                    cout << "Помилка! Введіть невід'ємне число: ";
                    cin.clear();
                    cin.ignore(10000, '\n');
                }

                if (limit == 0)
                    checkLimitExceeded(spending, N);
                else
                    checkLimitExceeded(spending, N, limit);

                break;
            }

            case 4:
                showTopThreeDays(spending, N);
                break;

            case 0:
                cout << "\nЗавершення роботи. До побачення!\n";
                break;
        }

    } while (choice != 0);

    return 0;
}