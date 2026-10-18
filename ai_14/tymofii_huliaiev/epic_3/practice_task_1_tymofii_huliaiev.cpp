#include <iostream>
#include <cmath>    // fabs()
#include <iomanip>  // setw(), setprecision()

using namespace std;

// Вивід масиву
void showDailySpending(const double spending[], int n) {
    cout << "\nДень     Витрати, грн\n";
    cout << "---------------------\n";
    for (int i = 0; i < n; i++) {
        cout << setw(4) << (i + 1) << setw(15) << fixed << setprecision(2) << spending[i] << endl;
    }
}

// Рекурсивне сумування масиву без циклів
double calculateTotalRecursive(const double spending[], int n) {
    if (n <= 0) return 0.0;
    return spending[n - 1] + calculateTotalRecursive(spending, n - 1);
}

// Пошук min/max через посилання (&)
void findMinMax(const double spending[], int n, double &minVal, double &maxVal) {
    minVal = spending[0];
    maxVal = spending[0];
    for (int i = 1; i < n; i++) {
        if (spending[i] < minVal) minVal = spending[i];
        if (spending[i] > maxVal) maxVal = spending[i];
    }
}

// Розрахунок статистики
void showStatistics(const double spending[], int n, double budget) {
    double minVal, maxVal;
    findMinMax(spending, n, minVal, maxVal);

    double total = calculateTotalRecursive(spending, n);
    double remaining = budget - total;

    // Рахуємо середнє (пропускаємо дні з 0 грн)
    int shoppingDays = 0;
    double shoppingTotal = 0.0;
    for (int i = 0; i < n; i++) {
        if (spending[i] == 0) {
            continue; // Пропуск днів без витрат
        }
        shoppingDays++;
        shoppingTotal += spending[i];
    }
    double avgShopping = (shoppingDays > 0) ? (shoppingTotal / shoppingDays) : 0.0;

    // Шукаємо день вичерпання бюджету
    double accumulated = 0.0;
    int exhaustedDay = -1;
    double accumulatedAtExhaustion = 0.0;
    int dayIndex = 0;

    while (dayIndex < n) {
        accumulated += spending[dayIndex];
        if (accumulated > budget) {
            exhaustedDay = dayIndex + 1;
            accumulatedAtExhaustion = accumulated;
            break; // Перевищили бюджет — виходимо
        }
        dayIndex++;
    }

    cout << "\n--- СТАТИСТИКА ВИТРАТ ---\n";
    cout << fixed << setprecision(2);
    cout << "Мінімальні витрати за день:       " << setw(8) << minVal << " грн\n";
    cout << "Максимальні витрати за день:   " << setw(8) << maxVal << " грн\n";
    cout << "Сумарні витрати:               " << setw(8) << total << " грн\n";

    if (remaining < 0) {
        cout << "Перевитрата понад бюджет:      " << setw(8) << fabs(remaining) << " грн\n";
    } else {
        cout << "Залишок бюджету:               " << setw(8) << remaining << " грн\n";
    }

    cout << "Днів з покупками:                    " << shoppingDays << "\n";
    if (shoppingDays > 0) {
        cout << "Середні витрати за такий день: " << setw(8) << avgShopping << " грн\n";
    } else {
        cout << "Покупок не було взагалі.\n";
    }

    if (exhaustedDay != -1) {
        cout << "Бюджет вичерпано на дні " << exhaustedDay 
             << ", накопичено " << accumulatedAtExhaustion << " грн.\n";
    } else {
        cout << "Бюджету вистачило на всі " << n << " днів (залишок: " << remaining << " грн).\n";
    }
}

// Значення за замовчуванням limit = 1000.0
void showExceededLimit(const double spending[], int n, double limit = 1000.0) {
    cout << "\nЛіміт: " << fixed << setprecision(2) << limit << " грн\n";
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (spending[i] > limit) {
            cout << "  день " << (i + 1) << ": " << spending[i] << " грн\n";
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}

// Топ-3 найдорожчих днів
void showTop3Spending(const double spending[], int n) {
    // Копія масиву, щоб не міняти оригінал
    double temp[31];
    for (int i = 0; i < n; i++) {
        temp[i] = spending[i];
    }

    // Сортування бульбашкою за спаданням
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (temp[j] < temp[j + 1]) {
                double t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    int topCount = (n < 3) ? n : 3;
    cout << "\nТоп-" << topCount << " витрат: ";
    for (int i = 0; i < topCount; i++) {
        cout << fixed << setprecision(2) << temp[i] << (i < topCount - 1 ? ", " : " грн\n");
    }
}

int main() {
    double budget;
    cout << "Бюджет на місяць (грн): ";
    while (!(cin >> budget) || budget <= 0) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Помилка! Введіть додатне число: ";
    }

    int n;
    cout << "Кількість днів обліку: ";
    while (!(cin >> n) || n <= 0 || n > 31) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Помилка! Введіть кількість днів від 1 до 31: ";
    }

    double spending[31];
    cout << "Витрати по днях, введіть " << n << " чисел (грн): ";
    for (int i = 0; i < n; i++) {
        while (!(cin >> spending[i]) || spending[i] < 0) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Помилка! Введіть число за день " << (i + 1) << ": ";
        }
    }

    // Очищення буфера від залишків чисел у рядку
    while (cin.get() != '\n');

    int choice;
    do {
MENU: // Мітка для goto
        cout << "\n-------------------------------\n";
        cout << "1 - Показати витрати по днях\n";
        cout << "2 - Статистика витрат\n";
        cout << "3 - Дні з перевищенням денного ліміту\n";
        cout << "4 - Три найдорожчі дні\n";
        cout << "0 - Вийти\n";
        cout << "Виберіть пункт: ";

        if (!(cin >> choice)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "\nПомилка вводу! Повернення в меню...\n";
            goto MENU;
        }

        switch (choice) {
            case 1:
                showDailySpending(spending, n);
                break;
            case 2:
                showStatistics(spending, n, budget);
                break;
            case 3: {
                double inputLimit;
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                while (!(cin >> inputLimit) || inputLimit < 0) {
                    cin.clear();
                    while (cin.get() != '\n');
                    cout << "Помилка! Введіть число >= 0: ";
                }

                if (inputLimit == 0) {
                    showExceededLimit(spending, n);
                } else {
                    showExceededLimit(spending, n, inputLimit);
                }
                break;
            }
            case 4:
                showTop3Spending(spending, n);
                break;
            case 0:
                cout << "Завершення роботи.\n";
                break;
            default:
                cout << "\nНевідомий пункт! Повернення в меню...\n";
                goto MENU;
        }
    } while (choice != 0);

    return 0;
}