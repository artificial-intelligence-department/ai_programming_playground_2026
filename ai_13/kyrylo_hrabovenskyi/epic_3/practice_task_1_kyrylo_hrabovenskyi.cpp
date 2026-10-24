#include <iostream>

using namespace std;

// Прототипи функцій згідно з вимогами ТЗ
void showSpending(const int spending[], int N);
void getMinMax(const int spending[], int N, double& minRef, double& maxRef);
double getSumRecursive(const int spending[], int N);
void showStatistics(const int spending[], int N, int budget);
void checkDailyLimit(const int spending[], int N, double limit = 1000.0); // Параметр за замовчуванням
void showTopThree(const int spending[], int N);

int main()
{
    const int max_days = 31;
    link1:
    int budget;
    cout << "enter monthly budget (UAH):\n";
    if (!(cin >> budget) || budget < 0) {
        cout << "ohhhh (invalid budget)\n";
        goto link1;
    }
    link2:
    int N;
    cout << "enter tracking period (days):\n";
    if (!(cin >> N) || N <= 0 || N > max_days) {
        cout << "are you the Flash. Your girlfriend said that you are\n";
        goto link2;
    }

    int spending[max_days];
    cout << "daily expenses (UAH):\n";
    for (int i = 0; i < N; i++) {
        if (!(cin >> spending[i]) || spending[i] < 0) {
            cout << "Invalid spending value! Setting to 0.\n";
            spending[i] = 0;
        }
    }

    int choice;

    // Цикл do-while повертає користувача в меню, поки він не вибере 0
    do {
        // Мітка для оператора goto у випадку помилки введення літер/символів
    menu_start:
        cout << "\n========== MENU ==========\n";
        cout << "1. Show daily expenses\n";
        cout << "2. Expense statistics\n";
        cout << "3. Days exceeding daily limit\n";
        cout << "4. Top 3 most expensive days\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        // Валідація нечислових символів за допомогою goto
        if (!(cin >> choice)) {
            cout << "Error: Invalid menu item! Please enter a number.\n";
            cin.clear(); // Скидаємо прапорець помилки cin
            while (cin.get() != '\n'); // Очищаємо буфер введення
            goto menu_start; // Перенаправлення назад до меню
        }

        switch (choice) {
        case 1:
            showSpending(spending, N);
            break;
        case 2:
            showStatistics(spending, N, budget);
            break;
        case 3: {
            double userLimit;
            cout << "Enter daily limit (UAH, 0 = default 1000): ";
            cin >> userLimit;
            if (userLimit <= 0) {
                checkDailyLimit(spending, N); // Виклик без параметра (спрацює 1000)
            }
            else {
                checkDailyLimit(spending, N, userLimit); // Виклик із параметром користувача
            }
            break;
        }
        case 4:
            showTopThree(spending, N);
            break;
        case 0:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
            goto menu_start; // Використання goto для невалідного пункту
        }
    } while (choice != 0);

    return 0;
}

// 1. ПОКАЗАТИ ВИТРАТИ ПО ДНЯХ (Використовує цикл for для обходу масиву)
void showSpending(const int spending[], int N) {
    cout << "\nDay\tSpending, UAH\n";
    for (int i = 0; i < N; i++) {
        cout << i + 1 << "\t" << spending[i] << ".00\n";
    }
}

// 2а. ПАРАМЕТРИ-ПОСИЛАННЯ: Функція повертає min та max через оператори &
void getMinMax(const int spending[], int N, double& minRef, double& maxRef) {
    minRef = spending[0];
    maxRef = spending[0];
    for (int i = 1; i < N; i++) {
        if (spending[i] > maxRef) maxRef = spending[i];
        if (spending[i] < minRef) minRef = spending[i];
    }
}

// 2б. РЕКУРСІЯ: Обчислення суми витрат рекурсивним шляхом (без циклів)
double getSumRecursive(const int spending[], int N) {
    if (N <= 0) return 0;
    return spending[N - 1] + getSumRecursive(spending, N - 1);
}

