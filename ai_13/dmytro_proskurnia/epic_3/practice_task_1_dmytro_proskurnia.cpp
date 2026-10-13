/*
Practice Task Проскурня Дмитро ШІ-13
*/
#include <iostream>
#include <iomanip>
#include <cmath>

void printSpendings(double arr[], int n);
void minMax(double arr[], int n, double& min_el, double& max_el);
double spendingsSum(double arr[], int n);
void spendingStatistics(double arr[], int n, double budget);
void limitOverrun(double arr[], int N, double limit = 0);
void mostExpensive(double arr[], int N);
void bubbleSort(double arr[], int N);

int main() {
//Ввід
wrong_budget:
    std::cout << "Бюджет на місяць (грн): ";
    double budget{};
    std::cin >> budget;
    if (budget < 0) {
        std::cout << "Бюджет має бути не меньший за 0" << std::endl;
        goto wrong_budget;
    }

wrong_N:
    std::cout << "Кількість днів обліку: ";
    int N{};
    std::cin >> N;
    if (N <= 0 || N > 31) {
        std::cout << "Кількість днів має бути не меньша за 1 та не більша за 31" << std::endl;
        goto wrong_N;
    }

wrong_el:
    std::cout << "Витрати по днях (грн): ";
    double spending[N];
    bool has_wrong = false;
    for (auto& el : spending) {
        std::cin >> el;
        if (el < 0) {
            has_wrong = true;
        }
    }

    if (has_wrong) {
        std::cout << "Кожна витрата має бути не меньша за 0" << std::endl;
        goto wrong_el;
    }

    //Меню
    int operation{};
    do {
        std::cout << std::endl;
        std::cout << "=============== Меню ===============" << std::endl;
        std::cout << "1: Показати витрати по днях" << std::endl;
        std::cout << "2: Статистика витрат" << std::endl;
        std::cout << "3: Дні з перевищенням денного ліміту" << std::endl;
        std::cout << "4: Три найдорожчі дні" << std::endl;
        std::cout << "0: Вийти" << std::endl;
        std::cin >> operation;
        std::cout << std::endl;

        switch (operation)
        {
        case 1:
            printSpendings(spending, N);
            break;

        case 2:
            spendingStatistics(spending, N, budget);
            break;

        case 3:
            limitOverrun(spending, N);
            break;

        case 4:
            mostExpensive(spending, N);
            break;

        default:
            break;
        }


    } while (operation);


    return 0;
}

void printSpendings(double arr[], int n) {
    std::cout << "День     Витрати, грн" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << std::fixed << std::setprecision(2) << std::setw(4)
                  << i + 1 << std::setw(17) << arr[i] << std::endl;
    }

}

void minMax(double arr[], int n, double& min_el, double& max_el) {
    min_el = arr[0], max_el = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_el)
            min_el = arr[i];
        if (arr[i] > max_el)
            max_el = arr[i];
    }
}

double spendingsSum(double arr[], int n) {
    if (n <= 0)
        return 0;
    return arr[n - 1] + spendingsSum(arr, n - 1);
}

void spendingStatistics(double arr[], int n, double budget) {
    double min_el{}, max_el{};
    minMax(arr, n, min_el, max_el);

    double sum = spendingsSum(arr, n);

    double overrun = budget - sum;
    if (overrun >= 0)
        overrun = 0;
    else
        overrun = std::abs(overrun);

    int days{};
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0)
            days++;
    }

    double average = (days == 0 ? 0 : sum / days);

    double overrun_day{};
    double overrun_sum{};
    for (int i = 0; i < n; i++) {
        overrun_day = i + 1;
        overrun_sum += arr[i];
        if (overrun_sum > budget) {
            break;
        }
    }

    std::cout << "Мінімальні витрати за день:    " << std::setw(20) << std::fixed << std::setprecision(2)
              << min_el  << " грн" << std::endl;
    std::cout << "Максимальні витрати за день:   " << std::setw(20) << std::fixed << std::setprecision(2)
              << max_el  << " грн" << std::endl;
    std::cout << "Сумарні витрати:               " << std::setw(20) << std::fixed << std::setprecision(2)
              << sum     << " грн" << std::endl;
    std::cout << "Перевитрата понад бюджет:      " << std::setw(20) << std::fixed << std::setprecision(2)
              << overrun << " грн" << std::endl;
    std::cout << "Днів з покупками:              " << std::setw(20)
              << days              << std::endl;
    std::cout << "Середні витрати за такий день: " << std::setw(20) << std::fixed << std::setprecision(2)
              << average << " грн" << std::endl;
    if (overrun_sum <= budget)
    std::cout << std::setw(20) << "Бюджет не вичерпано" << std::endl;
    else
    std::cout << std::defaultfloat << "Бюджет вичерпано на дні " << overrun_day << std::fixed
              << std::setprecision(2) << ", накопичено " << std::setw(13) << overrun_sum << " грн." << std::endl;

}

void limitOverrun(double arr[], int N, double limit) {
    std::cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
    std::cin >> limit;
    if (limit == 0)
        limit = 1000;

    std::cout << std::fixed << std::setprecision(2) << "Ліміт: " << limit << " грн" << std::endl;

    int cnt_overrun = 0;
    for (int i = 0; i < N; i++) {
        if (arr[i] > limit) {
            cnt_overrun++;
            std::cout << std::fixed << std::setprecision(2)
                      << "\tдень " << i + 1 << ": " << arr[i] << " грн" << std::endl;
        }
    }
    std::cout << "Разом днів з перевищенням: " << cnt_overrun << std::endl;
}

void mostExpensive(double arr[], int N) {
    double sorted[N];
    for (int i = 0; i < N; i++)
        sorted[i] = arr[i];

    bubbleSort(sorted, N);

    std::cout << "Топ-3 витрат: ";
    for (int i = 0; i < std::min(3, N); i++) {
        std::cout << std::fixed << std::setprecision(2) << sorted[i] << ", ";
    }
    std::cout << "грн" << std::endl;
}

void bubbleSort(double arr[], int N) {
    for (int i = 0; i < N - 1; i++)
        for (int j = i + 1; j < N; j++)
            if (arr[i] < arr[j])
                std::swap(arr[i], arr[j]);
}