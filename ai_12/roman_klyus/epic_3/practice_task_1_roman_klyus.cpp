#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const int max_days = 31;

void clear_input() {
    cin.clear();
    cin.ignore(1000, '\n');
}

void show_menu() {
    cout << endl;
    cout << "1. Показати витрати по днях" << endl;
    cout << "2. Статистика витрат" << endl;
    cout << "3. Дні з перевищенням денного ліміту" << endl;
    cout << "4. Три найдорожчі дні" << endl;
    cout << "0. Вийти" << endl;
    cout << "Ваш вибір: ";
}

void min_max_values(double spending[], int n, double &min_value, double &max_value) {
    min_value = spending[0];
    max_value = spending[0];

    for (int i = 0; i < n; ++i) {
        if (spending[i] < min_value) min_value = spending[i];
        if (spending[i] > max_value) max_value = spending[i];
    }
}

double sum(double spending[], int n) {
    if (n == 0) return 0;
    return spending[n-1] + sum(spending, n - 1);
}

void show_spending(double spending[], int n) {
    cout << fixed << setprecision(2);
    cout << endl << "День     Витрати, грн" << endl;
    for (int i = 0; i < n; ++i) {
        cout << setw(4) << i+1 << setw(27) << spending[i] << endl;
    }
}

void show_stats(double spending[], int n, int budget) {
    double min_value, max_value;
    min_max_values(spending, n, min_value, max_value);
    double total = sum(spending, n);
    double left = budget - total;

    cout << fixed << setprecision(2) << endl;
    cout << "Мінімальні витрати за день: " << min_value << " грн" << endl;
    cout << "Максимальні витрати за день: " << max_value << " грн" << endl;
    cout << "Сумарні витрати: " << total << " грн" << endl;

    if (left < 0) {
        cout << "Перевитрата понад бюджет: " << fabs(left) << " грн" << endl;
    } else {
        cout << "Залишок бюджету: " << left << " грн" << endl;
    }

    int count = 0;
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        if (spending[i] == 0) continue;
        sum += spending[i];
        count++;
    }

    cout << "Днів з покупками: " << count << endl;
    if (count > 0) {
        cout << "Середні витрати за такий день: " << sum / count << " грн" << endl;
    } else {
        cout << "Середні витрати за такий день: немає днів з покупками" << endl;
    }

    double spent = 0;
    int day = 0;
    while (day < n) {
        spent += spending[day];
        if (spent > budget) break;
        day++;
    }
    
    if (day < n) {
        cout << "Бюджет вичерпано на дні " << day + 1 << ", накопичено " << spent << " грн." << endl;
    } else {
        cout << "Бюджету вистачило на всі дні, залишок: " << budget - spent << " грн." << endl;
    }
}

void show_over_limit(double spending[], int n, double limit = 1000) {
    cout << fixed << setprecision(2);
    cout << "Ліміт: " << limit << " грн" << endl;

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (spending[i] > limit) {
            cout << "  день " << i + 1 << ": " << spending[i] << " грн" << endl;
            count++;
        }
    }

    cout << "Разом днів з перевищенням: " << count << endl;
}

void show_top3(double spending[], int n) {
    double sorted[max_days];
    for (int i = 0; i < n; ++i) sorted[i] = spending[i];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - (i + 1); ++j) {
            if (sorted[j] < sorted[j+1]) {
                double sort = sorted[j];
                sorted[j] = sorted[j+1];
                sorted[j+1] = sort;
            }
        }
    }

    int shown = 3;
    if (n < 3) shown = n;

    cout << fixed << setprecision(2);
    cout << "Топ-" << shown << " витрат: ";
    for (int i = 0; i < shown; i++) {
        if (i > 0) {
            cout << ", ";
        }
        cout << sorted[i];
    }
    cout << " грн" << endl;
}

int main() {
    double budget;
    int n;
    double spending[max_days];

    cout << "Бюджет на місяць (грн): ";
    if (!(cin >> budget) || budget <= 0) {
        cout << "Помилка: бюджет має бути числом, більшим за нуль." << endl;
        return 1;
    }

    cout << "Кількість днів обліку: ";
    if (!(cin >> n) || n < 1 || n > max_days) {
        cout << "Помилка: кількість днів має бути числом від 1 до " << max_days << "." << endl;
        return 1;
    }

    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < n; i++) {
        if (!(cin >> spending[i]) || spending[i] < 0) {
            cout << "Помилка: витрати мають бути числами не менше нуля." << endl;
            return 1;
        }
    }

    int choice;
    do {
    menu:
        if (cin.eof()) {
            return 1;
        }
        show_menu();

        if (!(cin >> choice) || choice < 0 || choice > 4) {
            clear_input();
            cout << "Помилка: оберіть пункт меню від 0 до 4." << endl;
            goto menu;
        }

        switch (choice) {
            case 1:
                show_spending(spending, n);
                break;
            case 2:
                show_stats(spending, n, budget);
                break;
            case 3: {
                double limit;
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                if (!(cin >> limit) || limit < 0) {
                    clear_input();
                    cout << "Помилка: ліміт має бути числом не менше нуля." << endl;
                    goto menu;
                }
                if (limit == 0) {
                    show_over_limit(spending, n);
                } else {
                    show_over_limit(spending, n, limit);
                }
                break;
            }
            case 4:
                show_top3(spending, n);
                break;
        }
    } while (choice != 0);

    return 0;
}