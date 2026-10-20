#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// 1. Рекурсивна функція для обчислення сумарних витрат (без циклів)
double calculateTotal(const double spending[], int N) {
    if (N <= 0) return 0.0;
    return spending[N - 1] + calculateTotal(spending, N - 1);
}

// 2. Функція знаходження мінімуму та максимуму (параметри-посилання)
void findMinMax(const double spending[], int N, double &minVal, double &maxVal) {
    if (N <= 0) return;
    minVal = spending[0];
    maxVal = spending[0];
    for (int i = 1; i < N; ++i) {
        if (spending[i] < minVal) minVal = spending[i];
        if (spending[i] > maxVal) maxVal = spending[i];
    }
}

// 3. Функція для виведення середніх витрат (без врахування днів по 0 грн)
void showAverageSpending(const double spending[], int N) {
    double total = 0.0;
    int count = 0;
    for (int i = 0; i < N; ++i) {
        if (spending[i] <= 0) continue; // Пропускаємо дні з витратами <= 0
        total += spending[i];
        count++;
    }

    double average = total / count;
    cout << "\nСередні витрати за " << count << " днів: " << average << " грн" << endl;

}

// Пункт 1 меню: Показати витрати по днях
void showDailySpending(const double spending[], int N) {
    cout << "\n--- Витрати по днях ---" << endl;
    cout << "День       " << "Витрати, грн" << endl;
    cout << fixed;

    for (int i = 0; i < N; ++i) {
        cout << (i + 1) << "          " << spending[i] << endl;
    }
}


// Пункт 2 меню: Статистика витрат
void showStatistics(const double spending[], int N, double budget) {

    double minVal; 
    double maxVal;
    findMinMax(spending, N, minVal, maxVal);

    cout << "\n--- Статистика витрат ---" << endl;

    cout << "Мінімальні витрати: " << minVal << " грн" << endl;
    cout << "максима льні витрати: " << maxVal << " грн" << endl;


    double total = calculateTotal(spending, N);
    cout << "Загальні витрати: " << total << " грн" << endl;

    double remaining = budget - total;
    if (remaining >= 0) {
        cout << "Залишок бюджету: " << remaining << " грн" << endl;
    } else {
        cout << "Перевищення бюджету на: " << -remaining << " грн" << endl;
    }
    
    showAverageSpending(spending, N);

    // День, коли бюджет вичерпано.
    int count = 0;
    double spended = 0;
    while (count < N) {
        
        spended += spending[count];
        if (spended > budget) {
            cout << "Бюджет вичерпано на день " << (count + 1) << " залишок: " << spended << " грн" << endl;
            break;
        }
        count++;
    }
    if (spended <= budget) {
        cout << "Залишок бюджету: " << (budget - spended) << " грн" << endl;
    }
    
}

// Пункт 3 меню: денний ліміт
void showDailyLimit(const double spending[], int N, double budget, double dailyLimit = 0) {
    cout << "\n--- Денний ліміт витрат ---" << endl;
     
    if (dailyLimit == 0) dailyLimit = 1000;
    cout << "Денний ліміт: " << dailyLimit << " грн" << endl;
    int count = 0;
    for (int i = 0; i < N; ++i) {
        if (spending[i] > dailyLimit) {
            cout << "День " << (i + 1) << ": " << spending[i] << " грн" << endl;
            count++;
        }
        
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}

// Пункт 4 меню: топ-3 днів з найбільшими витратами
void showTop3SpendingDays(const double spending[], int N) {
    cout << "\n--- Топ-3 днів з найбільшими витратами ---" << endl;
    double top3[31];
    for(int i = 0; i < 31; ++i) {
        top3[i] = spending[i]; 
    }

    double temp;
    for (int i = 0; i < N-1; ++i) {
        for (int j = 0; j < N-i-1; ++j) {
            if (top3[j] < top3[j+1]) {
                temp = top3[j];
                top3[j] = top3[j+1];
                top3[j+1] = temp;
            }
        }
    }
    
    int count = (N < 3) ? N : 3;
    cout << "Топ-" << count << " витрат: ";
    for (int i = 0; i < count; ++i) {
        cout << " " << top3[i] << ", ";
    }
    cout << "грн" << endl;
}            
int main()
{
    double budget = 0.0;
    int N = 0;
    double spending[31];
    int choice;
    double dailyLimit = 0;

    while (true) {
        cout << "Бюджет на місяць (грн): ";
        if (cin >> budget && budget >= 0) break;
        cin.clear();
		cin.ignore(10000, '\n');
        cout << "Помилка! Введіть коректну додатну суму бюджету." << endl;
    }

    // Валідація кількості днів
    while (true) {
        cout << "Кількість днів обліку (1..31): ";
        if (cin >> N && N >= 1 && N <= 31) break;
        cin.clear();
		cin.ignore(10000, '\n');
        cout << "Помилка! Кількість днів має бути цілим числом від 1 до 31." << endl;
    }

    // Введення витрат
    cout << "Витрати по днях (грн, " << N << " чисел): ";
    for (int i = 0; i < N; ++i) {

        while (!(cin >> spending[i]) || spending[i] < 0) {
            cout << "Помилка вводу для дня " << (i + 1) << "! Введіть число > 0: ";
            cin.clear();
		    cin.ignore(10000, '\n');
        }
    }

    
    do {
MENU_LABEL: // Мітка для goto
        cout << "\n--- Меню ---" << endl;
        cout << "1. Показати витрати по днях" << endl;
        cout << "2. Статистика витрат" << endl;
        cout << "3. Денний ліміт витрат" << endl;
        cout << "4. Топ-3 днів з найбільшими витратами" << endl;
        cout << "5. Вийти" << endl;
        cout << "Виберіть пункт меню: ";
        cin >> choice;

        switch (choice) {
            case 1:
                showDailySpending(spending, N);
                break;
            case 2:
                showStatistics(spending, N, budget);
                break;
            case 3:

                cout << "Ведіть денний ліміт (грн, 0 = за замовчуванням): " << endl;
                if (!(cin >> dailyLimit) || dailyLimit < 0) {
                    cin.clear();
		            cin.ignore(10000, '\n');
                    cout << "Некоректний ліміт, повернення в меню..." << endl;
                    goto MENU_LABEL;
                } 
                showDailyLimit(spending, N, budget, dailyLimit);
                break;
            case 4:
                showTop3SpendingDays(spending, N);
                break;
            case 5:
                cout << "Вихід з програми." << endl;
                break;
            default:
                cout << "Помилка! Введіть коректний пункт меню." << endl;
                cin.clear();
		        cin.ignore(10000, '\n');
                goto MENU_LABEL; 
        }
        
    } while (choice != 5);
    
    return 0;
}