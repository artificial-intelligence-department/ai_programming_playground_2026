/*
Задача:  Аналізатор місячного бюджету
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Оголошення функцій
void showSpending(double spending[], int days);
void findMinMax(double spending[], int days, double &minimum, double &maximum);
double sumSpending(double spending[], int days);
void showStatistics(double spending[], int days, double budget);
void showLimitDays(double spending[], int days, double limit = 1000);
void showTopThree(double spending[], int days);

int main() {
    double budget;
    int days;
    double spending[31];

    // Формат виводу сум
    cout << fixed << setprecision(2);

    // Введення бюджету
    cout << "Введіть бюджет на місяць: ";
    cin >> budget;

    if (cin.fail() || budget < 0) {
        cout << "Помилка: введіть невід'ємне число." << endl;
        return 1;
    }

    // Введення кількості днів
    cout << "Введіть кількість днів (від 1 до 31): ";
    cin >> days;

    if (cin.fail() || days < 1 || days > 31) {
        cout << "Помилка: введіть ціле число від 1 до 31." << endl;
        return 1;
    }

    // Введення витрат по днях
    cout << "Витрати по днях (грн): ";

    for (int i = 0; i < days; i++) {
        cin >> spending[i];

        if (cin.fail() || spending[i] < 0) {
            cout << "Помилка: введіть невід'ємне число." << endl;
            return 1;
        }
    }

    int choice;

    // Меню програми
    do {
    menu:
        cout << endl;
        cout << "Оберіть пункт:" << endl;
        cout << "1. Показати витрати по днях" << endl;
        cout << "2. Статистика витрат" << endl;
        cout << "3. Дні з перевищенням денного ліміту" << endl;
        cout << "4. Три найдорожчі дні" << endl;
        cout << "0. Вийти" << endl;
        cout << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        if (cin.fail() || choice < 0 || choice > 4) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка: виберіть пункт від 0 до 4." << endl;
            goto menu;
        }

        cout << endl;

        // Виконання обраного пункту
        switch (choice) {
            case 1:
                showSpending(spending, days);
                break;

            case 2:
                showStatistics(spending, days, budget);
                break;

            case 3:
                // Введення денного ліміту
                double limit;

                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                cin >> limit;

                if (cin.fail() || limit < 0) {
                    cout << "Помилка: введіть невід'ємне число." << endl;
                    return 1;
                }

                if (limit == 0) {
                    showLimitDays(spending, days);
                }
                else {
                    showLimitDays(spending, days, limit);
                }

                break;

            case 4:
                showTopThree(spending, days);
                break;

            case 0:
                break;
        }
    } while (choice != 0);

    return 0;
}

// Вивід витрат по днях
void showSpending(double spending[], int days) {
    cout << "День     Витрати, грн" << endl;

    for (int i = 0; i < days; i++) {
        cout << setw(4) << i + 1 << setw(16) << spending[i] << endl;
    }
}

// Пошук мінімальних і максимальних витрат
void findMinMax(double spending[], int days, double &minimum, double &maximum) {
    minimum = spending[0];
    maximum = spending[0];

    for (int i = 1; i < days; i++) {
        if (spending[i] < minimum) {
            minimum = spending[i];
        }

        if (spending[i] > maximum) {
            maximum = spending[i];
        }
    }
}

// Обчислення сумарних витрат
double sumSpending(double spending[], int days) {
    if (days == 0) {
        return 0;
    }

    return spending[days - 1] + sumSpending(spending, days - 1);
}

// Вивід статистики витрат
void showStatistics(double spending[], int days, double budget) {
    double minimum;
    double maximum;

    findMinMax(spending, days, minimum, maximum);

    cout << "Мінімальні витрати за день:  " << setw(10) << minimum << " грн" << endl;
    cout << "Максимальні витрати за день: " << setw(10) << maximum << " грн" << endl;

    double total = sumSpending(spending, days);
    cout << "Сумарні витрати:             " << setw(10) << total << " грн" << endl;

    // Визначення залишку або перевитрати бюджету
    double remaining = budget - total;

    if (remaining >= 0) {
        cout << "Залишок бюджету:             " << setw(10) << remaining << " грн" << endl;
    }
    else {
        cout << "Перевитрата понад бюджет:    " << setw(10) << abs(remaining) << " грн" << endl;
    }

    // Підрахунок днів з покупками
    int shoppingDays = 0;

    for (int i = 0; i < days; i++) {
        if (spending[i] == 0) {
            continue;
        }

        shoppingDays++;
    }

    cout << "Днів з покупками:            " << setw(10) << shoppingDays << endl;

    // Обчислення середніх витрат за день з покупками
    if (shoppingDays > 0) {
        double average = total / shoppingDays;
        cout << "Середні витрати за такий день: " << setw(8) << average << " грн" << endl;
    }
    else {
        cout << "Днів з покупками немає." << endl;
    }

    // Визначення дня вичерпання бюджету
    double accumulated = 0;
    int day = 0;

    while (day < days) {
        accumulated += spending[day];

        if (accumulated > budget) {
            cout << "Бюджет вичерпано на дні " << day + 1
                 << ", накопичено " << accumulated << " грн." << endl;
            break;
        }

        day++;
    }

    if (accumulated <= budget) {
        cout << "Бюджету вистачило на всі дні. Залишок: "
             << budget - accumulated << " грн." << endl;
    }
}

// Вивід днів з перевищенням денного ліміту
void showLimitDays(double spending[], int days, double limit) {
    int count = 0;

    cout << "Ліміт: " << limit << " грн" << endl;

    for (int i = 0; i < days; i++) {
        if (spending[i] > limit) {
            cout << "  день " << i + 1 << ": " << spending[i] << " грн" << endl;
            count++;
        }
    }

    cout << "Разом днів з перевищенням: " << count << endl;
}

// Вивід найбільших витрат
void showTopThree(double spending[], int days) {
    // Копіювання масиву витрат
    double copy[31];

    for (int i = 0; i < days; i++) {
        copy[i] = spending[i];
    }

    // Упорядкування витрат за спаданням
    for (int i = 0; i < days - 1; i++) {
        for (int j = i + 1; j < days; j++) {
            if (copy[j] > copy[i]) {
                double temp = copy[i];
                copy[i] = copy[j];
                copy[j] = temp;
            }
        }
    }

    // Визначення кількості результатів
    int count = 3;
    if (days < 3) {
        count = days;
    }

    // Вивід результатів
    cout << "Топ-" << count << " витрат: ";

    for (int i = 0; i < count; i++) {
        cout << copy[i];

        if (i < count - 1) {
            cout << ", ";
        }
    }

    cout << " грн" << endl;
}
