/* 
 Аналізатор місячного бюджету
 Автор: Serhii Yurchenko
 Група: AI-13
 */
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;
 
const int MAX_DAYS = 31;              // максимальна тривалість обліку
const double MAX_AMOUNT = 1000000000; // верхня межа допустимих сум
const double DEFAULT_LIMIT = 1000.0;  // денний ліміт за замовчуванням
 
// Введення та валідація
 
// Скидає стан помилки потоку й відкидає залишок рядка
void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}
 
// Перевіряє, що після числа йде пробіл, кінець рядка або кінець вводу
bool endsCleanly() {
    int next = cin.peek();
    if (cin.eof()) return true;
    return next == ' ' || next == '\t' || next == '\n';
}
 
// Запитує дійсне число з діапазону [lo; hi]; false — ввід завершено
bool askDouble(string prompt, double lo, double hi, double &value) {
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            if (cin.eof()) return false;
            cout << "Помилка: введіть число.\n";
        } else if (!endsCleanly()) {
            cout << "Помилка: зайві символи після числа.\n";
        } else if (value < lo || value > hi) {
            cout << "Помилка: значення має бути від " << lo << " до " << hi << ".\n";
        } else {
            clearInput();
            return true;
        }
        clearInput();
    }
}
 
// Запитує ціле число з діапазону [lo; hi]; false — ввід завершено
bool askInt(string prompt, int lo, int hi, int &value) {
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            if (cin.eof()) return false;
            cout << "Помилка: введіть ціле число.\n";
        } else if (!endsCleanly()) {
            cout << "Помилка: зайві символи після числа.\n";
        } else if (value < lo || value > hi) {
            cout << "Помилка: значення має бути від " << lo << " до " << hi << ".\n";
        } else {
            clearInput();
            return true;
        }
        clearInput();
    }
}
 
// Зчитує витрати за n днів; при помилці перепитує лише проблемний день
bool readSpending(double spending[], int n) {
    cout << "Витрати по днях (грн), " << n << " чисел поспіль: ";
    int i = 0;
    while (i < n) {
        if (!(cin >> spending[i])) {
            if (cin.eof()) return false;
            cout << "Помилка в дні " << i + 1 << ": введіть число.\n";
        } else if (!endsCleanly()) {
            cout << "Помилка в дні " << i + 1 << ": зайві символи після числа.\n";
        } else if (spending[i] < 0 || spending[i] > MAX_AMOUNT) {
            cout << "Помилка в дні " << i + 1 << ": значення від 0 до " << MAX_AMOUNT << ".\n";
        } else {
            i++;
            continue;
        }
        clearInput();
        cout << "Продовжіть з дня " << i + 1 << ": ";
    }
    clearInput();
    return true;
}
 
// Обчислення
 
// Сума елементів від індексу i до n-1 (рекурсивно)
double sumRecursive(const double arr[], int i, int n) {
    if (i == n) return 0;
    return arr[i] + sumRecursive(arr, i + 1, n);
}
 
// Мінімум і максимум повертаються через параметри-посилання
void findMinMax(const double arr[], int n, double &minValue, double &maxValue) {
    minValue = arr[0];
    maxValue = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minValue) minValue = arr[i];
        if (arr[i] > maxValue) maxValue = arr[i];
    }
}
 
// Пункти меню
 
// 1. Витрати по днях
void showSpending(const double spending[], int n) {
    cout << "\n День      Витрати, грн\n";
    for (int i = 0; i < n; i++) {
        cout << setw(5) << i + 1 << setw(18) << spending[i] << "\n";
    }
}
 
