/*
    Class Practice Work, Момоток Артем, ШІ-13
*/
#include <iostream>
#include <iomanip>

const double DEFAULT_LIMIT = 1000.0;

// Виводить витрати для кожного дня.
void expensesByDay(const double spending[], int N) {
    std::cout << "Витрати по днях: " << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << "День " << (i + 1) << ": " << spending[i] << " грн" << std::endl;
    }
}

// Знаходить найменші та найбільші витрати й записує результати у параметри-посилання.
void findMinMax(const double spending[], int N, double& minValue, double& maxValue) {
    minValue = spending[0];
    maxValue = spending[0];
    for (int i = 1; i < N; i++) {
        if (spending[i] < minValue) minValue = spending[i];
        if (spending[i] > maxValue) maxValue = spending[i];
    }
}

// Повертає суму перших N елементів; умова завершення рекурсії — N == 0.
double sumRecursive(const double spending[], int N) {
    if (N == 0) return 0;
    return spending[N - 1] + sumRecursive(spending, N - 1);
}

// Обчислює підсумки, баланс бюджету, середні витрати та день перевищення бюджету.
void spendingStatistics(const double spending[], int N, double budget) {
    double minValue, maxValue;
    findMinMax(spending, N, minValue, maxValue);
    std::cout << "Мінімальні витрати за день: " << minValue << " грн" << std::endl;
    std::cout << "Максимальні витрати за день: " << maxValue << " грн" << std::endl;

    double total = sumRecursive(spending, N);
    std::cout << "Сумарні витрати: " << total << " грн" << std::endl;

    double balance = budget - total;
    if (balance < 0) {
        std::cout << "Перевитрата понад бюджет: " << std::abs(balance) << " грн" << std::endl;
    } else {
        std::cout << "Залишок бюджету: " << balance << " грн" << std::endl;
    }

    // Середні витрати за дні з покупками (continue пропускає нульові дні)
    double purchasesSum = 0;
    int purchaseDays = 0;
    for (int i = 0; i < N; i++) {
        if (spending[i] == 0) continue;
        purchasesSum += spending[i];
        purchaseDays++;
    }
    std::cout << "Днів з покупками: " << purchaseDays << std::endl;
    if (purchaseDays > 0) {
        std::cout << "Середні витрати за такий день: " << purchasesSum / purchaseDays << " грн" << std::endl;
    } else {
        std::cout << "Покупок не було, середні витрати порахувати неможливо." << std::endl;
    }

    // Накопичує витрати по днях і зупиняється, якщо вони перевищили бюджет.
    double accumulated = 0;
    int day = 0;
    bool exhausted = false;
    while (day < N) {
        accumulated += spending[day];
        day++;
        if (accumulated > budget) {
            exhausted = true;
            break;
        }
    }
    if (exhausted) {
        std::cout << "Бюджет вичерпано на дні " << day << ", накопичено " << accumulated << " грн." << std::endl;
    } else {
        std::cout << "Бюджету вистачило на всі дні. Залишок: " << budget - accumulated << " грн." << std::endl;
    }
}

// Виводить дні, у які витрати більші за вказаний ліміт.
void daysOverLimit(const double spending[], int N, double limit = DEFAULT_LIMIT) {
    std::cout << "Ліміт: " << limit << " грн" << std::endl;
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (spending[i] > limit) {
            std::cout << "  День " << (i + 1) << ": " << spending[i] << " грн" << std::endl;
            count++;
        }
    }
    std::cout << "Разом днів з перевищенням: " << count << std::endl;
}

// Сортує копію витрат за спаданням і виводить до трьох найбільших значень.
void topThreeDays(const double spending[], int N) {
    double copy[100];
    for (int i = 0; i < N; i++) {
        copy[i] = spending[i];
    }

    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (copy[j] < copy[j + 1]) {
                double temp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp;
            }
        }
    }

    int count;
    if (N < 3) {
        count = N;
    } else {
        count = 3;
    }
    std::cout << "Топ-" << count << " витрат: ";
    for (int i = 0; i < count; i++) {
        if (i > 0) std::cout << ", ";
        std::cout << copy[i];
    }
    std::cout << " грн" << std::endl;
}

// Перевіряє введений ліміт; 0 означає використання стандартного ліміту.
void daysOverLimitMenu(const double spending[], int N) {
    double limit;
    while (true) {
        std::cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
        std::cin >> limit;
        if (std::cin.fail()) {
            if (std::cin.eof()) return;      // ввід закінчився
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        } else if (limit >= 0) {
            break;
        }
        std::cout << "Некоректний ввід: потрібне число від 0." << std::endl;
    }
    if (limit == 0) {
        daysOverLimit(spending, N);          // береться ліміт за замовчуванням 1000 грн
    } else {
        daysOverLimit(spending, N, limit);
    }
}

int main() {
    // Налаштовуємо виведення чисел із двома знаками після коми.
    std::cout << std::fixed << std::setprecision(2);

    // Запитуємо додатний бюджет і повторюємо введення, доки значення некоректне.
    double budget;
    while (true) {
        std::cout << "Бюджет на місяць, грн: ";
        std::cin >> budget;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        } else if (budget > 0) {
            break;
        }
        std::cout << "Бюджет має бути числом більше 0." << std::endl;
    }

    // Кількість днів: ціле число від 1 до 31
    int N;
    while (true) {
        std::cout << "Кількість днів обліку: ";
        std::cin >> N;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        } else if (N >= 1 && N <= 31) {
            break;
        }
        std::cout << "Кількість днів має бути цілим числом від 1 до 31." << std::endl;
    }

    // Зчитуємо невід'ємні витрати для кожного дня.
    double spending[100];
    std::cout << "Витрати по днях, грн: ";
    for (int i = 0; i < N; i++) {
        while (true) {
            std::cin >> spending[i];
            if (std::cin.fail() ) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
            } else if (spending[i] >= 0) {
                break;
            }
            std::cout << "Некоректний ввід для дня " << (i + 1)
                      << ": потрібне число від 0. Введіть це значення ще раз: ";
        }
    }

    // Показуємо меню повторно, доки користувач не вибере вихід.
    int action{};

    do {
        menu:
        std::cout << std::endl;
        std::cout << "1 - Показати витрати по днях" << std::endl;
        std::cout << "2 - Статистика витрат" << std::endl;
        std::cout << "3 - Дні з перевищенням денного ліміту" << std::endl;
        std::cout << "4 - Три найдорожчі дні" << std::endl;
        std::cout << "0 - Вийти" << std::endl;
        std::cout << "Ваш вибір: ";

        // Зчитуємо вибір; некоректне введення передаємо до гілки default.
        std::cin >> action;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            action = -1;
        }

        std::cout << std::endl;
        // Виконуємо дію, що відповідає пункту меню.
        switch (action) {

            case 1: expensesByDay(spending, N);
            break;

            case 2: spendingStatistics(spending, N, budget);
            break;

            case 3: daysOverLimitMenu(spending, N);
            break;

            case 4: topThreeDays(spending, N);
            break;

            case 0: std::cout << "До побачення!" << std::endl;
            break;

            default: std::cout << "Некоректний ввід" << std::endl;
            goto menu;
        }

    } while (action != 0);

    return 0;
}