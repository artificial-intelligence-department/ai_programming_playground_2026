/*
Назва: Class Pratice Work
Автор: Макух Арсеній
Група: ШІ-13
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void menu () {
    cout << "\nМеню:\n"
    << "1 - Показати витрати по днях\n"
    << "2 - Статистика витрат\n"
    << "3 - Дні з перевищенням денного ліміту\n"
    << "4 - Три найдорожчі дні\n"
    << "0 - Вийти" << endl;
}

void findMinMax(double spending[], int n, double &min_spent, double &max_spent) {
    min_spent = spending[0];
    max_spent = spending[0];

    for (int i = 1; i < n; i++) {
        if (spending[i] < min_spent) {
            min_spent = spending[i];
        }

        if (spending[i] > max_spent) {
            max_spent = spending[i];
        }
    }
}

void showSpendingByDays(double spending[], int n) {
    cout << "\n" << setw(9) << "День " << setw(18) << "Витрати, грн" << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(4) << (i + 1) << setw(14) << spending[i] << endl;
    }
}

double totalSpending(double spending[], int n) {
    if (n == 0)
        return 0;

    return spending[n - 1] + totalSpending(spending, n - 1);
}

void spendingStats(double budget, double spending[], int n) {
    double min_spent, max_spent;
    findMinMax(spending, n, min_spent, max_spent);

    double total_spent = totalSpending(spending, n), remainder = budget - total_spent, shopping_total = 0;
    int days_of_shopping = 0;

    for (int i = 1; i < n; i++) {
        if (spending[i] < min_spent) {
            min_spent = spending[i];
        }
        shopping_total += spending[i];
        days_of_shopping++;
    }

    double avg_spent = 0;
    if (days_of_shopping > 0) {
        avg_spent = shopping_total / days_of_shopping;
    }

    int i = 0, overlimited_day;
    bool budget_exceeded = false;
    double saved = 0;

    while (i < n) {
        saved += spending[i];

        if (saved > budget) {
            overlimited_day = i + 1;
            budget_exceeded = true;
            break;
        }

        i++;
    }

    cout << "\nМінімальні витрати за день: " << min_spent << " грн" << endl;
    cout << "Максимальні витрати за день: " << max_spent << " грн" << endl;
    cout << "Сумарні витрати: " << total_spent << " грн" << endl;

    if (remainder < 0) {
        cout << "Перевитрата понад бюджет: " << abs(remainder) << " грн" << endl;
    } else {
        cout << "Залишок бюджету: " << remainder << " грн" << endl;
    }

    cout << "Днів з покупками: " << days_of_shopping << endl;
    cout << "Середні витрати за такий день: " << avg_spent << " грн" << endl;

    if (budget_exceeded) {
        cout << "Бюджет вичерпано на дні " << overlimited_day << ", накопичено " << saved << " грн." << endl;
    } else {
        cout << "Бюджету вистачило на всі дні. Залишок: " << budget - saved << " грн." << endl;
    }
}

void overlimitDays (double spending[], int n, int day_limit = 1000) {
    int total_overlimited_days = 0;
    cout << "\nДенний ліміт (грн, 0 = за замовчуванням): ";
    cin >> day_limit;

    if (day_limit == 0) {
        day_limit = 1000;
    }

    cout << "Ліміт: " << day_limit << " грн" << endl;

    for (int i = 0; i < n; i++) {
        if (spending[i] > day_limit) {
            total_overlimited_days++;
            cout << "   день " << (i + 1) << ": " << spending[i] << " грн" << endl;
        }
    }

    cout << "Разом днів з перевищенням: " << total_overlimited_days << endl;
}

void mostExpensiveDays (double spending[], int n) {
    double sorted_spending[n], temp;

    for(int i = 0; i < n; i++) {
        sorted_spending[i] = spending[i];
    }

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n - 1; k++) {
            if (sorted_spending[k] < sorted_spending[k + 1]) {
                temp = sorted_spending[k + 1];
                sorted_spending[k + 1] = sorted_spending[k];
                sorted_spending[k] = temp;
            }
        }
    }

    cout << "\nТоп-3 витрат: " << sorted_spending[0] << ", " << sorted_spending[1] << ", " << sorted_spending[2] << " грн" << endl;
}

int main() {
    int budget = 0, n = 0;
    int menu_choice;

    cout << fixed << setprecision(2);

    cout << "Бюджет на місяць, грн: ";
    cin >> budget;

    cout << "Кількість днів обліку: ";
    cin >> n;
    double spending[n];

    cout << "Витрати по днях, грн: ";
    for (int i = 0; i < n; i++) {
        cin >> spending[i];
    }

    do {
        home:
            menu();
            string input;
            getline(cin >> ws, input);

            if (input.length() != 1 ||
                input[0] < '0' || input[0] > '4') {
                cout << "Некоректний ввід!" << endl;
                goto home;
            }

            menu_choice = input[0] - '0';

            switch(menu_choice) {
                case 1:
                    showSpendingByDays(spending, n);
                    break;
                case 2:
                    spendingStats(budget, spending, n);
                    break;
                case 3:
                    overlimitDays(spending, n);
                    break;
                case 4:
                    mostExpensiveDays(spending, n);
                    break;
                case 0:
                    cout << "Ви вийшли." << endl;
                    return 0;
                default:
                    goto home;
                    cout << "\nНеправильний пункт меню." << endl;
                    break;
            }
    } while (menu_choice != 0);

    return 0;
}