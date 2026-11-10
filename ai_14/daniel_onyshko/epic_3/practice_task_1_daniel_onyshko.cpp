#include <iostream>
#include <iomanip>
#include <cmath>     // Для вбудованої функції std::abs
#include <limits>    // Для std::numeric_limits

using namespace std;

// Прототипи функцій
double calculateTotalRecursive(const double spending[], int n, int index = 0);
void findMinMax(const double spending[], int n, double &minVal, double &maxVal);
void showDailySpending(const double spending[], int n);
void showStatistics(double budget, const double spending[], int n);
void showLimitExceedances(const double spending[], int n, double dailyLimit = 1000.0);
void showTopThree(const double spending[], int n);

int main() {
    double budget;
    int n;

    // Валідація вводу бюджету
    cout << "Введіть місячний бюджет (грн): ";
    while (!(cin >> budget) || budget <= 0) {
        cout << "Помилка! Бюджет має бути додатним числом. Спробуйте ще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Валідація кількості днів (облік в межах одного місяця, 1-31)
    cout << "Введіть кількість днів обліку (1-31): ";
    while (!(cin >> n) || n <= 0 || n > 31) {
        cout << "Помилка! Кількість днів має бути цілим числом від 1 до 31. Спробуйте ще раз: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Динамічне виділення пам'яті під масив витрат
    double *spending = new double[n];

    cout << "Введіть витрати по днях (" << n << " чисел через пробіл): ";
    for (int i = 0; i < n; ++i) {
        while (!(cin >> spending[i]) || spending[i] < 0) {
            cout << "Помилка для дня " << (i + 1) << ". Введіть невід'ємну суму витрат: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    int choice;

menu_start: // Мітка для перенаправлення через goto при помилці вибору меню
    do {
        cout << "1. Показати витрати по днях\n";
        cout << "2. Статистика витрат\n";
        cout << "3. Дні з перевищенням денного ліміту\n";
        cout << "4. Три найдорожчі дні\n";
        cout << "0. Вийти\n";
        cout << "Виберіть пункт меню (0-4): ";

        // Валідація пункту меню (введення нечислових символів)
        if (!(cin >> choice)) {
            cout << "Помилка вводу! Будь ласка, введіть число від 0 до 4.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto menu_start;
        }

        switch (choice) {
            case 1:
                showDailySpending(spending, n);
                break;
            case 2:
                showStatistics(budget, spending, n);
                break;
            case 3:
                showLimitExceedances(spending, n); // Використає параметр за замовчуванням 1000.0 грн
                break;
            case 4:
                showTopThree(spending, n);
                break;
            case 0:
                cout << "Вихід з програми. До побачення!\n";
                break;
            default:
                cout << "Невірний пункт меню! Спробуйте знову.\n";
                goto menu_start; // Повернення до головного меню через goto
        }

    } while (choice != 0);

    // Звільнення динамічної пам'яті
    delete[] spending;

    return 0;
}

// 1. Рекурсивна функція для обчислення сумарних витрат без циклів
double calculateTotalRecursive(const double spending[], int n, int index) {
    if (index >= n) {
        return 0.0;
    }
    return spending[index] + calculateTotalRecursive(spending, n, index + 1);
}

// 2. Функція знаходження мін. та макс. витрат через параметри-посилання (&)
void findMinMax(const double spending[], int n, double &minVal, double &maxVal) {
    if (n <= 0) return;
    minVal = spending[0];
    maxVal = spending[0];
    for (int i = 1; i < n; ++i) {
        if (spending[i] < minVal) {
            minVal = spending[i];
        }
        if (spending[i] > maxVal) {
            maxVal = spending[i];
        }
    }
}

// Пункт 1: Виведення витрат по днях за допомогою циклу for
void showDailySpending(const double spending[], int n) {
    cout << "\nДень\t Витрати, грн\n";
    for (int i = 0; i < n; ++i) {
        cout << setw(3) << (i + 1) << "\t\t" << fixed << setprecision(2) << setw(10) << spending[i] << "\n";
    }
}

// Пункт 2: Статистика витрат
void showStatistics(double budget, const double spending[], int n) {
    double minVal = 0.0, maxVal = 0.0;
    findMinMax(spending, n, minVal, maxVal);

    // Обчислення суми через рекурсивну функцію
    double total = calculateTotalRecursive(spending, n, 0);

    cout << "\n--- Статистика витрат ---\n";
    cout << "Мінімальні витрати за день: \t" << fixed << setprecision(2) << minVal << " грн\n";
    cout << "Максимальні витрати за день: \t" << maxVal << " грн\n";
    cout << "Сумарні витрати: \t\t" << total << " грн\n";

    // Використання вбудованої математичної функції std::abs для розрахунку перевитрати
    if (total > budget) {
        double overspending = std::abs(budget - total);
        cout << "Перевитрата понад бюджет: \t" << overspending << " грн\n";
    } else {
        double remainder = budget - total;
        cout << "Залишок бюджету: \t\t" << remainder << " грн\n";
    }

    // Підрахунок середніх витрат за дні з покупками (з використанням continue)
    int countWithPurchases = 0;
    double sumWithPurchases = 0.0;
    for (int i = 0; i < n; ++i) {
        if (spending[i] == 0.0) {
            continue; // Пропускаємо дні без покупок
        }
        countWithPurchases++;
        sumWithPurchases += spending[i];
    }

    cout << "Днів з покупками:\t\t" << countWithPurchases << "\n";
    if (countWithPurchases > 0) {
        double avg = sumWithPurchases / countWithPurchases;
        cout << "Середні витрати за такий день: " << avg << " грн\n";
    } else {
        cout << "Середні витрати за такий день: 0.00 грн\n";
    }

    // Накопичення витрат через цикл while та вихід через break, коли бюджет вичерпано
    double accumulated = 0.0;
    int exhaustDay = -1;
    int i = 0;
    while (i < n) {
        accumulated += spending[i];
        if (accumulated > budget) {
            exhaustDay = i + 1;
            break; // Зупиняємо цикл одразу на дні перевищення
        }
        i++;
    }

    if (exhaustDay != -1) {
        cout << "Бюджет вичерпано на дні " << exhaustDay << ", накопичено " << accumulated << " грн.\n";
    } else {
        cout << "Бюджету вистачило на всі дні. Залишок: " << (budget - accumulated) << " грн.\n";
    }
}

// Пункт 3: Дні з перевищенням денного ліміту (з параметром за замовчуванням 1000.0 грн)
void showLimitExceedances(const double spending[], int n, double dailyLimit) {
    cout << "\nВведіть денний ліміт (грн, 0 = використати за замовчуванням 1000 грн): ";
    double inputLimit;
    while (!(cin >> inputLimit) || inputLimit < 0) {
        cout << "Некоректний ввід. Введіть невід'ємне число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (inputLimit != 0.0) {
        dailyLimit = inputLimit;
    }

    cout << "Актуальний ліміт: " << fixed << setprecision(2) << dailyLimit << " грн\n";

    int exceedCount = 0;
    for (int i = 0; i < n; ++i) {
        if (spending[i] > dailyLimit) {
            cout << "  день " << (i + 1) << ": " << spending[i] << " грн\n";
            exceedCount++;
        }
    }
    cout << "Разом днів з перевищенням: " << exceedCount << "\n";
}

// Пункт 4: Три найдорожчі дні (сортування копії масиву за спаданням вкладеними циклами)
void showTopThree(const double spending[], int n) {
    // Створюємо копію масиву динамічно, щоб оригінал залишився незмінним
    double *copyArr = new double[n];
    for (int i = 0; i < n; ++i) {
        copyArr[i] = spending[i];
    }

    // Вкладені цикли (сортування бульбашкою) для сортування копії за спаданням
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (copyArr[j] < copyArr[j + 1]) {
                double temp = copyArr[j];
                copyArr[j] = copyArr[j + 1];
                copyArr[j + 1] = temp;
            }
        }
    }

    cout << "\nТоп-3 витрат: ";
    int limit = (n < 3) ? n : 3;
    if (limit == 0) {
        cout << "немає даних.";
    } else {
        for (int i = 0; i < limit; ++i) {
            cout << fixed << setprecision(2) << copyArr[i];
            if (i < limit - 1) {
                cout << ", ";
            }
        }
        cout << " грн";
    }
    cout << "\n";

    delete[] copyArr; // Звільняємо пам'ять копії масиву
}