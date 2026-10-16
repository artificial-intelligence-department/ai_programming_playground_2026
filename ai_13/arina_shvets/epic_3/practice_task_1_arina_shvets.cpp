#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
 
// Показати витрати по днях
void showSpending(double a[], int n) {
    cout << "День\tВитрати, грн" << endl << fixed << setprecision(2);
    for (int i = 0; i < n; i++) {
        cout << setw(4) << i + 1 << "\t\t" << a[i] << endl;
    }
}
 
// Сума витрат
double total(double a[], int n) {
    if (n == 0) return 0;
    return a[n - 1] + total(a, n - 1);
}
 
// Мінімум і максимум
void minMax(double a[], int n, double &mn, double &mx) {
    mn = a[0];
    mx = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < mn) mn = a[i];
        if (a[i] > mx) mx = a[i];
    }
}
 
// Статистика витрат
void statistics(double a[], int n, double budget) {
    cout << fixed << setprecision(2);

    double mn, mx;
    minMax(a, n, mn, mx);
    cout << "Мінімальні витрати за день:     " << setw(8) << mn << " грн" << endl;
    cout << "Максимальні витрати за день:   " << setw(8) << mx << " грн" << endl;
 
    double sum = total(a, n);
    cout << "Сумарні витрати:               " << setw(8) << sum << " грн" << endl;
 
    if (sum > budget) {
        cout << "Перевитрата понад бюджет:      " << setw(8) << fabs(budget - sum) << " грн" << endl;
    } else {
        cout << "Залишок бюджету:               " << setw(8) << budget - sum << " грн" << endl;
    }
 
    // середні витрати за дні з покупками
    double s = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) continue;
        s += a[i];
        cnt++;
    }
    if (cnt > 0) cout << "Середні витрати (дні з покупками): " << s / cnt << endl;
    else cout << "Покупок не було" << endl;
 
    // день, коли бюджет вичерпано
    double acc = 0;
    int i = 0;
    bool exhausted = false;
    while (i < n) {
        acc += a[i];
        if (acc > budget) {
            cout << "Бюджет вичерпано на день " << i + 1 << endl;
            exhausted = true;
            break;
        }
        i++;
    }
    if (!exhausted) cout << "Бюджету вистачило, залишок: " << budget - acc << endl;
}
 
// Дні з перевищенням ліміту
void overLimit(double a[], int n, double limit = 1000) {
    cout << fixed << setprecision(2);
    int count = 0;

    if (limit == 0) {
        limit = 1000;
    }

    cout << "Ліміт: " << limit << " грн" << endl;
    for (int i = 0; i < n; i++) {
        if (a[i] > limit) {
            cout << "    день " << i + 1 << ": " << a[i] << " грн" << endl;
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}
 
// Три найдорожчі дні
void topThree(double a[], int n) {
    double b[31];
    for (int i = 0; i < n; i++) b[i] = a[i];
 
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (b[j] < b[j + 1]) {
                double t = b[j];
                b[j] = b[j + 1];
                b[j + 1] = t;
            }
        }
    }
 
    int k = 3;
    if (n < 3) k = n;
    cout << "Топ-3 витрат ";
    for (int i = 0; i < k; i++) cout << b[i] << " ";
    cout << "\n";
}
 
int main() {
    double budget;
    int n;
    double spending[31];
 
    cout << "Бюджет на місяць: ";
    while (!(cin >> budget) || budget <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Помилка! Введіть додатне число: ";
    }
 
    cout << "Кількість днів (1-31): ";
    while (!(cin >> n) || n < 1 || n > 31) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Помилка! Введіть ціле число від 1 до 31: ";
    }
 
    cout << "Витрати по днях: ";
    for (int i = 0; i < n; i++) {
        while (!(cin >> spending[i]) || spending[i] < 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка! Введіть число >= 0: ";
        }
    }
 
    int choice;
    double limit;
 
    do {
    menu:
        cout << "--- Меню ---" << endl;
        cout << "1. Показати витрати по днях" << endl;
        cout << "2. Статистика витрат" << endl;
        cout << "3. Дні з перевищенням денного ліміту" << endl;
        cout << "4. Три найдорожчі дні" << endl;
        cout << "0. Вийти" << endl;
        cout << "Ваш вибір: ";
 
        if (!(cin >> choice)) {         
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка! Введіть число." << endl;
            goto menu;
        }
 
        switch (choice) {
            case 1:
                showSpending(spending, n);
                break;
            case 2:
                statistics(spending, n, budget);
                break;
            case 3:
                cout << "Денний ліміт (0 = 1000): ";
                if (!(cin >> limit) || limit < 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Помилка! Некоректний ліміт." << endl;
                    goto menu;
                }
                if (limit == 0) overLimit(spending, n);
                else overLimit(spending, n, limit);
                break;
            case 4:
                topThree(spending, n);
                break;
            case 0:
                break;
            default:                      // неправильний пункт
                cout << "Немає такого пункту меню." << endl;
                goto menu;
        }
    } while (choice != 0);
 
    return 0;
}