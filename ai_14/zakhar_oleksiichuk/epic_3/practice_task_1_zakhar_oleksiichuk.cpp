/*
Task name: Аналізатор місячного бюджету
Name: Захар Олексійчук
Group: ШІ-14 (ai_14)
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void MinMaxValues(const float arr[], int size, float &min_val, float &max_val) {
    min_val = arr[0];
    max_val = arr[0];

    for (int i = 1; i < size; ++i) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }
}

float TotalSpendings(const float arr[], int size) {
    if (size <= 0) return 0;
    return arr[size - 1] + TotalSpendings(arr, size - 1);
}

int CountShoppingDays(const float arr[], int size) {
    int shoppingDays = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) continue;
        shoppingDays++;
    }
    return shoppingDays;
}

float AverageForShoppingDays(const float arr[], int size, int shoppingDays) {
    if (shoppingDays == 0) return 0.0f;
    float shoppingDaysSum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) continue;
        shoppingDaysSum += arr[i];
    }
    return shoppingDaysSum / shoppingDays;
}

int ExceededBudgetDay(const float arr[], int size, float budget, float &spentTillEmpty) {
    float sum = 0;
    int ind = 0;
    
    while (ind < size) {
        sum += arr[ind];
        if (sum > budget) {
            spentTillEmpty = sum;
            return ind + 1;
        }
        ind++;
    }
    
    spentTillEmpty = sum;
    return 0; 
}


// Пункт 1: Показати витрати по днях
void PrintDailySpendings(const float arr[], int size) {
    cout << "\nДень     Витрати, грн\n";
    for (int i = 0; i < size; i++) {
        cout << setw(4) << i + 1 << setw(17) << fixed << setprecision(2) << arr[i] << "\n";
    }
}

// Пункт 2: Статистика витрат
void PrintStatistics(const float arr[], int size, float budget) {
    float minValue = 0.0f, maxValue = 0.0f;
    MinMaxValues(arr, size, minValue, maxValue);

    float totalSpendings = TotalSpendings(arr, size);
    
    float costOverrun = 0.0f;
    if (totalSpendings > budget) {
        costOverrun = fabs(totalSpendings - budget);
    }

    int shoppingDays = CountShoppingDays(arr, size);
    float avgForShoppingDays = AverageForShoppingDays(arr, size, shoppingDays);

    float spentTillEmpty = 0.0f;
    int exceededBudget = ExceededBudgetDay(arr, size, budget, spentTillEmpty);

    cout << "\nМінімальні витрати за день:       " << setw(8) << fixed << setprecision(2) << minValue << " грн\n";
    cout << "Максимальні витрати за день:   " << setw(8) << maxValue << " грн\n";
    cout << "Сумарні витрати:               " << setw(8) << totalSpendings << " грн\n";
    cout << "Перевитрата понад бюджет:      " << setw(8) << costOverrun << " грн\n";
    cout << "Днів з покупками:                    " << shoppingDays << "\n";
    cout << "Середні витрати за такий день: " << setw(8) << avgForShoppingDays << " грн\n";

    if (exceededBudget > 0) {
        cout << "Бюджет вичерпано на дні " << exceededBudget << ", накопичено " << fixed << setprecision(2) << spentTillEmpty << " грн.\n";
    } else {
        cout << "Бюджету вистачило на всі дні. Залишок: " << fixed << setprecision(2) << (budget - totalSpendings) << " грн.\n";
    }
}

// Пункт 3: Дні з перевищенням ліміту
int PrintExceededLimitDays(const float arr[], int size, float limit = 1000.0f) {
    int count = 0;
    cout << "\nЛіміт: " << fixed << setprecision(2) << limit << " грн\n";

    for (int i = 0; i < size; i++) {
        if (arr[i] > limit) {
            cout << "  день " << i + 1 << ": " << fixed << setprecision(2) << arr[i] << " грн\n";
            count++;
        }
    }

    cout << "Разом днів з перевищенням: " << count << "\n";
    return count;
}

// Пункт 4: Три найдорожчі дні (вкладені цикли + сортування копії)
void SpendingsBubbleSort(const float arr[], int size) {
    float temp[31];
    for (int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (temp[j] < temp[j + 1]) {
                float swapTemp = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swapTemp;
            }
        }
    }

    int count = (size < 3) ? size : 3;

    cout << "\nТоп-3 витрат: ";
    for (int i = 0; i < count; i++) {
        cout << fixed << setprecision(2) << temp[i];
        if (i < count - 1) {
            cout << ", ";
        }
    }
    cout << " грн\n";
}

int main() {
    // Ініціалізація
    float budget;
    int days;

    // Ввід та валідація
    cout << "Бюджет на місяць (грн): ";
    if (!(cin >> budget) || budget < 0) {
        cout << "Помилка введення бюджету\n";
        return 0;
    }

    cout << "Кількість днів обліку: ";
    if (!(cin >> days) || days <= 0 || days > 31) {
        cout << "Помилка введення кількості днів\n";
        return 0;
    }

    float spendings[31];

    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < days; i++) {
        if (!(cin >> spendings[i]) || spendings[i] < 0) {
            cout << "Помилка введення витрат\n";
            return 0;
        }
    }

    int choice;


SHOW_MENU:
    do {
        cout << "\n--- МЕНЮ ---\n";
        cout << "1. Показати витрати по днях\n";
        cout << "2. Статистика витрат\n";
        cout << "3. Дні з перевищенням денного ліміту\n";
        cout << "4. Три найдорожчі дні\n";
        cout << "0. Вийти\n";
        cout << "Оберіть пункт: ";

        if (!(cin >> choice)) {
            cout << "Помилка введення.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            goto SHOW_MENU; 
        }

        switch (choice) {
            case 1:
                PrintDailySpendings(spendings, days);
                break;
            case 2:
                PrintStatistics(spendings, days, budget);
                break;
            case 3: {
                float userLimit;
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                if (!(cin >> userLimit) || userLimit < 0) {
                    cout << "Некоректний ліміт!\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                } else if (userLimit == 0) {
                    PrintExceededLimitDays(spendings, days); 
                } else {
                    PrintExceededLimitDays(spendings, days, userLimit);
                }
                break;
            }
            case 4:
                SpendingsBubbleSort(spendings, days);
                break;
            case 0:
                cout << "Завершення роботи програми.\n";
                break;
            default:
                cout << "Невірний пункт меню! Спробуйте ще раз.\n";
                goto SHOW_MENU; 
        }
    } while (choice != 0); 

    return 0;
}