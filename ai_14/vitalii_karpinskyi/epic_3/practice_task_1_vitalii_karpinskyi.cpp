/*
Аналізатор місячного бюджету
Карпінський Віталій
СШІ-14
*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
// Пункт 1, вивід витрат по днях
void choice_1(const double spending[], int N) {
    cout << fixed << setprecision(2);
    cout << "\nДень    Витрати, грн" << endl;
    for(int i = 0; i < N; i++) {
        cout << "   " << i + 1 << "    " << spending[i] << endl;
    }
}
// Мін, Макс значення повертаються через параметр-посилання
void MinMax(const double spending[], int N, double &min, double &max) {
    min = spending[0];
    max = spending[0];
    for(int i = 1; i < N; i++) {
        if (spending[i] < min) {
            min = spending[i];
        }
        if (spending[i] > max) {
            max = spending[i];
        }
    }
}
// Всього витрат рекурсивою функцією
double totalSpendings(const double spending[], int N) {
    if(N <= 0) {
        return 0;
    }
    return spending[N - 1] + totalSpendings(spending, N - 1);
}
// Обчислення залишку бюджету
double budgetLeft(double budget, double total) {
    return budget - total;
}

// Обчислення середніх витрат лише для днів з витратами
double averageSpendings(const double spending[], int N, int &days) {
    double sum = 0;
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (spending[i] == 0) {
            continue;
        }
        sum += spending[i];
        count++;
    }
    if (count == 0) {
        return 0;
    }
    days = count;
    return sum / count;
}
// Перевірка коли бюджет вичерпано
void enoughBudget(const double spending[], int N, double budget) {
    double summa = 0;
    int i = 0;
    while (i < N) {
        summa += spending[i];
        if (summa > budget) {
            break;
        }
        i++;
    cout << fixed << setprecision(2);
    }
    if (summa > budget) {
        cout << "Бюджет вичерпано на дні " << i + 1 << ", накопичено " << summa << " грн" << endl;
    } else {
        cout << fixed << setprecision(2);
        cout << "Бюджету вистачило на всі дні, залишок: " << budget - summa << " грн" << endl;
    }
    
}
// Пункт 2, статистика витрат
void choice_2(const double spending[], int N, double budget) {
    double min = 0;
    double max = 0;
    int days = 0;
    MinMax(spending, N, min, max);

    double total = totalSpendings(spending, N);

    double remains = budgetLeft(budget, total);

    double average = averageSpendings(spending, N, days);

    cout << fixed << setprecision(2);
    cout << "Мінімальні витрати за день:    " << min << " грн" << endl;
    cout << "Максимальні витрати за день:   " << max << " грн" << endl;
    cout << "Сумарні витрати:               " << total << " грн" << endl;
    if(remains < 0) {
        cout << "Перевитрата понад бюджет:      " << fabs(remains) << " грн" << endl;
    } else {
        cout << "Залишок бюджету: " << remains << " грн" << endl;
    }

    cout << "Днів з покупками:              " << days << endl;

    cout << "Середні витрати за такий день: " << average << " грн" << endl;
    enoughBudget(spending, N, budget);
}
// Пункт 3, дні з перевищенням ліміту
void choice_3(const double spending[], int N, double limit = 1000.0) {
    int count = 0;
    cout << fixed << setprecision(2);
    cout << "Ліміт: " << limit << " грн" << endl;
    for (int i = 0; i < N; i++) {
        if(spending[i] > limit) {
            cout << "    День " << i + 1 << ": " << spending[i] << " грн" << endl; 
            count++;
        }
    }
cout << "Разом днів з перевищенням: " << count << endl;
}
// Пункт 4, 3 найдорожчі дні
void choice_4(const double spending[], int N) {
    double copy[32];
    for (int i = 0; i < N; i++) {
        copy[i] = spending[i];
    }
    // Сортування бульбашкою
    for (int i = 0; i < N - 1; i++){
        for (int j = 0; j < N - 1 - i; j++){
            if (copy[j] < copy[j + 1]) {
                double swap = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = swap;
            }
        }
    }
    int count = 3;
    if (N < 3) {
        count = N;
    }
    cout << "Топ-3 витрат: ";
    for (int i = 0; i < count; i++) {
        cout << copy[i];
        if (i < count - 1) {
            cout << ", ";
        }
    }
    cout << " грн" << endl;
}

int main() {
    // Введення та валідація даних
    double budget = 0;
    cout << "Введіть свій бюджет на місяць (грн): ";
    cin >> budget;
    if (cin.fail() || budget < 0) {
        cout << "Помилка: невірно введений бюджет" << endl;
        return 0;
    }

    int N = 0;
    cout << "Введіть кількість днів обліку: ";
    cin >> N;
    if (cin.fail() || N <= 0 || N > 31) {
        cout << "Помилка: невірно введені дані" << endl;
        return 0;
    }

    double spending[32] = {0};
    cout << "Введіть витрати за кожен день (грн): ";
    for (int i = 0; i < N; i++ ) {
        cin >> spending[i];

        if (cin.fail() || spending[i] < 0) {
        cout << "Помилка: невірно введені дані" << endl;
        return 0;
        }
    }
    short choice;
    cin.ignore(10000, '\n');
    double limit = 0;
    // Цикл do while для повторення меню
    do {
        choices: // Мітка go to
        cout << "\n======Меню======" << endl;
        cout << "1   Показати витрати по днях" << endl;
        cout << "2   Статистика витрат" << endl;
        cout << "3   Дні з перевищенням денного ліміту" << endl;
        cout << "4   Три найдорожчі дні" << endl;
        cout << "0   Вийти" << endl;
        cout << "Виберіть пункт: ";

        cin >> choice;
        if (cin.fail()) {
        cout << "Помилка: невірно введені дані\n" << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto choices;
        }
        cout << '\n';
        switch (choice) {
            case 1:
                choice_1(spending, N);
                break;
            case 2:
                choice_2(spending, N, budget);
                break;
            case 3:
                cout << "Введіть денний ліміт (грн, 0 = за замовчуванням): ";
                cin >> limit;
                if(cin.fail() || limit < 0) {
                    cout << "Некоректний ввід\n" << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    goto choices;
                }
                // Перевірка на значення за замовчуванням
                if (limit == 0) {
                    choice_3(spending, N);
                } else {
                    choice_3(spending, N, limit);
                }
                break;
            case 4:
                choice_4(spending, N);
                break;
            case 0:
                cout << "Завершення роботи" << endl;
                break;
            default:
                cout << "Помилка: невідомий пункт\n" << endl;
                goto choices;
                
        }
    } while(choice != 0);
    
    return 0;
}