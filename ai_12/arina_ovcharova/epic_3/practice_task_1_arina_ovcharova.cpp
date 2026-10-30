#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;

const int MAX_DAYS = 31;

// Зчитує число з клавіатури. Повертає false, якщо введено не число
// або одразу після числа йдуть зайві символи (наприклад, 8000abc).
bool readNumber(double &x) {
    if (!(cin >> x)) {
        if (cin.eof()) exit(0);      // кінець вводу
        cin.clear();                 // скидаємо стан помилки
        cin.ignore(10000, '\n');     // викидаємо некоректний ввід
        return false;
    }
    int c = cin.peek();              // який символ іде після числа
    if (c != '\n' && c != ' ' && c != '\t' && c != '\r' && c != EOF) {
        cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

// Сумарні витрати рекурсивно (без циклу)
double sumRecursive(double a[], int n) {
    if (n == 0) return 0;
    return a[n - 1] + sumRecursive(a, n - 1);
}

// Мінімум і максимум повертаються через параметри-посилання
void findMinMax(double a[], int n, double &mn, double &mx) {
    mn = a[0];
    mx = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < mn) mn = a[i];
        if (a[i] > mx) mx = a[i];
    }
}

// Пункт 1: витрати по днях
void showDays(double a[], int n) {
    cout << "День Витрати, грн\n";
    for (int i = 0; i < n; i++)
        cout << setw(4) << i + 1 << setw(14) << a[i] << "\n";
}

// Пункт 2: статистика
void showStats(double a[], int n, double budget) {
    double mn, mx;
    findMinMax(a, n, mn, mx);
    double total = sumRecursive(a, n);
    cout << "Мінімальні витрати за день: " << mn << " грн\n";
    cout << "Максимальні витрати за день: " << mx << " грн\n";
    cout << "Сумарні витрати: " << total << " грн\n";
    if (total > budget)
        cout << "Перевитрата понад бюджет: " << fabs(budget - total) << " грн\n";
    else
        cout << "Залишок бюджету: " << budget - total << " грн\n";

    // середні витрати за дні з покупками (дні з нулем пропускаємо)
    double s = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) continue;
        s += a[i];
        count++;
    }
    cout << "Днів з покупками: " << count << "\n";
    if (count > 0)
        cout << "Середні витрати за день з покупками: " << s / count << " грн\n";
    else
        cout << "Середніх витрат немає: днів з покупками не було\n";

    // день, коли бюджет вичерпано
    double spent = 0;
    int i = 0;
    bool found = false;
    while (i < n) {
        spent += a[i];
        i++;
        if (spent > budget) {
            found = true;
            break;
        }
    }
    if (found)
        cout << "Бюджет вичерпано на день " << i
             << ", накопичено " << spent << " грн\n";
    else
        cout << "Бюджету вистачило на всі дні, залишок: "
             << budget - spent << " грн\n";
}

// Пункт 3: дні з перевищенням ліміту (за замовчуванням 1000 грн)
void showLimit(double a[], int n, double limit = 1000) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > limit) {
            cout << " день " << i + 1 << ": " << a[i] << " грн\n";
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << "\n";
}

// Пункт 4: три найдорожчі дні (сортуємо копію масиву)
void showTop(double a[], int n) {
    double b[MAX_DAYS];
    for (int i = 0; i < n; i++) b[i] = a[i];
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (b[j] > b[i]) {
                double t = b[i];
                b[i] = b[j];
                b[j] = t;
            }
    cout << "Топ-" << (n < 3 ? n : 3) << " витрат: ";
    for (int i = 0; i < n && i < 3; i++) {
        cout << b[i];
        if (i < n - 1 && i < 2) cout << ", ";
    }
    cout << " грн\n";
}

int main() {
    cout << fixed << setprecision(2);
    double budget, a[MAX_DAYS];
    int n, choice;

    cout << "Бюджет на місяць (грн): ";
    if (!readNumber(budget) || budget <= 0) {
        cout << "Помилка введення бюджету\n";
        return 0;
    }

    cout << "Кількість днів обліку: ";
    double nd;
    if (!readNumber(nd) || nd != floor(nd) || nd < 1 || nd > MAX_DAYS) {
        cout << "Помилка введення кількості днів\n";
        return 0;
    }
    n = static_cast<int>(nd);

    cout << "Витрати по днях (грн):\n";
    for (int i = 0; i < n; i++) {
        if (!readNumber(a[i]) || a[i] < 0) {
            cout << "Помилка введення витрат за день " << i + 1 << "\n";
            return 0;
        }
    }

    do {
    menu:
        cout << "\n1 - Показати витрати по днях\n"
                "2 - Статистика витрат\n"
                "3 - Дні з перевищенням денного ліміту\n"
                "4 - Три найдорожчі дні\n"
                "0 - Вийти\n"
                "Ваш вибір: ";
        double v;
        if (!readNumber(v) || v != floor(v)) {   // нечислове або дробове
            cout << "Неправильний пункт меню\n";
            goto menu;
        }
        choice = static_cast<int>(v);
        switch (choice) {
            case 1: showDays(a, n); break;
            case 2: showStats(a, n, budget); break;
            case 3: {
                double limit;
                cout << "Денний ліміт (грн, 0 = за замовчуванням 1000): ";
                if (!readNumber(limit) || limit < 0) {
                    cout << "Помилка введення ліміту\n";
                    goto menu;
                }
                cout << "Ліміт: " << (limit == 0 ? 1000.0 : limit) << " грн\n";
                if (limit == 0) showLimit(a, n);
                else showLimit(a, n, limit);
                break;
            }
            case 4: showTop(a, n); break;
            case 0: cout << "Вихід з програми\n"; break;
            default:
                cout << "Неправильний пункт меню\n";
                goto menu;
        }
    } while (choice != 0);
    return 0;
}