// 2. Статистика витрат
void showStatistics(const double spending[], int n, double budget) {
    double minValue, maxValue;
    findMinMax(spending, n, minValue, maxValue);
    double total = sumRecursive(spending, 0, n);
    double balance = budget - total;
 
    cout << "\n";
    cout << "Мінімальні витрати за день:    " << minValue << " грн\n";
    cout << "Максимальні витрати за день:   " << maxValue << " грн\n";
    cout << "Сумарні витрати:               " << total << " грн\n";
 
    if (balance >= 0)
        cout << "Залишок бюджету:               " << balance << " грн\n";
    else
        cout << "Перевитрата понад бюджет:      " << fabs(balance) << " грн\n";
 
    // Середні витрати за дні з покупками
    double purchaseSum = 0;
    int purchaseDays = 0;
    for (int i = 0; i < n; i++) {
        if (spending[i] == 0) continue;
        purchaseSum += spending[i];
        purchaseDays++;
    }
    cout << "Днів з покупками:              " << purchaseDays << "\n";
    if (purchaseDays > 0)
        cout << "Середні витрати за такий день: " << purchaseSum / purchaseDays << " грн\n";
    else
        cout << "Середні витрати за такий день: немає днів з покупками\n";
 
    // День вичерпання бюджету
    double accumulated = 0;
    int day = 0;
    bool exhausted = false;
    while (day < n) {
        accumulated += spending[day];
        if (accumulated > budget) {
            exhausted = true;
            break;
        }
        day++;
    }
    if (exhausted)
        cout << "Бюджет вичерпано на дні " << day + 1 << ", накопичено " << accumulated << " грн.\n";
    else
        cout << "Бюджету вистачило на всі дні, залишок " << budget - accumulated << " грн.\n";
}
 
// 3. Дні з перевищенням денного ліміту
void showOverLimit(const double spending[], int n, double limit = DEFAULT_LIMIT) {
    cout << "\nЛіміт: " << limit << " грн\n";
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (spending[i] > limit) {
            cout << "  день " << i + 1 << ": " << spending[i] << " грн\n";
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << "\n";
}
 
// Запитує ліміт (0 — значення за замовчуванням); false — ввід завершено
bool overLimitMenu(const double spending[], int n) {
    double limit;
    if (!askDouble("Денний ліміт (грн, 0 = за замовчуванням): ", 0, MAX_AMOUNT, limit))
        return false;
    if (limit == 0)
        showOverLimit(spending, n);
    else
        showOverLimit(spending, n, limit);
    return true;
}
 
// 4. Три найдорожчі дні
void showTopThree(const double spending[], int n) {
    double sorted[MAX_DAYS];
    for (int i = 0; i < n; i++) {
        sorted[i] = spending[i];
    }
 
    // Сортування копії за спаданням; оригінал не змінюється
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (sorted[j] < sorted[j + 1]) {
                double tmp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = tmp;
            }
        }
    }
 
    int shown = n < 3 ? n : 3;
    cout << "\nТоп-" << shown << " витрат: ";
    for (int i = 0; i < shown; i++) {
        if (i > 0) cout << ", ";
        cout << sorted[i];
    }
    cout << " грн\n";
}
 
// main
 
int main() {
    cout << fixed << setprecision(2);
 
    double budget;
    int n;
    double spending[MAX_DAYS];
 
    if (!askDouble("Бюджет на місяць (грн): ", 0.01, MAX_AMOUNT, budget) ||
        !askInt("Кількість днів обліку: ", 1, MAX_DAYS, n) ||
        !readSpending(spending, n)) {
        cout << "\nВвід завершено до отримання всіх даних.\n";
        return 1;
    }
 
    int choice = -1;
 
    do {
    main_menu:
        cout << "\n=== МЕНЮ ===\n"
             << "1. Показати витрати по днях\n"
             << "2. Статистика витрат\n"
             << "3. Дні з перевищенням денного ліміту\n"
             << "4. Три найдорожчі дні\n"
             << "0. Вийти\n"
             << "Ваш вибір: ";
 
        if (!(cin >> choice)) {
            if (cin.eof()) {
                cout << "\nВвід завершено.\n";
                return 0;
            }
            clearInput();
            cout << "Помилка: оберіть пункт від 0 до 4.\n";
            goto main_menu;
        }
        if (!endsCleanly()) {
            clearInput();
            cout << "Помилка: оберіть пункт від 0 до 4.\n";
            goto main_menu;
        }
        clearInput();
 
        // Номер поза меню — повернення до меню
        if (choice < 0 || choice > 4) {
            cout << "Помилка: оберіть пункт від 0 до 4.\n";
            goto main_menu;
        }
 
        switch (choice) {
            case 1: showSpending(spending, n); break;
            case 2: showStatistics(spending, n, budget); break;
            case 3:
                if (!overLimitMenu(spending, n)) {
                    cout << "\nВвід завершено.\n";
                    return 0;
                }
                break;
            case 4: showTopThree(spending, n); break;
            case 0: cout << "До побачення!\n"; break;
        }
    } while (choice != 0);
 
    return 0;
}
