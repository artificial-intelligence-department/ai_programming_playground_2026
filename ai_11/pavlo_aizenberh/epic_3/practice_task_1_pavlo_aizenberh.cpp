#include <iostream> 
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

double budget = 0;
int N = 0;
double spending[31] = {0};

// сумарні витрати обчислити рекурсивною функцією, без циклу
double calculateTotalRecursive(const double spending[], int N, int index) {
    if (index >= N) return 0.0;
    return spending[index] + calculateTotalRecursive(spending, N, index + 1);
}

// еовернути мінімум і максимум через параметри-посилання (&)
void minmax(double &minVal, double &maxVal) {
    if (N <= 0) return;
    minVal = spending[0];
    maxVal = spending[0];
    for (int i = 1; i < N; i++) {
        if (spending[i] < minVal) minVal = spending[i];
        if (spending[i] > maxVal) maxVal = spending[i];
    } 
}

// вивести список витрат по днях
void table() {
    cout << "\nДень     Витрати, грн" << endl;
    for (int i = 0; i < N; i++) {
        cout << setw(4) << i + 1 << "       " 
             << right << setw(10) << fixed << setprecision(2) << spending[i] << endl;
    }
}

// статистика витрат
void statistics() {
    double minVal = 0, maxVal = 0;
    minmax(minVal, maxVal); 

    double sum = calculateTotalRecursive(spending, N, 0); // виклик рекурсивної функції

    // накопичувати витрати і вийти одразу при перевищенні
    double accumulated = 0;
    int dayExceeded = -1;
    int i = 0;
    while (i < N) {
        accumulated += spending[i];
        if (accumulated > budget) {
            dayExceeded = i + 1; // номер дня (з 1)
            break;
        }
        i++;
    }

    // пропускати дні без покупок при обчисленні середніх витрат
    int notnull = 0;
    double sumNonNull = 0;
    for (int j = 0; j < N; j++) {
        if (spending[j] == 0) {
            continue;   
        }
        notnull++;
        sumNonNull += spending[j];
    }

    double av = (notnull > 0) ? (sumNonNull / notnull) : 0.0;

    cout << fixed << setprecision(2) << endl;
    cout << left << setw(31) << "Мінімальні витрати за день:" 
         << right << setw(9) << minVal << " грн" << endl;
    cout << left << setw(31) << "Максимальні витрати за день:" 
         << right << setw(9) << maxVal << " грн" << endl;
    cout << left << setw(31) << "Сумарні витрати:" 
         << right << setw(9) << sum << " грн" << endl;

    // використовуємо функцію з бібліотеки cmath, fabs(), для модуля перевитрати
    if (sum > budget) {
        cout << left << setw(31) << "Перевитрата понад бюджет:" 
             << right << setw(9) << fabs(sum - budget) << " грн" << endl;
    } else {
        cout << left << setw(31) << "Залишок бюджету:" 
             << right << setw(9) << (budget - sum) << " грн" << endl;
    }

    cout << left << setw(31) << "Днів з покупками:" 
         << right << setw(9) << notnull << endl;
    cout << left << setw(31) << "Середні витрати за такий день:" 
         << right << setw(9) << av << " грн" << endl;

    if (dayExceeded != -1) {
        cout << "Бюджет вичерпано на дні " << dayExceeded << ", накопичено " 
             << accumulated << " грн." << endl;
    } else {
        cout << "Бюджету вистачило на всі дні. Залишок: " 
             << (budget - sum) << " грн." << endl;
    }
}

// параметр за замовчуванням (limit = 1000)
void exceeding(double limit = 1000) {
    cout << "Ліміт: " << fixed << setprecision(2) << limit << " грн" << endl;
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (spending[i] > limit) {
            count++;
            cout << "  день " << i + 1 << ": " 
                 << fixed << setprecision(2) << spending[i] << " грн" << endl;    
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}   

// сортування копії масиву за спаданням
void top() {
    double tempSpending[31];
    for (int i = 0; i < N; i++) {
        tempSpending[i] = spending[i]; // зберігаємо початковий масив незмінним
    }

    // сортування бульбашкою
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (tempSpending[j] < tempSpending[j + 1]) {
                double temp = tempSpending[j];
                tempSpending[j] = tempSpending[j + 1];
                tempSpending[j + 1] = temp; 
            }
        }
    }

    cout << "Топ-3 витрат: ";
    int count = (N < 3) ? N : 3;
    for (int i = 0; i < count; i++) {
        cout << fixed << setprecision(2) << tempSpending[i];
        if (i < count - 1) cout << ", ";
    }
    cout << " грн" << endl;
}

int main() {
    // валідація вхідних даних
    cout << "Бюджет на місяць (грн): ";
    while (!(cin >> budget) || budget < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Помилка! Введіть дійсне число >= 0: ";
    }

    cout << "Кількість днів обліку: ";
    while (!(cin >> N) || N <= 0 || N > 31) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Помилка! Введіть кількість днів (від 1 до 31): ";
    }

    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < N; i++) {
        while (!(cin >> spending[i]) || spending[i] < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некоректне значення для дня " << i + 1 << "! Введіть число >= 0: ";
        }
    }

    int choice;
    //do-while конструкція - тіло do виконується, допоки while залишається істинним
    do {
menu: //  goto мітка
        cout << "\n==========================================================" << endl;
        cout << "Пункт    Операція" << endl;
        cout << "1        Показати витрати по днях" << endl;
        cout << "2        Статистика витрат" << endl;
        cout << "3        Дні з перевищенням денного ліміту" << endl;
        cout << "4        Три найдорожчі дні" << endl;
        cout << "0        Вийти" << endl;
        cout << "==========================================================" << endl;
        cout << "Виберіть пункт: ";

        // обробка помилкового вводу пункту меню
        if (!(cin >> choice) || choice < 0 || choice > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nНекоректний пункт меню! Спробуйте ще раз." << endl;
            goto menu;
        }

        switch (choice) {
            case 1:
                table();
                break;

            case 2:
                statistics();
                break;

            case 3: {
                double inputLimit;
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                while (!(cin >> inputLimit) || inputLimit < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Введіть число >= 0: ";
                }
                 
                // якщо введено 0 — викликаємо без аргументу ( спрацьовує limit = 1000 )
                if (inputLimit == 0) {
                    exceeding();
                } else {
                    exceeding(inputLimit);
                }
                break;
            }

            case 4:
                top();
                break;

            case 0:
                break;
        }
    } while (choice != 0);

    return 0;
}