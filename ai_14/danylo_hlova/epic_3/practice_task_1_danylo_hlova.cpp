#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
// Виведення таблиці витрат по днях
void table(double spend[], int n) {
    cout << "\nДень     Витрати, грн" << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(4) << (i + 1) 
             << setw(15) << fixed << setprecision(2) << spend[i] << endl;
    }
}
// Пошук найменшої та найбільшої витрати за місяць
void findMinMax(double spend[], int n, double &minVal, double &maxVal) {
    minVal = spend[0];
    maxVal = spend[0];
    for (int i = 1; i < n; i++) {
        if (spend[i] < minVal) {
            minVal = spend[i];
        }
        if (spend[i] > maxVal) {
            maxVal = spend[i];
        }
    }
}
// Обчислення загальної суми всіх витрат
double sumRecursive(double spend[], int n) {
    if (n == 0) {
        return 0;
    }
    return spend[n - 1] + sumRecursive(spend, n - 1);
}
// порівняння з бюджетом, середні витрати,день вичерпання коштів
void statistics(double spend[], int n, double budget) {
    double minVal, maxVal;
    findMinMax(spend, n, minVal, maxVal);

    double total = sumRecursive(spend, n);
// Рахує суму та кількість днів, у які дійсно були покупки
    double sumWithPurchases = 0;
    int daysWithPurchases = 0;

    for (int i = 0; i < n; i++) {
        if (spend[i] == 0) {
            continue;               // пропускаю дні без покупок
        }
        sumWithPurchases += spend[i];
        daysWithPurchases++;
    }

    double average = 0;
    if (daysWithPurchases > 0) {
        average = sumWithPurchases / daysWithPurchases;
    }
// Вивід результатів
    cout << fixed << setprecision(2);
    cout << "\nМінімальні витрати за день:       " << minVal << " грн" << endl;
    cout << "Максимальні витрати за день:   " << maxVal << " грн" << endl;
    cout << "Сумарні витрати:               " << total << " грн" << endl;

    if (total > budget) {
        cout << "Перевитрата понад бюджет:      " << fabs(budget - total) << " грн" << endl;
    } else {
        cout << "Залишок бюджету:               " << (budget - total) << " грн" << endl;
    }

    cout << "Днів з покупками:                    " << daysWithPurchases << endl;
    cout << "Середні витрати за такий день: " << average << " грн" << endl;
// Шукає день на якому бюджет закінчився
    double accumulated = 0;
    int day = 0;
    bool exhausted = false;

    while (day < n) {
        accumulated += spend[day];
        day++;

        if (accumulated > budget) {
            exhausted = true;
            break;                  // зупиняє коли перевищили
        }
    }

    if (exhausted) {
        cout << "Бюджет вичерпано на дні " << day 
             << ", накопичено " << accumulated << " грн." << endl;
    } else {
        cout << "Бюджету вистачило на всі дні. Залишок: " 
             << (budget - accumulated) << " грн." << endl;
    }
}
// Пошук днів, коли витрати перевищили заданий ліміт (по стандарту 1000 грн)
void daysOverLimit(double spend[], int n, double limit = 1000.0) {
    cout << "Ліміт: " << fixed << setprecision(2) << limit << " грн" << endl;
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (spend[i] > limit) {
            cout << "  день " << (i + 1) << ": " << spend[i] << " грн" << endl;
            count++;
        }
    }
    
    cout << "Разом днів з перевищенням: " << count << endl;
}
// Знаходження трьох днів з найбільшими витратами
void top3Days(double spend[], int n) {
    double copy[31];
// Копіює масив, щоб не змінити оригінальні дані
    for (int i = 0; i < n; i++) {
        copy[i] = spend[i];
    }
    
    // сорутвання(бульбашкою)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (copy[j] < copy[j + 1]) {
                double temp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp;
            }
        }
    }
    // Виводить до 3 найбільших сум
    cout << "\nТоп-3 витрат: ";
    int maxItems = (n < 3) ? n : 3;
    for (int i = 0; i < maxItems; i++) {
        cout << fixed << setprecision(2) << copy[i];
        if (i < maxItems - 1) {
            cout << ", ";
        }
    }
    cout << " грн" << endl;
}

int main() {
    // Введення та перевірка вхідних даних (бюджет, кількість днів та витрати)
    double budget;
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;

    if (cin.fail() || budget < 0) {
        cout << "Помилка вводу бюджету!" << endl;
        return 1;
    }

    int n;
    cout << "Кількість днів обліку: ";
    cin >> n;

    if (cin.fail() || n < 1 || n > 31) {
        cout << "Помилка: кількість днів має бути від 1 до 31!" << endl;
        return 1;
    }

    double spend[31];
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < n; i++) {
        cin >> spend[i];
        if (cin.fail() || spend[i] < 0) {
            cout << "Помилка: витрати мають бути числом >= 0!" << endl;
            return 1;
        }
    }

    int choice;
// Головне меню програми
choices:
    do {
        cout << "\n---- МЕНЮ ----" << endl;
        cout << "1 - Показати витрати по днях" << endl;
        cout << "2 - Статистика витрат" << endl;
        cout << "3 - Дні з перевищенням денного ліміту" << endl;
        cout << "4 - Три найдорожчі дні" << endl;
        cout << "0 - Вихід" << endl;
        cout << "Введіть свій пункт: ";

        cin >> choice;
// Захист від введення літер або некоректних символів
        if (cin.fail()) {
            cout << "Помилка вводу! Спробуйте ще раз." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto choices;
        }
// Обробка вибору користувача
        switch (choice) {
            case 1:
                table(spend, n);
                break;
            case 2:
                statistics(spend, n, budget);
                break;
            case 3: {
                double limit;
                cout << "\nДенний ліміт (грн, 0 = за замовчуванням): ";
                cin >> limit;
                
                if (cin.fail() || limit < 0) {
                    cout << "Помилка вводу! Спробуйте ще раз." << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    goto choices;
                }
                
                if (limit == 0) {
                    daysOverLimit(spend, n); // Використовує значення за замовчуванням (1000.0)
                } else {
                    daysOverLimit(spend, n, limit);
                }
                break;
            }
            case 4:
                top3Days(spend, n);
                break;
            case 0:
                cout << "Вихід з програми." << endl;
                break;
            default:
                cout << "Невірний пункт меню!" << endl;
                goto choices;
        }

    } while (choice != 0);

    return 0;
}