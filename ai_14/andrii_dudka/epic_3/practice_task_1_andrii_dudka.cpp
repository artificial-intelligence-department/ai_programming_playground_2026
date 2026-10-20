#include <cmath>
#include <iostream>
#include <string>

using namespace std;

const int MAX_DAYS = 31;
const double MAX_AMOUNT = 1000000000.0;
const double EPS = 0.0001;

bool isDelimiter(int character) {
    return character < 0 || character == ' ' || character == '\t' ||
           character == '\n' || character == '\r';
}

void clearBadInput() {
    cin.clear();
    string rest;
    getline(cin, rest);
}

bool readDouble(double& value) {
    if (!(cin >> value)) {
        if (!cin.eof()) clearBadInput();
        return false;
    }
    if (!isDelimiter(cin.peek()) || !isfinite(value)) {
        if (!cin.eof()) clearBadInput();
        return false;
    }
    return true;
}

bool readInt(int& value) {
    if (!(cin >> value)) {
        if (!cin.eof()) clearBadInput();
        return false;
    }
    if (!isDelimiter(cin.peek())) {
        if (!cin.eof()) clearBadInput();
        return false;
    }
    return true;
}

bool readAmount(const string& prompt, double& value, bool positive) {
    while (true) {
        cout << prompt;
        if (readDouble(value) && value <= MAX_AMOUNT &&
            (positive ? value > 0 : value >= 0)) {
            return true;
        }
        if (cin.eof()) return false;
        if (positive) cout << "Введіть суму понад 0 і не більше 1000000000 грн.\n";
        else cout << "Введіть суму від 0 до 1000000000 грн.\n";
    }
}

void showSpending(const double spending[], int days) {
    cout << "День\tВитрати, грн\n";
    for (int i = 0; i < days; ++i) {
        cout << i + 1 << '\t' << spending[i] << '\n';
    }
}

void findMinMax(const double spending[], int days, double& minimum, double& maximum) {
    minimum = spending[0];
    maximum = spending[0];
    for (int i = 1; i < days; ++i) {
        if (spending[i] < minimum) minimum = spending[i];
        if (spending[i] > maximum) maximum = spending[i];
    }
}

double sumRecursive(const double spending[], int days) {
    if (days == 0) return 0;
    return spending[days - 1] + sumRecursive(spending, days - 1);
}

void showStatistics(const double spending[], int days, double budget) {
    double minimum, maximum;
    findMinMax(spending, days, minimum, maximum);
    double total = sumRecursive(spending, days);
    double remaining = budget - total;
    if (fabs(remaining) < EPS) remaining = 0;

    cout << "Мінімальні витрати за день: " << minimum << " грн\n";
    cout << "Максимальні витрати за день: " << maximum << " грн\n";
    cout << "Сумарні витрати: " << total << " грн\n";
    if (remaining < 0) {
        cout << "Перевитрата понад бюджет: " << fabs(remaining) << " грн\n";
    } else {
        cout << "Залишок бюджету: " << remaining << " грн\n";
    }

    double purchasesTotal = 0;
    int purchaseDays = 0;
    for (int i = 0; i < days; ++i) {
        if (spending[i] == 0) continue;
        purchasesTotal += spending[i];
        ++purchaseDays;
    }
    cout << "Днів з покупками: " << purchaseDays << '\n';
    if (purchaseDays > 0) {
        cout << "Середні витрати за такий день: "
             << purchasesTotal / purchaseDays << " грн\n";
    } else {
        cout << "Середні витрати за такий день: 0.00 грн\n";
    }

    double accumulated = 0;
    int day = 0;
    while (day < days) {
        accumulated += spending[day];
        if (accumulated > budget + EPS) {
            cout << "Бюджет вичерпано на дні " << day + 1
                 << ", накопичено " << accumulated << " грн.\n";
            break;
        }
        ++day;
    }
    if (day == days) {
        double finalRemaining = budget - accumulated;
        if (fabs(finalRemaining) < EPS) finalRemaining = 0;
        cout << "Бюджету вистачило на всі дні. Залишок: "
             << finalRemaining << " грн.\n";
    }
}

void showDaysOverLimit(const double spending[], int days, double limit = 1000.0) {
    int count = 0;
    cout << "Ліміт: " << limit << " грн\n";
    for (int i = 0; i < days; ++i) {
        if (spending[i] > limit) {
            cout << "  день " << i + 1 << ": " << spending[i] << " грн\n";
            ++count;
        }
    }
    cout << "Разом днів з перевищенням: " << count << '\n';
}

void showTopThree(const double spending[], int days) {
    double copy[MAX_DAYS];
    for (int i = 0; i < days; ++i) copy[i] = spending[i];

    for (int i = 0; i < days - 1; ++i) {
        for (int j = i + 1; j < days; ++j) {
            if (copy[j] > copy[i]) {
                double temp = copy[i];
                copy[i] = copy[j];
                copy[j] = temp;
            }
        }
    }

    cout << "Топ-3 витрат: ";
    int count = days < 3 ? days : 3;
    for (int i = 0; i < count; ++i) {
        if (i > 0) cout << ", ";
        cout << copy[i];
    }
    cout << " грн\n";
}

int main() {
    double budget;
    if (!readAmount("Бюджет на місяць (грн): ", budget, true)) return 0;

    int days;
    while (true) {
        cout << "Кількість днів обліку (1-31): ";
        if (readInt(days) && days >= 1 && days <= MAX_DAYS) break;
        if (cin.eof()) return 0;
        cout << "Введіть ціле число від 1 до 31.\n";
    }

    double spending[MAX_DAYS];
    for (int i = 0; i < days; ++i) {
        string prompt = "Витрати за день " + to_string(i + 1) + " (грн): ";
        if (!readAmount(prompt, spending[i], false)) return 0;
    }

    cout.setf(ios::fixed);
    cout.precision(2);
    int choice;
menu:
    do {
        cout << "\n1. Показати витрати по днях\n"
             << "2. Статистика витрат\n"
             << "3. Дні з перевищенням денного ліміту\n"
             << "4. Три найдорожчі дні\n"
             << "0. Вихід\n"
             << "Ваш вибір: ";
        if (!readInt(choice) || choice < 0 || choice > 4) {
            if (cin.eof()) return 0;
            cout << "Неправильний пункт меню.\n";
            goto menu;
        }

        switch (choice) {
            case 1:
                showSpending(spending, days);
                break;
            case 2:
                showStatistics(spending, days, budget);
                break;
            case 3: {
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                double limit;
                if (!readDouble(limit) || limit < 0 || limit > MAX_AMOUNT) {
                    if (cin.eof()) return 0;
                    cout << "Некоректний ліміт.\n";
                    goto menu;
                }
                if (limit == 0) showDaysOverLimit(spending, days);
                else showDaysOverLimit(spending, days, limit);
                break;
            }
            case 4:
                showTopThree(spending, days);
                break;
        }
    } while (choice != 0);

    return 0;
}