// 2в. СТАТИСТИКА ВИТРАТ (Головна функція аналітики)
void showStatistics(const int spending[], int N, int budget) {
    double min_val, max_val;
    getMinMax(spending, N, min_val, max_val);
    double total_score = getSumRecursive(spending, N);

    cout << "\nMinimal daily expenses: " << min_val << ".00 UAH\n";
    cout << "Maximal daily expenses: " << max_val << ".00 UAH\n";
    cout << "Total expenses: " << total_score << ".00 UAH\n";

    // Обчислення залишку або перевитрати БЕЗ сторонніх бібліотек
    double budget_left = budget - total_score;
    if (budget_left >= 0) {
        cout << "Budget left: " << budget_left << ".00 UAH\n";
    }
    else {
        // Заміна cmath abs: просто міняємо знак за допомогою унарного мінуса (-)
        double overrun = -budget_left;
        cout << "Budget overrun (deficit): " << overrun << ".00 UAH\n";
    }

    // Середні витрати за дні з покупками (Використання оператора continue)
    double sum_purchases = 0;
    int purchase_days = 0;
    for (int i = 0; i < N; i++) {
        if (spending[i] == 0) {
            continue; // Пропускаємо дні без покупок за допомогою continue
        }
        sum_purchases += spending[i];
        purchase_days++;
    }
    cout << "Days with purchases: " << purchase_days << "\n";
    if (purchase_days > 0) {
        cout << "Average expenses per spending day: " << (sum_purchases / purchase_days) << " UAH\n";
    }
    else {
        cout << "Average expenses per spending day: 0.00 UAH\n";
    }

    // День вичерпання бюджету (Накопичення циклом while + вихід через break)
    double current_sum = 0;
    int exhaust_day = -1;
    int i = 0;
    while (i < N) {
        current_sum += spending[i];
        if (current_sum > budget) {
            exhaust_day = i + 1; // Запам'ятовуємо людський день (індекс + 1)
            break; // Негайно перериваємо цикл через break
        }
        i++;
    }

    if (exhaust_day != -1) {
        cout << "Budget exhausted on day " << exhaust_day << ", accumulated " << current_sum << ".00 UAH.\n";
    }
    else {
        cout << "Budget was enough for all days! Leftover: " << budget_left << ".00 UAH\n";
    }
}

// 3. ДНІ З ПЕРЕВИЩЕННЯМ ДЕННОГО ЛІМІТУ (Параметр ліміту за замовчуванням)
void checkDailyLimit(const int spending[], int N, double limit) {
    cout << "\nLimit: " << limit << ".00 UAH\n";
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (spending[i] > limit) {
            cout << "  day " << i + 1 << ": " << spending[i] << ".00 UAH\n";
            count++;
        }
    }
    cout << "Total days exceeding limit: " << count << "\n";
}

// 4. ТРИ НАЙДОРОЖЧІ ДНІ (Сортування копії масиву вкладеними циклами за спаданням)
void showTopThree(const int spending[], int N) {
    int temp_arr[31]; // Створюємо тимчасовий масив під ліміт місяця

    // Створюємо копію оригінального масиву, щоб він залишився незмінним за ТЗ
    for (int i = 0; i < N; i++) {
        temp_arr[i] = spending[i];
    }

    // Сортування копії масиву бульбашкою (вкладені цикли) за спаданням
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (temp_arr[j] < temp_arr[j + 1]) {
                int temp = temp_arr[j];
                temp_arr[j] = temp_arr[j + 1];
                temp_arr[j + 1] = temp;
            }
        }
    }

    // Виведення топ-3 значень (або скільки є, якщо днів менше 3)
    cout << "\nTop-3 expenses: ";
    int items_to_print = (N < 3) ? N : 3;
    for (int i = 0; i < items_to_print; i++) {
        cout << temp_arr[i] << ".00";
        if (i < items_to_print - 1) cout << ", ";
    }
    cout << " UAH\n";
}