/*
 Аналізатор місячного бюджету
 Рудь Дмитро, група СШІ-11
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <limits>

using namespace std;

const int MAX_DAYS = 31;              // облік ведеться не довше одного місяця
const double DEFAULT_LIMIT = 1000.0;  // денний ліміт за замовчуванням

// ---------------------------------------------------------------
//  Допоміжні функції введення (перевірка нечислових символів)
// ---------------------------------------------------------------

// Після числа має йти пробіл, кінець рядка або кінець вводу ("12abc", "5.5" для int - помилка)
bool endOfToken() {
    int c = cin.peek();
    return c == '\n' || c == ' ' || c == '\t' || c == '\r' || c == EOF;
}

// Скидає стан помилки cin і викидає решту рядка, щоб не було зациклення
void discardLine() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool readDouble(double &x) {
    if (cin >> x && endOfToken()) return true;
    if (cin.eof()) {
        cout << "\nВведення завершено. Вихід з програми." << endl;
        exit(0);
    }
    discardLine();
    return false;
}

bool readInt(int &x) {
    if (cin >> x && endOfToken()) return true;
    if (cin.eof()) {
        cout << "\nВведення завершено. Вихід з програми." << endl;
        exit(0);
    }
    discardLine();
    return false;
}

// ---------------------------------------------------------------
//  Функції меню
// ---------------------------------------------------------------

void displayMenu() {
    cout << "Меню:\n"
         << "1 - Показати витрати по днях\n"
         << "2 - Статистика витрат\n"
         << "3 - Дні з перевищенням денного ліміту\n"
         << "4 - Три найдорожчі дні\n"
         << "0 - Вийти\n";
}

// Пункт 1
void showSpending(const double spending[], int n) {
    cout << "День     Витрати, грн\n";
    for (int i = 0; i < n; i++) {
        cout << setw(4) << i + 1 << setw(17) << spending[i] << "\n";
    }
}

// Рекурсивна сума перших n елементів (без циклу)
double sumSpending(const double spending[], int n) {
    if (n == 0) {
        return 0.0;                                     // база рекурсії
    }
    return spending[n - 1] + sumSpending(spending, n - 1);
}

// Мінімум і максимум повертаються через параметри-посилання
void findMinMax(const double spending[], int n, double &minValue, double &maxValue) {
    minValue = spending[0];
    maxValue = spending[0];
    for (int i = 1; i < n; i++) {
        if (spending[i] < minValue) minValue = spending[i];
        if (spending[i] > maxValue) maxValue = spending[i];
    }
}

// Пункт 2
void showStatistics(const double spending[], int n, double budget) {
    double minSpending, maxSpending;
    findMinMax(spending, n, minSpending, maxSpending);
    double total = sumSpending(spending, n);
    double balance = budget - total;

    cout << "Мінімальні витрати за день: " << minSpending << " грн\n";
    cout << "Максимальні витрати за день: " << maxSpending << " грн\n";
    cout << "Сумарні витрати: " << total << " грн\n";
    if (balance < 0) {
        cout << "Перевитрата понад бюджет: " << fabs(balance) << " грн\n";
    } else {
        cout << "Залишок бюджету: " << balance << " грн\n";
    }

    // Середні витрати лише за дні з покупками (дні з нулем пропускаємо через continue)
    int purchaseDays = 0;
    double purchaseSum = 0.0;
    for (int i = 0; i < n; i++) {
        if (spending[i] <= 0) {
            continue;
        }
        purchaseSum += spending[i];
        purchaseDays++;
    }
    cout << "Днів з покупками: " << purchaseDays << "\n";
    if (purchaseDays > 0) {
        cout << "Середні витрати за такий день: " << purchaseSum / purchaseDays << " грн\n";
    } else {
        cout << "Середні витрати за такий день: немає днів з покупками\n";
    }

    // День, коли бюджет вичерпано: накопичуємо циклом while, виходимо через break
    double accumulated = 0.0;
    int day = 0;
    bool exhausted = false;
    while (day < n) {
        accumulated += spending[day];
        day++;
        if (accumulated > budget) {
            exhausted = true;
            break;
        }
    }
    if (exhausted) {
        cout << "Бюджет вичерпано на дні " << day
             << ", накопичено " << accumulated << " грн.\n";
    } else {
        cout << "Бюджету вистачило на всі дні, залишок: " << balance << " грн\n";
    }
}

// Пункт 3 (ліміт - параметр за замовчуванням)
void dailyLimitExceeded(const double spending[], int n, double limit = DEFAULT_LIMIT) {
    cout << "Ліміт: " << limit << " грн\n";
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (spending[i] > limit) {
            cout << "день " << i + 1 << ": " << spending[i] << " грн\n";
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << "\n";
}

// Пункт 4 (сортуємо КОПІЮ масиву вкладеними циклами, оригінал не змінюється)
void threeMostExpensiveDays(const double spending[], int n) {
    double sorted[MAX_DAYS];
    for (int i = 0; i < n; i++) {
        sorted[i] = spending[i];
    }

    // сортування вибором за спаданням
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (sorted[j] > sorted[i]) {
                double temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }

    int k = (n < 3) ? n : 3;
    cout << "Топ-" << k << " витрат: ";
    for (int i = 0; i < k; i++) {
        if (i > 0) cout << ", ";
        cout << sorted[i];
    }
    cout << " грн\n";
}

// ---------------------------------------------------------------
//  main
// ---------------------------------------------------------------

int main() {
    double budget;
    int n;
    double spending[MAX_DAYS];

    cout << "Бюджет на місяць (грн): ";
    while (!readDouble(budget) || budget <= 0) {
        cout << "Бюджет має бути додатним числом. Введіть ще раз: ";
    }

    cout << "Кількість днів обліку: ";
    while (!readInt(n) || n < 1 || n > MAX_DAYS) {
        cout << "Кількість днів - ціле число від 1 до " << MAX_DAYS << ". Введіть ще раз: ";
    }

    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < n; i++) {
        double value;
        while (!readDouble(value) || value < 0) {
            cout << "Витрати за день " << i + 1
                 << " - число не менше 0. Введіть це значення ще раз: ";
        }
        spending[i] = value;
    }
    cout << "\n";

    cout << fixed << setprecision(2);   // один раз для всієї програми

    int choice;
    do {
menu:
        displayMenu();
        cout << "Виберіть пункт меню: ";
        if (!readInt(choice) || choice < 0 || choice > 4) {
            cout << "Невірний пункт меню. Введіть число від 0 до 4.\n\n";
            goto menu;                  // назад до меню
        }
        cout << "\n";

        switch (choice) {
            case 1:
                showSpending(spending, n);
                break;
            case 2:
                showStatistics(spending, n, budget);
                break;
            case 3: {
                double limit;
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                if (!readDouble(limit) || limit < 0) {
                    cout << "Ліміт має бути числом не менше 0.\n\n";
                    goto menu;          // назад до меню
                }
                if (limit == 0) {
                    dailyLimitExceeded(spending, n);          // береться 1000 грн
                } else {
                    dailyLimitExceeded(spending, n, limit);
                }
                break;
            }
            case 4:
                threeMostExpensiveDays(spending, n);
                break;
            case 0:
                cout << "Вихід з програми.\n";
                break;
        }
        cout << "\n";
    } while (choice != 0);

    return 0;
}