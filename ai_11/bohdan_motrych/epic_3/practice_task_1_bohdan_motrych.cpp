#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Ініціалізація констант
const int N_MAX = 31;
const double DEFAULT_LIMIT = 1000.0;

// Виведення витрат по днях
void showSpending(const double a[], int N)  {
    cout << "\nДень        Витрати, грн\n";
    for (int i = 0; i < N; i++)
        cout << setw(4) << i + 1
             << setw(20) << a[i] << "\n";
}

// Знаходження мінімум і максимум
void findMinMax(const double a[], int N, double &min, double &max) {
    min = a[0];
    max = a[0];
    for (int i = 1; i < N; i++) {
        if (a[i] < min) min = a[i];
        if (a[i] > max) max = a[i];
    }
}

// Знаходження суми
double findTotal(const double a[], int N) {
    if (N == 0)
        return 0;
    return a[N - 1] + findTotal(a, N - 1);
}


// Виведення статистики витрат
void showStatistics(const double a[], int N, double budget) {
    double min, max;
    findMinMax(a, N, min, max);
    double sum = findTotal(a, N);
    double remainder = budget - sum;

    cout << "\nМінімальні витрати за день:     " << min << " грн\n";
    cout << "Максимальні витрати за день:    " << max << " грн\n";
    cout << "Сумарні витрати:                " << sum << " грн\n";

    if (remainder < 0)
        cout << "Перевитрата понад бюджет:       " << fabs(remainder) << " грн\n";
    else
        cout << "Залишок бюджету:                " << remainder << " грн\n";

    // Знаходення середнього значення
    double purchaseSum = 0;
    int purchaseDays = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] == 0)
            continue;
        purchaseSum += a[i];
        purchaseDays++;
    }

    cout << "Днів з покупками:               " << purchaseDays << "\n";
    if (purchaseDays > 0)
        cout << "Середні витрати за такий день:  " << purchaseSum / purchaseDays << " грн\n";
    else
        cout << "Середні витрати за такий день:  немає даних (покупок не було)\n";

    // Знаходення днів, коли бюджет було вичерпано
    double acc = 0;
    int day = 0;
    int exhaustedDay = -1;
    while (day < N) {
        acc += a[day];
        if (acc > budget) {
            exhaustedDay = day + 1;
            break;
        }
        day++;
    }
    if (exhaustedDay != -1)
        cout << "Бюджет вичерпано на дні " << exhaustedDay << ", накопичено " << acc << " грн.\n";
    else
        cout << "Бюджету вистачило на всі дні, залишок " << budget - acc << " грн.\n";
}

// Знаходження і виведення перевищення ліміту
void showDaysOverLimit(const double a[], int N, double limit = DEFAULT_LIMIT) {
    cout << "\nЛіміт: " << limit << " грн\n";
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] > limit) {
            cout << "  День " << i + 1 << ": " << a[i] << " грн\n";
            count++;
        }
    }
    if (count == 0)
        cout << "  днів з перевищенням немає\n";
    cout << "Разом днів з перевищенням: " << count << "\n";
}

// Знаходження і виведення трьох найдорожчих днів
void showTopThree(const double a[], int N) {
    double copy[N_MAX];
    for (int i = 0; i < N; i++)
        copy[i] = a[i];

    // Сортування масиву
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (copy[j] < copy[j + 1]) {
                double t = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = t;
            }
        }
    }

    int k = (N < 3) ? N : 3;
    cout << "\nТоп-" << k << " витрат: ";
    for (int i = 0; i < k; i++) {
        cout << copy[i];
        if (i < k - 1)
            cout << ", ";
    }
    cout << " грн\n";
}

// Виведення меню
void printMenu() {
    cout << "\n ===== Аналізатор місячного бюджету =====\n"
         << "1. Показати витрати по днях\n"
         << "2. Статистика витрат\n"
         << "3. Дні з перевищенням денного ліміту\n"
         << "4. Три найдорожчі дні\n"
         << "0. Вийти\n";
}

int main()
{
    cout << fixed << setprecision(2);

    double budget = 0;
    cout << "Бюджет на місяць (грн): ";
    if ((!(cin >> budget)) || budget <= 0){
        cout << "Помилка: бюджет має бути числом більше 0" << endl;
        return 0;
    }

    int N = 0;
    cout << "Кількість днів обліку: ";
    if ((!(cin >> N)) || N <= 0 || N > N_MAX){
        cout << "Помилка: кількість днів має бути числом більше 0 і менше 31" << endl;
        return 0;
    }

    double spending[N_MAX];
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < N; i++) {
        if ((!(cin >> spending[i])) || N < 0){
            cout << "Помилка: витрати мають бути невід'ємними числами" << endl;
            return 0;
        }
    }

    int choice = -1;
    do {
        menu:
            printMenu();
            cout << "Ваш вибір: ";

            switch (choice) {
            case 1:
                showSpending(spending, N);
                break;
            case 2:
                showStatistics(spending, N, budget);
                break;
            case 3: {
                double limit = 1000;
                cout << "Введіть ліміт: \n";
                cin >> limit;
                if (limit == 0)
                    showDaysOverLimit(spending, N);
                else
                    showDaysOverLimit(spending, N, limit);
                break;
            }
            case 4:
                showTopThree(spending, N);
                break;
            case 0:
                cout << "Завершення роботи...\n";
                break;
            default:
                cout << "Помилка: введіть число від 0 до 4.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                goto menu;
                break;
            }
        } while (choice != 0);

    return 0;
}