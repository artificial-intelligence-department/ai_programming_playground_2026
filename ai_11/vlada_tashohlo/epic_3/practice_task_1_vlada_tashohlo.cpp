/*
Епік 3. Практичне завдання: Аналізатор місячного бюджету
Авторка: Ташогло Влада
Група: ші-11
*/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// Константи програми
const int DEFAULT_BUDGET = 1000;
const int MAX_DAYS_PER_MONTH = 31;
const int TOP_DAYS_COUNT = 3;

// Прототипи функцій 
void clearInput();
int parseSpendingLine(const string& line, int* values, int& count, int limit);
void collectSpendingLine(const string& line, int* values, int& count, int dayCount);
bool inputSpending(int* spending, int dayCount);
void output_menu();
void show_spending(int* spending, int N);
void findMinMaxRecursive(int* spending, int N, int& minVal, int& maxVal);
long long getTotalSpending(int* spending, int N);
void getRemainingBudget(int* spending, int N, int budget);
int calculateSpendingStats(int* spending, int N, long long& totalSpending, double& averageSpending);
void show_statistics(int* spending, int N, int budget);
void show_days_exceeding_limit(int* spending, int N, int limit = DEFAULT_BUDGET);
void show_top_three_days(int* spending, int N);

// Головна функція: введення даних, меню та обробка вибраної операції
int main() {
    int budget = 0;
    int dayCount = 0;

    cout << "Бюджет на місяць (грн): ";
    while (!(cin >> budget) || budget < 0) {
        cout << "Бюджет має бути додатним числом" << endl
             << "Бюджет на місяць (грн): ";
        clearInput();
    }

    if (budget == 0) {
        budget = DEFAULT_BUDGET;
    }

    cout << "Кількість днів обліку: ";
    while (!(cin >> dayCount) || dayCount < 1 || dayCount > MAX_DAYS_PER_MONTH) {
        cout << "Кількість днів має бути від 1 до 31" << endl
             << "Кількість днів обліку: ";
        clearInput();
    }

    int* spending = new int[dayCount];
    if (!inputSpending(spending, dayCount)) {
        delete[] spending;
        return 1;
    }

    int action = -1;

    do {
menu:
        output_menu();
        cout << "Введіть номер операції: ";

        if (!(cin >> action)) {
            cout << "Невірний номер операції" << endl;
            clearInput();
            action = -1;
            goto menu;
        }

        switch (action) {
        case 1:
            show_spending(spending, dayCount);
            break;

        case 2:
            show_statistics(spending, dayCount, budget);
            break;

        case 3:
            show_days_exceeding_limit(spending, dayCount);
            break;

        case 4:
            show_top_three_days(spending, dayCount);
            break;

        case 0:
            cout << "Вихід з програми" << endl;
            break;

        default:
            cout << "Невірний номер операції" << endl;
            goto menu;
        }
    } while (action != 0);

    delete[] spending;

    return 0;
}

// Очищення буфера введення після помилки читання
void clearInput() {
    cin.clear();

    char ch = '\0';
    while (cin.get(ch) && ch != '\n') {
    }
}

// Розбиває один рядок на цілі невід'ємні числа і додає їх у масив values.
// count — скільки чисел вже накопичено, limit — місткість масиву.
// Повертає кількість чисел, доданих із цього рядка, або код помилки:
// -1 — у рядку є нечисловий символ, -2 — від'ємне значення,
// -3 — чисел більше, ніж limit.
int parseSpendingLine(const string& line, int* values, int& count, int limit) {
    istringstream stream(line);
    string token;

    while (stream >> token) {
        istringstream number(token);
        int value = 0;

        if (!(number >> value) || number.peek() != EOF) {
            return -1;
        }

        if (value < 0) {
            return -2;
        }

        if (count >= limit) {
            return -3;
        }

        values[count] = value;
        ++count;
    }

    return count;
}

