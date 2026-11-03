#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// 2.Статистика витрат(Рекурсивна функція для обчислення сумарних витрат)
double calcTotal(const double spending[], int N) {
    if (N <= 0) return 0.0;
    return spending[N - 1] + calcTotal(spending, N - 1);
}

// 2.Статистика витрат(функція знаходження мінімуму та максимуму)
void findMinMax(const double spending[], int N, double &minVal, double &maxVal) {
    if (N <= 0) return;
    minVal = spending[0];
    maxVal = spending[0];
    for (int i = 1; i < N; ++i) {
        if (spending[i] < minVal) minVal = spending[i];
        if (spending[i] > maxVal) maxVal = spending[i];
    }
}

// 2.Статистика витрат(функція для виведення середніх витрат (без врахування днів по 0 грн))
void showAvgSpnd(const double spending[], int N) {
    double total = 0.0;
    int count = 0;
    for (int i = 0; i < N; ++i) {
        if (spending[i] <= 0) continue; // Пропускаємо дні без покупок
        total += spending[i];
        count++;
    }
    if (count > 0) {
        double average = total / count;
        cout << "Днів з покупками: " << count << endl;
        cout << "Середні витрати за такий день: " << fixed << setprecision(2) << average << " грн" << endl;
    } else {
        cout << "Днів з покупками: 0" << endl;
        cout << "Середні витрати за такий день: 0.00 грн" << endl;
    }
}
// 1.Показати витрати по днях
void showDailySpnd(const double spending[], int N) {
    cout << "===Витрати по днях===" << endl;
    cout << "День \t Витрати, грн" << endl;
    for (int i = 0; i < N; ++i) {
        cout << (i + 1) << "\t"<< spending[i] << endl;
    }
}
// 2.Статистика витрат
void showStat(const double spending[], int N, double budget) {
    double minVal, maxVal;
    findMinMax(spending, N, minVal, maxVal);
    cout << "===Статистика витрат===" << endl;
    cout << "Мінімальні витрати за день: " << minVal << " грн" << endl;
    cout << "Максимальні витрати за день: " << maxVal << " грн" << endl;
    double total = calcTotal(spending, N);
    cout << "Сумарні витрати: " << total << " грн" << endl;
    double remaining=budget-total;
    if (remaining >= 0) {
        cout << "Залишок бюджету: " << remaining << " грн" << endl;
    } else {
        cout << "Перевитрата понад бюджет: " << abs(remaining) << " грн" << endl;
    }
    showAvgSpnd(spending, N);
    // 2.Статистика витрат (день, коли бюджет вичерпано)
    int count = 0;
    double potrach = 0;
    bool exhausted = false;
    while (count < N) {
        potrach += spending[count];
        if (potrach > budget) {
            cout << "Бюджет вичерпано на дні " << (count + 1) 
                 << ", накопичено " << potrach << " грн." << endl;
            exhausted = true;
            break;
        }
        count++;
    }
    if (!exhausted) {
        cout << "Бюджету вистачило на всі дні. Залишок: " << remaining << " грн." << endl;
    }
}
// 3.Дні щ перевищенням денного ліміту
void showDailyLim(const double spending[], int N, double dailyLim = 1000.0) {
    if (dailyLim == 0) dailyLim = 1000.00;
    cout << "===Денний ліміт витрат===" << endl;
    cout << "Ліміт: " << fixed << setprecision(2) << dailyLim << " грн" << endl;   
    int count = 0;
    for (int i = 0; i < N; ++i) {
        if (spending[i] > dailyLim) {
            cout << "день " << (i + 1) << ": " << spending[i] << " грн" << endl;
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}
// 4.Три найдорожчі дні
void showTop3Spnd(const double spending[], int N) {
    cout << "===Топ-3 днів з найбільшими витратами===" << endl;
    double top3[31];
    for (int i = 0; i < N; ++i) {
        top3[i] = spending[i];
    }
    // Бабл сорт
    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - i - 1; ++j) {
            if (top3[j] < top3[j + 1]) {
                double temp = top3[j];
                top3[j] = top3[j + 1];
                top3[j + 1] = temp;
            }
        }
    }
    // Виведення
    int count = (N < 3) ? N : 3;
    cout << "Топ-" << count << " витрат: ";
    for (int i = 0; i < count; ++i) {
        cout << top3[i] << " грн";
        if (i < count - 1) cout << ", ";
    }
    cout << endl;
}
int main() {
    double budget = 0.0;
    int N = 0;
    double spending[31];
    int choice;
    double dailyLimit = 0;
    cout << fixed << setprecision(2);
    // Валідація бюджету
    while (true) {
        cout << "Бюджет на місяць (грн): ";
        if (cin >> budget && budget >= 0) break;
        cout << "Помилка! Введіть коректну додатну суму бюджету." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
    // Валідація кількості днів
    while (true) {
        cout << "Кількість днів обліку (1..31): ";
        if (cin >> N && N >= 1 && N <= 31) break;
        cout << "Помилка! Кількість днів має бути цілим числом від 1 до 31." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
    // Введення витрат
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < N; ++i) {
        while (!(cin >> spending[i]) || spending[i] < 0) {
            cout << "Помилка вводу для дня " << (i + 1) << "! Введіть число >= 0: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
    do {
menu: // Мітка для goto
        cout << endl << "--- Меню ---" << endl;
        cout << "1. Показати витрати по днях" << endl;
        cout << "2. Статистика витрат" << endl;
        cout << "3. Дні з перевищенням денного ліміту" << endl;
        cout << "4. Три найдорожчі дні" << endl;
        cout << "0. Вийти" << endl;
        cout << "Виберіть пункт меню: ";
        if (!(cin >> choice)) {
            cout << endl <<"Помилка! Введено некоректний символ. Перенаправлення в меню..." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            goto menu;
        }
        switch (choice) {
            case 1:
                showDailySpnd(spending, N);
                break;
            case 2:
                showStat(spending, N, budget);
                break;
            case 3:
                cout << "Введіть денний ліміт (грн): ";
                if (!(cin >> dailyLimit) || dailyLimit < 0) {
                    cout << "Некоректний ліміт, повернення в меню..." << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    goto menu;
                }
                showDailyLim(spending, N, dailyLimit);
                break;
            case 4:
                showTop3Spnd(spending, N);
                break;
            case 0:
                cout << "Вихід з програми." << endl;
                break;
            default:
                cout << "Помилка! Введіть коректний пункт меню." << endl;
                goto menu;
        }
    } while (choice != 0);
    return 0;
}