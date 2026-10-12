/*
 * Практична робота: Аналізатор місячного бюджету
 * Ткач Артем
 * ШІ-13
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
using namespace std;

const int MAX_DAYS = 31;
const double DEFAULT_LIMIT = 1000;

// Зчитує дійсне число; false, якщо введено не число
bool readDouble(double &value) {
    if (cin >> value) return true;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}

double readNonNegative(const char *prompt) {
    double v;
    while (true) {
        cout << prompt;
        if (readDouble(v) && v >= 0) return v;
        cout << "Помилка: потрібне невід'ємне число." << endl;
    }
}

int readDays() {
    double v;
    while (true) {
        cout << "Кількість днів обліку (1-" << MAX_DAYS << "): ";
        if (readDouble(v) && v >= 1 && v <= MAX_DAYS && v == floor(v)) return (int)v;
        cout << "Помилка: потрібне ціле число від 1 до " << MAX_DAYS << "." << endl;
    }
}

// Рекурсивна сума
double sumRec(const double a[], int n) {
    if (n == 0) return 0;
    return a[n - 1] + sumRec(a, n - 1);
}

// Мінімум і максимум через параметри-посилання
void minMax(const double a[], int n, double &mn, double &mx) {
    mn = mx = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < mn) mn = a[i];
        if (a[i] > mx) mx = a[i];
    }
}

void showDays(const double a[], int n) {
    cout << "День     Витрати, грн" << endl;
    for (int i = 0; i < n; i++)
        cout << setw(4) << i + 1 << setw(17) << a[i] << endl;
}

void showStats(const double a[], int n, double budget) {
    double mn, mx;
    minMax(a, n, mn, mx);
    double total = sumRec(a, n);
    double rest = budget - total;

    cout << "Мінімальні витрати за день:  " << setw(10) << mn << " грн" << endl;
    cout << "Максимальні витрати за день: " << setw(10) << mx << " грн" << endl;
    cout << "Сумарні витрати:             " << setw(10) << total << " грн" << endl;
    if (rest < 0)
        cout << "Перевитрата понад бюджет:    " << setw(10) << fabs(rest) << " грн" << endl;
    else
        cout << "Залишок бюджету:             " << setw(10) << rest << " грн" << endl;

    int count = 0;
    double buys = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) continue;
        buys += a[i];
        count++;
    }
    cout << "Днів з покупками: " << count << endl;
    if (count > 0)
        cout << "Середні витрати за такий день: " << buys / count << " грн" << endl;
    else
        cout << "Покупок не було, середнє не обчислюється." << endl;

    double acc = 0;
    int day = 0;
    while (day < n) {
        acc += a[day];
        day++;
        if (acc > budget) break;
    }
    if (acc > budget)
        cout << "Бюджет вичерпано на дні " << day << ", накопичено " << acc << " грн." << endl;
    else
        cout << "Бюджету вистачило на всі дні, залишок " << budget - acc << " грн." << endl;
}

void showOverLimit(const double a[], int n, double limit = DEFAULT_LIMIT) {
    cout << "Ліміт: " << limit << " грн" << endl;
    int count = 0;
    for (int i = 0; i < n; i++)
        if (a[i] > limit) {
            cout << "  день " << i + 1 << ": " << a[i] << " грн" << endl;
            count++;
        }
    cout << "Разом днів з перевищенням: " << count << endl;
}

void showTop3(const double a[], int n) {
    double c[MAX_DAYS];
    for (int i = 0; i < n; i++) c[i] = a[i];
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (c[j] < c[j + 1]) {
                double t = c[j];
                c[j] = c[j + 1];
                c[j + 1] = t;
            }
    int k = n < 3 ? n : 3;
    cout << "Топ-" << k << " витрат: ";
    for (int i = 0; i < k; i++)
        cout << c[i] << (i + 1 < k ? ", " : "");
    cout << " грн" << endl;
}

int main() {
    double spending[MAX_DAYS];
    cout << fixed << setprecision(2);

    double budget = readNonNegative("Бюджет на місяць (грн): ");
    int n = readDays();
    for (int i = 0; i < n; i++) {
        cout << "Витрати за день " << i + 1 << " (грн): ";
        double v;
        if (!readDouble(v) || v < 0) {
            cout << "Помилка: потрібне невід'ємне число." << endl;
            i--;
            continue;
        }
        spending[i] = v;
    }

    int choice;
    do {
    menu:
        cout << "\n1 - Витрати по днях\n2 - Статистика\n3 - Дні з перевищенням ліміту\n"
                "4 - Три найдорожчі дні\n0 - Вийти\nПункт: ";
        if (!(cin >> choice) || choice < 0 || choice > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неправильний пункт меню." << endl;
            goto menu;
        }
        switch (choice) {
        case 1:
            showDays(spending, n);
            break;
        case 2:
            showStats(spending, n, budget);
            break;
        case 3: {
            double limit = readNonNegative("Денний ліміт (грн, 0 = за замовчуванням): ");
            if (limit == 0) showOverLimit(spending, n);
            else showOverLimit(spending, n, limit);
            break;
        }
        case 4:
            showTop3(spending, n);
            break;
        }
    } while (choice != 0);
    return 0;
}