// Розбирає один рядок вводу та перевіряє кількість накопичених значень.
// Менше ніж dayCount — просимо ввести решту, більше — просимо ввести заново.
void collectSpendingLine(const string& line, int* values, int& count, int dayCount) {
    const int before = count;
    const int added = parseSpendingLine(line, values, count, dayCount);

    if (added == -1) {
        count = 0;
        cout << "Витрати мають бути цілими числами. Введіть витрати з самого початку:" << endl;
        return;
    }

    if (added == -2) {
        count = 0;
        cout << "Витрати не можуть бути від'ємними. Введіть витрати з самого початку:" << endl;
        return;
    }

    if (added == -3) {
        count = 0;
        cout << "Введено більше ніж " << dayCount
             << " значень, а днів обліку " << dayCount
             << ". Введіть витрати з самого початку:" << endl;
        return;
    }

    // порожній рядок — просто чекаємо наступний рядок даних
    if (added == before) {
        return;
    }

    if (count < dayCount) {
        cout << "Введено " << count << " з " << dayCount
             << " днів обліку. Введіть решту витрат:" << endl;
    }
}

// Ввід витрат по днях із перевіркою кількості заданих чисел.
// Повертає false, якщо потік введення завершився.
bool inputSpending(int* spending, int dayCount) {
    string line;
    int values[MAX_DAYS_PER_MONTH];
    int count = 0;

    // залишок поточного рядка після кількості днів обліку: користувач
    // міг ввести бюджет, кількість днів і витрати в одному рядку
    if (getline(cin, line)) {
        collectSpendingLine(line, values, count, dayCount);
    }

    while (count != dayCount) {
        cout << "Витрати по днях (грн): ";

        if (!getline(cin, line)) {
            cout << "Витрати не введені. Програма завершується." << endl;
            return false;
        }

        collectSpendingLine(line, values, count, dayCount);
    }

    for (int i = 0; i < dayCount; ++i) {
        spending[i] = values[i];
    }

    return true;
}

// Виведення головного меню користувача
void output_menu() {
    cout << "===== Меню =====" << endl;
    cout << left << setw(8) << "Пункт   " << setw(35) << "Операція" << endl;
    cout << left << setw(8) << "1" << setw(35) << "Показати витрати по днях" << endl;
    cout << left << setw(8) << "2" << setw(35) << "Статистика витрат" << endl;
    cout << left << setw(8) << "3" << setw(35) << "Дні з перевищенням денного ліміту" << endl;
    cout << left << setw(8) << "4" << setw(35) << "Три найдорожчі дні" << endl;
    cout << left << setw(8) << "0" << setw(35) << "Вихід" << endl;
}

// Виведення витрат по кожному дню
void show_spending(int* spending, int N) {
    cout << "===== Витрати по днях (грн) =====" << endl;
    cout << left << setw(8) << "День    " << "Витрати, грн" << endl;

    for (int i = 0; i < N; ++i) {
        cout << left << setw(8) << (i + 1)
             << fixed << setprecision(2) << static_cast<double>(spending[i]) << endl;
    }
}

// Рекурсивний пошук мінімального та максимального значення
void findMinMaxRecursive(int* spending, int N, int& minVal, int& maxVal) {
    if (N == 1) {
        minVal = spending[0];
        maxVal = spending[0];
        return;
    }

    findMinMaxRecursive(spending, N - 1, minVal, maxVal);

    if (spending[N - 1] < minVal) {
        minVal = spending[N - 1];
    }

    if (spending[N - 1] > maxVal) {
        maxVal = spending[N - 1];
    }
}

// Підсумок витрат за всі дні через рекурсію
long long getTotalSpending(int* spending, int N) {
    if (N == 0) {
        return 0;
    }

    return spending[N - 1] + getTotalSpending(spending, N - 1);
}

