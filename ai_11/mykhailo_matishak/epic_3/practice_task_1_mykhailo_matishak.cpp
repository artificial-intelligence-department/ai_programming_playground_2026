/*Задача: Аналізатор місячного бюджету
Автор: Матішак Михайло
Група: ШІ-11*/
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//Рекурсивна функція: рахує суму витрат
float SumOfSpendings(float spending[], int n) {
    if (n == 0) {
        return 0;
    }
    return spending[n - 1] + SumOfSpendings(spending, n - 1);
}

//Таблиця, що показує витрати по днях
void showTable(float spending[], int N) {
    cout << fixed << setprecision(2);
    cout << left << setw(10) << "День" << right << setw(15) << "Витрати, грн" << endl;

    for (int i = 0; i < N; i++) {
        cout << left << setw(10) << i + 1 << right << setw(15) << spending[i] << endl;
    }
    cout << endl;
}
//Знаходить мінімум і максимум
void findMinMax(float spending[], int n, float &minValue, float &maxValue) {
    minValue = spending[0];
    maxValue = spending[0];

    for (int i = 1; i < n; i++) {
        if (spending[i] < minValue) {
            minValue = spending[i];
        }
        if (spending[i] > maxValue) {
            maxValue = spending[i];
        }
    }
}
//Виводить статистику витрат
void showStatistics(float spending[], int N, float budget) {
    float minValue, maxValue;
    findMinMax(spending, N, minValue, maxValue);

    float total = SumOfSpendings(spending, N);
    float remain = budget - total;

    cout << fixed << setprecision(2);
    cout << "Мінімальні витрати за день: " << minValue << " грн" << endl;
    cout << "Максимальні витрати за день: " << maxValue << " грн" << endl;
    cout << "Сумарні витрати: " << total << " грн" << endl;

    if (total > budget) {
        cout << "Перевитрата понад бюджет: " << fabs(remain) << " грн" << endl;
    } else {
        cout << "Залишок бюджету: " << remain << " грн" << endl;
    }

    int daysWithSpending = 0;
    float sumWithSpending = 0;

    for (int i = 0; i < N; i++) {
        if (spending[i] == 0) {
            continue;
        }
        sumWithSpending += spending[i];
        daysWithSpending++;
    }

    cout << "Днів з покупками: " << daysWithSpending << endl;

    if (daysWithSpending > 0) {
        cout << "Середні витрати за день з покупками: " << sumWithSpending / daysWithSpending << " грн" << endl;
    } else {
        cout << "Середні витрати за день з покупками: 0.00 грн" << endl;
    }

    int day = 0;
    float accumulated = 0;
    bool exhausted = false;

//Накопичення витрат по днях
    while (day < N) {
        accumulated += spending[day];
        if (accumulated > budget) {
            exhausted = true;
            break;
        }
        day++;
    }

    if (exhausted) {
        cout << "Бюджет вичерпано на дні " << day + 1 << ", накопичено " << accumulated << " грн." << endl;
    } else {
        cout << "Бюджету вистачило на всі дні." << endl;
    }
}
//Вивід днів, де витрати більші за ліміт
void showOverLimit(float spending[], int N, float limit = 1000) {
    int count = 0;

    cout << fixed << setprecision(2);
    cout << "Ліміт: " << limit << " грн" << endl;

    for (int i = 0; i < N; i++) {
        if (spending[i] > limit) {
            cout << "  день " << i + 1 << ": " << spending[i] << " грн" << endl;
            count++;
        }
    }

    cout << "Разом днів з перевищенням: " << count << endl;
}
//Три найбільші витрати
void showTopThree(float spending[], int N) {
    float copy[31];
    for (int i = 0; i < N; i++) {
        copy[i] = spending[i];
    }
    //Сортування бульбашкою
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (copy[j] > copy[i]) {
                float temp = copy[i];
                copy[i] = copy[j];
                copy[j] = temp;
            }
        }
    }

    int count = N;
    if (count > 3) {
        count = 3;
    }

    cout << fixed << setprecision(2);
    cout << "Топ-" << count << " витрат: ";

    for (int i = 0; i < count; i++) {
        cout << copy[i];
        if (i < count - 1) {
            cout << ", ";
        }
    }
    cout << " грн" << endl;
}

int main() {
    float budget;
    int N;
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    while (cin.fail() || budget < 0) {
        cout << "Помилка: введіть невід'ємне число: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> budget;
    }
//Зчитування кількості днів від 1 до 31
    cout << "Кількість днів обліку: ";
    cin >> N;
    while (cin.fail() || N <= 0 || N > 31) {
        cout << "Помилка: кількість днів має бути від 1 до 31: ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> N;
    }

    float spending[N];
//Зчитуємо витрати за кожен день
    cout << "Витрати за кожен день (грн): ";
    for (int i = 0; i < N; i++) {
        cin >> spending[i];
        while (cin.fail() || spending[i] < 0) {
            cout << "Помилка: витрата має бути невід'ємним числом. Введіть знову: ";
            cin.clear();
            cin.ignore(1000, '\n');
            cin >> spending[i];
        }
    }

    int choice;
//Меню повторюється, поки користувач не веде 0
menu:
    do {
        cout << "Меню:" << endl;
        cout << "1 - Показати витрати по днях" << endl;
        cout << "2 - Статистика витрат" << endl;
        cout << "3 - Дні з перевищенням денного ліміту" << endl;
        cout << "4 - Три найдорожчі дні" << endl;
        cout << "0 - Вийти" << endl;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка: введіть номер пункту." << endl;
            goto menu;
        }

        if (choice < 0 || choice > 4) {
            cout << "Немає такого пункту меню." << endl;
            goto menu;
        }

        switch (choice) {
            case 1:
                showTable(spending, N);
                break;

            case 2:
                showStatistics(spending, N, budget);
                break;

            case 3: {
                float inpLimit;
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                cin >> inpLimit;

                if (cin.fail() || inpLimit < 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Помилка: ліміт має бути невід'ємним числом." << endl;
                    goto menu;
                }

                if (inpLimit == 0) {
                    showOverLimit(spending, N);
                } else {
                    showOverLimit(spending, N, inpLimit);
                }
                break;
            }

            case 4:
                showTopThree(spending, N);
                break;
        }

    } while (choice != 0);

    return 0;
}