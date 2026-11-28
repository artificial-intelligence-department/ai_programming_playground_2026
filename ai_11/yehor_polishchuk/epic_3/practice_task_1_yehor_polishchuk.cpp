#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int MAX_DAYS = 31;

// 1 пункт
void showSpending(const double arr[], int n) {
    cout << "День     Витрати, грн" << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(4) << i + 1 << setw(15) << arr[i] << endl;
    }
}

// 2 функція: допоміжні частини
// мінімальні та максимальні витрати за день
void minmax(const double arr[], int n, double &minVal, double &maxVal) {
    minVal = arr[0];
    maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
}

// сума рекурсією
double sumRec(const double arr[], int n) {
    if (n == 0) {
        return 0;
    }
    return arr[n - 1] + sumRec(arr, n - 1);
}

// середнє за дні з покупками
double happydays(const double arr[], int n, int &count) {
    double sum = 0;
    count = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            continue;
        }
        sum += arr[i];
        count++;
    }

    if (count == 0) {
        return 0;
    }

    return sum / count;
}

// день, коли вичерпано бюджет
void budgetExhaustedDay(const double arr[], int n, double budget) {
    double nakopycheno = 0;
    int i = 0;
    int day = -1;

    while (i < n) {
        nakopycheno += arr[i];

        if (nakopycheno > budget) {
            day = i + 1;
            break;
        }
        i++;
    }

    if (day == -1) {
        cout << "Бюджету вистачило, залишок: " << budget - nakopycheno << " грн." << endl;
    } else {
        cout << "Бюджет вичерпано на дні " << day
             << ", накопичено " << nakopycheno << " грн." << endl;
    }
}

// 2 пункт
void showStats(const double arr[], int n, double budget) {
    double minVal, maxVal;
    minmax(arr, n, minVal, maxVal);
    double total = sumRec(arr, n);

    cout << "Мінімальні витрати за день:" << setw(11) << minVal << " грн" << endl;
    cout << "Максимальні витрати за день:" << setw(10) << maxVal << " грн" << endl;
    cout << "Сумарні витрати:" << setw(22) << total << " грн" << endl;

    double remainder = budget - total;
    if (remainder < 0) {
        cout << "Перевитрата понад бюджет:" << setw(13) << fabs(remainder) << " грн" << endl;
    } else {
        cout << "Залишок бюджету:" << setw(22) << remainder << " грн" << endl;
    }

    int count;
    double avg = happydays(arr, n, count);
    cout << "Днів з покупками:" << setw(21) << count << endl;
    cout << "Середні витрати за такий день:" << setw(8) << avg << " грн" << endl;

    budgetExhaustedDay(arr, n, budget);
}

// 3 пункт
void showOverLimit(const double arr[], int n, double limit = 1000) {
    cout << "Ліміт: " << limit << " грн" << endl;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] > limit) {
            cout << "  день " << i + 1 << ": " << arr[i] << " грн" << endl;
            count++;
        }
    }

    cout << "Разом днів з перевищенням: " << count << endl;
}

// 4 пункт
void top3(const double arr[], int n) {
    // 1. копія масиву
    double copy[MAX_DAYS];
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }

    // 2. сортування «бульбашкою» за спаданням
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (copy[j] < copy[j + 1]) {
                double tmp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = tmp;
            }
        }
    }

    int top = (n < 3) ? n : 3;
    cout << "Топ-" << top << " витрат: ";
    for (int i = 0; i < top; i++) {
        cout << copy[i];
        if (i < top - 1) {
            cout << ", ";
        }
    }
    cout << " грн" << endl;
}

void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

double readBudget() {
    double b;
    while (true) {
        cout << "Бюджет на місяць (грн): ";
        if (cin >> b && b > 0) return b;
        if (cin.eof()) return 0;
        cout << "Помилка: введіть додатне число." << endl;
        clearInput();
    }
}

int readDays() {
    int n;
    while (true) {
        cout << "Кількість днів обліку (1-" << MAX_DAYS << "): ";
        if (cin >> n && n >= 1 && n <= MAX_DAYS) return n;
        if (cin.eof()) return 0;
        cout << "Помилка: введіть ціле число від 1 до " << MAX_DAYS << "." << endl;
        clearInput();
    }
}

void readSpending(double arr[], int n) {
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < n; i++) {
        while (!(cin >> arr[i]) || arr[i] < 0) {
            if (cin.eof()) return;
            cout << "Помилка у значенні для дня " << i + 1
                 << ". Введіть невід'ємне число: ";
            clearInput();
        }
    }
}

// меню
void printMenu() {
    cout << endl;
    cout << "===== МЕНЮ =====" << endl;
    cout << "1. Показати витрати по днях" << endl;
    cout << "2. Статистика витрат" << endl;
    cout << "3. Дні з перевищенням денного ліміту" << endl;
    cout << "4. Три найдорожчі дні" << endl;
    cout << "0. Вийти" << endl;
}

int main() {
    double spending[MAX_DAYS];

    double budget = readBudget();
    if (cin.fail()) return 1;

    int n = readDays();
    if (cin.fail()) return 1;

    readSpending(spending, n);
    if (cin.fail()) return 1;

    cout << fixed << setprecision(2);

    int choice;
    do {
    menu:
        printMenu();
        cout << "Ваш вибір: ";
        if (!(cin >> choice) || choice < 0 || choice > 4) {
            if (cin.eof()) return 1;
            cout << "Невірний пункт меню, спробуйте ще раз." << endl;
            clearInput();
            goto menu;                      // повернення до меню
        }

        switch (choice) {
            case 1:
                showSpending(spending, n);
                break;
            case 2:
                showStats(spending, n, budget);
                break;
            case 3: {
                double limit;
                 cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                if (!(cin >> limit) || limit < 0) {
                    if (cin.eof()) return 1;
                    cout << "Невірний ліміт." << endl;
                    clearInput();
                    goto menu;
                }
                if (limit == 0) showOverLimit(spending, n);
                else showOverLimit(spending, n, limit);
                break;
            }
            case 4:
                top3(spending, n);
                break;
        }
    } while (choice != 0);

    cout << "кінець" << endl;
    return 0;
}