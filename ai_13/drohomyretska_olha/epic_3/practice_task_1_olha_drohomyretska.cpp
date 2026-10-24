/*
Задача: Аналізатор місячного бюджету
Автор: Дрогомирецька Ольга
Група: ШІ-13
*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int MAX = 31;

double input(const char*);
int readInt(const char*, int, int);
double sum(const double[], int);
void minMax(const double[], int, double&, double&);
void showDays(const double[], int);
void statistics(const double[], int, double);
void limitDays(const double[], int, double = 1000);
void topThree(const double[], int);

int main() {
    cout << fixed << setprecision(2);

    double budget = input("Бюджет на місяць (грн): ");
    int n = readInt("Кількість днів обліку: ", 1, MAX);

    double a[MAX];
    cout << "Витрати по днях (грн): ";

    for (int i = 0; i < n; i++) {
        while (!(cin >> a[i]) || !isfinite(a[i]) || a[i] < 0) {
            cout << "Помилка! Введіть витрати за день "
                 << i + 1 << " ще раз: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int choice;
    do {
    menu:
        cout << "\n1 - Показати витрати по днях\n"
             << "2 - Статистика витрат\n"
             << "3 - Дні з перевищенням денного ліміту\n"
             << "4 - Три найдорожчі дні\n"
             << "0 - Вийти\n"
             << "Ваш вибір: ";

        if (!(cin >> choice) || choice < 0 || choice > 4) {
            cout << "Неправильний пункт меню!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            goto menu;
        }

        switch (choice) {
            case 1:
                showDays(a, n);
                break;

            case 2:
                statistics(a, n, budget);
                break;

            case 3: {
                double limit = input(
                    "Денний ліміт (грн, 0 = за замовчуванням): ");

                if (limit == 0)
                    limitDays(a, n);
                else
                    limitDays(a, n, limit);
                break;
            }

            case 4:
                topThree(a, n);
                break;

            case 0:
                cout << "Програму завершено.\n";
                break;
        }
    } while (choice != 0);
    return 0;
}
// Введення невід'ємного числа
double input(const char* msg) {
    double x;

    while (true) {
        cout << msg;

        if (cin >> x && isfinite(x) && x >= 0)
            return x;

        cout << "Помилка! Введіть невід'ємне число.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// Введення цілого числа в межах
int readInt(const char* msg, int min, int max) {
    int x;

    while (true) {
        cout << msg;

        if (cin >> x && x >= min && x <= max)
            return x;

        cout << "Помилка! Введіть ціле число від "
             << min << " до " << max << ".\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

// Рекурсивне обчислення суми
double sum(const double a[], int n) {
    if (n == 0)
        return 0;

    return a[n - 1] + sum(a, n - 1);
}

// Мінімум і максимум через параметри-посилання
void minMax(const double a[], int n, double& mn, double& mx) {
    mn = mx = a[0];

    for (int i = 1; i < n; i++) {
        if (a[i] < mn) mn = a[i];
        if (a[i] > mx) mx = a[i];
    }
}

// Показ витрат по днях
void showDays(const double a[], int n) {
    cout << "\nДень\tВитрати, грн\n";

    for (int i = 0; i < n; i++)
        cout << i + 1 << "\t" << a[i] << '\n';
}

// Статистика витрат
void statistics(const double a[], int n, double budget) {
    double mn, mx;
    double total = sum(a, n);
    double purchases = 0;
    int count = 0;

    minMax(a, n, mn, mx);

    cout << "\nМінімальні витрати за день: "
         << mn << " грн\n";
    cout << "Максимальні витрати за день: "
         << mx << " грн\n";
    cout << "Сумарні витрати: " << total << " грн\n";

    if (total > budget)
        cout << "Перевитрата понад бюджет: "
             << abs(budget - total) << " грн\n";
    else
        cout << "Залишок бюджету: "
             << budget - total << " грн\n";

    for (int i = 0; i < n; i++) {
        if (a[i] == 0)
            continue;

        purchases += a[i];
        count++;
    }

    cout << "Днів з покупками: " << count << '\n';

    // Перевіряю чи були взагалі дні з покупками
    if (count > 0)
        cout << "Середні витрати за такий день: "
             << purchases / count << " грн\n";
    else
        cout << "Покупок не було.\n";
    
// Перевіряю коли бюджет вичерпано
    double spent = 0;
    int day = 0;
    bool exhausted = false;

    while (day < n) {
        spent += a[day];
        day++;

        if (spent > budget) {
            cout << "Бюджет вичерпано на дні "
                 << day << ", накопичено "
                 << spent << " грн.\n";
            exhausted = true;
            break;
        }
    }

    if (!exhausted)
        cout << "Бюджет не перевищено. Залишок: "
             << budget - spent << " грн.\n";
}

// Дні з перевищенням денного ліміту
void limitDays(const double a[], int n, double limit) {
    int count = 0;

    cout << "Ліміт: " << limit << " грн\n";

    for (int i = 0; i < n; i++) {
        if (a[i] > limit) {
            cout << "  день " << i + 1 << ": "
                 << a[i] << " грн\n";
            count++;
        }
    }

    cout << "Разом днів з перевищенням: "
         << count << '\n';
}

// Три найбільші витрати
void topThree(const double a[], int n) {
    double b[MAX];

    for (int i = 0; i < n; i++)
        b[i] = a[i];

// Бульбашкове сортування
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (b[j] < b[j + 1]) {
                double temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }
// тернарний оператор
    int count = (n < 3) ? n : 3;

    cout << "Топ-" << count << " витрат: ";

    for (int i = 0; i < count; i++) {
        if (i > 0) cout << ", ";
        cout << b[i];
    }

    cout << " грн\n";
}