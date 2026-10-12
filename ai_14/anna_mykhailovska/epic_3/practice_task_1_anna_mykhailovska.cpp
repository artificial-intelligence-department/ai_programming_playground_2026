/*
    Задача: Аналізатор місячного бюджету
    Михайловська Анна
    ШІ-14
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int MAX_DAYS = 31; // Максимальна кількість днів у місяці

// Пункт 1: показує витрати в початковому порядку днів.
void point1(double spending[], int n) {
    cout << "День     Витрати, грн\n";
    cout << fixed << setprecision(2);

    for (int i = 0; i < n; i++) {
        cout << setw(4) << (i + 1) << setw(17) << spending[i] << '\n';
    }
}

// Функція для знаходження мінімальних та максимальних витрат
void findMinMax(double spending[], int n,
                double& minSpending, double& maxSpending) {
    minSpending = spending[0];
    maxSpending = spending[0];

    for (int i = 1; i < n; i++) {
        if (spending[i] < minSpending) {
            minSpending = spending[i];
        }
        if (spending[i] > maxSpending) {
            maxSpending = spending[i];
        }
    }
}

// Функція для знаходження суми витрат через рекурсію
double sum(double spending[], int n) {
    if (n == 0) {
        return 0;
    }
    return spending[n - 1] + sum(spending, n - 1);
}

// Пункт 2: статистика витрат і перевірка місячного бюджету.
void point2(double spending[], int n, double budget) {
    double minSpending = 0;
    double maxSpending = 0;

    findMinMax(spending, n, minSpending, maxSpending);
    double totalSpending = sum(spending, n);
    double remaining = budget - totalSpending;

    cout << fixed << setprecision(2);
    cout << "Мінімальні витрати за день: " << minSpending << " грн\n";
    cout << "Максимальні витрати за день: " << maxSpending << " грн\n";
    cout << "Сумарні витрати: " << totalSpending << " грн\n";

    // Перевірка залишку бюджету та виведення перевитрати
    if (remaining < 0) {
        cout << "Перевитрата понад бюджет: " << fabs(remaining) << " грн\n";
    } else {
        cout << "Залишок бюджету: " << remaining << " грн\n";
    }

    // Підрахунок днів з покупками
    int daysWithPurchases = 0;
    for (int i = 0; i < n; i++) {
        if (spending[i] == 0) {
            continue;
        }
        daysWithPurchases++;
    }
    cout << "Днів з покупками: " << daysWithPurchases << '\n';

    // Обчислення середніх витрат за дні з покупками
    if (daysWithPurchases > 0) {
        double average = totalSpending / daysWithPurchases;
        cout << "Середні витрати за такий день: " << average << " грн\n";
    } else {
        cout << "Середні витрати не обчислюються: немає днів з покупками.\n";
    }

    // Пошук дня перевищення бюджету
    double accumulated = 0;
    int dayIndex = 0;
    while (dayIndex < n) {
        accumulated += spending[dayIndex];

        if (accumulated > budget) {
            cout << "Бюджет вичерпано на дні " << (dayIndex + 1) << ", накопичено " << accumulated << " грн.\n";
            break;
        }
        dayIndex++;
    }

    // Виведення залишку, якщо бюджету вистачило на всі дні
    if (dayIndex == n) {
        cout << "Бюджету вистачило на всі дні. Залишок: "
             << (budget - accumulated) << " грн\n";
    }
}

// Пункт 3: дні з перевищенням денного ліміту.
void point3(double spending[], int n, double limit = 1000) {
    int count = 0;

    cout << fixed << setprecision(2);
    cout << "Ліміт: " << limit << " грн\n";

    for (int i = 0; i < n; i++) {
        if (spending[i] > limit) {
            cout << "День " << (i + 1) << ": " << spending[i] << " грн\n";
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << '\n';
}

// Пункт 4: три найбільші суми витрат.
void point4(double spending[], int n) {
    double spendingCopy[MAX_DAYS];

    for (int i = 0; i < n; i++) {
        spendingCopy[i] = spending[i];
    }

    // Сортування копії масиву за спаданням
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (spendingCopy[i] < spendingCopy[j]) {
                
                double temp = spendingCopy[i];
                spendingCopy[i] = spendingCopy[j];
                spendingCopy[j] = temp;
            }
        }
    }

    // Виведення до трьох найбільших сум
    cout << fixed << setprecision(2);
    cout << "Топ-3 витрат: ";

    for (int i = 0; i < 3 && i < n; i++) {
        if (i > 0) {
            cout << ", ";
        }
        cout << spendingCopy[i];
    }
    cout << " грн\n";
}

int main() {
    double budget = 0;
    int n = 0;
    double spending[MAX_DAYS];

    // Введення та перевірка бюджету
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    while (budget < 0) {
        cout << "Помилка: бюджет не може бути від'ємним числом.\n" << "Введіть значення ще раз: ";
        cin >> budget;
    }

    // Введення та перевірка кількості днів
    cout << "Кількість днів обліку: ";
    cin >> n;
    while (n < 1 || n > MAX_DAYS) {
        cout << "Помилка: кількість днів має бути від 1 до " << MAX_DAYS << ".\nВведіть значення ще раз: ";
        cin >> n;
    }

    // Введення та перевірка витрат по днях
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < n; i++) {
        cin >> spending[i];
        while (spending[i] < 0) {
            cout << "Помилка: витрати не можуть бути від'ємними.\n" << "Введіть значення ще раз: ";
            cin >> spending[i];
        }
    }

    // Робота меню 
    int choice = 0;
    do {
    menu:
        cout << "\nПункт    Операція\n";
        cout << "  1      Показати витрати по днях\n";
        cout << "  2      Статистика витрат\n";
        cout << "  3      Дні з перевищенням денного ліміту\n";
        cout << "  4      Три найдорожчі дні\n";
        cout << "  0      Вийти\n";
        cout << "Ваш вибір: ";

        cin >> choice;

        // Перевірка номера пункту меню
        if (choice < 0 || choice > 4) {
            cout << "Помилка: оберіть пункт від 0 до 4.\n";
            goto menu;
        }

        if (choice == 1) {
            point1(spending, n);
        }

        if (choice == 2) {
            point2(spending, n, budget);
        }

        if (choice == 3) {
            // Введення та перевірка денного ліміту
            double dailyLimit = 0;

            cout << "Денний ліміт (грн, 0 = 1000 грн): ";
            cin >> dailyLimit;
            while (dailyLimit < 0) {
                cout << "Ліміт не може бути від'ємним. Введіть ще раз: ";
                cin >> dailyLimit;
            }

            if (dailyLimit == 0) {
                point3(spending, n);
            } else {
                point3(spending, n, dailyLimit);
            }
        }

        if (choice == 4) {
            point4(spending, n);
        }
    } while (choice != 0);

    return 0;
}