// Показує, чи бюджет перевищено, і на якому дні це сталося
void getRemainingBudget(int* spending, int N, int budget) {
    long long totalSpending = getTotalSpending(spending, N);

    if (totalSpending > budget) {
        long long over = totalSpending - budget;
        cout << "Перевитрата понад бюджет: "
             << fixed << setprecision(2) << static_cast<double>(over) << " грн" << endl;

        long long cumulativeSpending = 0;
        int i = 0;

        while (i < N) {
            cumulativeSpending += spending[i];

            if (cumulativeSpending > budget) {
                cout << "Бюджет вичерпано на дні " << (i + 1)
                     << ", накопичено " << fixed << setprecision(2)
                     << static_cast<double>(cumulativeSpending) << " грн." << endl;
                break;
            }

            ++i;
        }
    } else {
        long long rest = budget - totalSpending;
        cout << "Залишок бюджету: "
             << fixed << setprecision(2) << static_cast<long double>(rest) << " грн" << endl;
    }
}

// Підрахунок загальних витрат та середніх витрат по днях з покупками
int calculateSpendingStats(int* spending, int N, long long& totalSpending, double& averageSpending) {
    totalSpending = getTotalSpending(spending, N);

    int daysWithShopping = 0;
    int i = 0;

    while (i < N) {
        if (spending[i] == 0) {
            ++i;
            continue;
        }

        ++daysWithShopping;
        ++i;
    }

    averageSpending = (daysWithShopping == 0)
        ? 0.0
        : static_cast<double>(totalSpending) / daysWithShopping;

    return daysWithShopping;
}

// Загальна статистика: мінімум, максимум, сума, залишок бюджету
void show_statistics(int* spending, int N, int budget) {
    int minVal = 0;
    int maxVal = 0;
    findMinMaxRecursive(spending, N, minVal, maxVal);

    long long shoppingTotal = 0;
    double averageSpending = 0.0;
    int daysWithShopping = calculateSpendingStats(spending, N, shoppingTotal, averageSpending);

    cout << "===== Статистика витрат =====" << endl;
    cout << "Мінімальні витрати за день: "
         << fixed << setprecision(2) << static_cast<double>(minVal) << " грн" << endl;
    cout << "Максимальні витрати за день: "
         << fixed << setprecision(2) << static_cast<double>(maxVal) << " грн" << endl;
    cout << "Сумарні витрати: "
         << fixed << setprecision(2) << static_cast<double>(shoppingTotal) << " грн" << endl;
    getRemainingBudget(spending, N, budget);
    cout << "Днів з покупками: " << daysWithShopping << endl;
    cout << "Середні витрати за такий день: "
         << fixed << setprecision(2) << averageSpending << " грн" << endl;
}

// Виведення днів, у які витрати перевищили встановлений ліміт
void show_days_exceeding_limit(int* spending, int N, int limit) {
    int input = 0;
    
    cout << "Денний ліміт (грн, 0 = за замовчуванням): ";

    while (!(cin >> input) || input < 0) {
        cout << "Денний ліміт має бути додатним числом" << endl
             << "Денний ліміт (грн, 0 = за замовчуванням): " ;
        clearInput();
    }

    if (input != 0) {
        limit = input;
    }

    cout << "Ліміт: " << fixed << setprecision(2) << static_cast<double>(limit) << " грн" << endl;

    int count = 0;
    for (int i = 0; i < N; ++i) {
        if (spending[i] > limit) {
            cout << "  день " << (i + 1) << ": "
                 << fixed << setprecision(2) << static_cast<double>(spending[i]) << " грн" << endl;
            ++count;
        }
    }

    cout << "Разом днів з перевищенням: " << count << endl;
}

// Пошук трьох найдорожчих днів за допомогою сортування масиву
void show_top_three_days(int* spending, int N) {
    int* copy = new int[N];
    for (int i = 0; i < N; ++i) {
        copy[i] = spending[i];
    }

    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - 1 - i; ++j) {
            if (copy[j] < copy[j + 1]) {
                int tmp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = tmp;
            }
        }
    }

    cout << "Топ-3 витрат: ";
    int k = (TOP_DAYS_COUNT < N) ? TOP_DAYS_COUNT : N;

    for (int i = 0; i < k; ++i) {
        cout << fixed << setprecision(2) << static_cast<double>(copy[i]);
        if (i + 1 < k) {
            cout << ", ";
        }
    }

    cout << " грн" << endl;

    delete[] copy;
}