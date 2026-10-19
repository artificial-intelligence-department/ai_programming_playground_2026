#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Виводить витрати за кожен день у вигляді таблиці
void dailyExpenses(double spending[], int days) {
    cout << "День" << "     Витрати, грн" << endl;

    // Перебираємо всі дні та виводимо витрати за кожен із них
    for (int i = 0; i < days; i++) {
        cout << i + 1 << "         " << fixed << setprecision(2) << spending[i] << endl;
    }
}

// Знаходить найменші та найбільші витрати за один день, min і max передаються за посиланням, тому їхні значення змінюються
void findMinMax(double spending[], int days, double& min, double& max) {
    min = spending[0];
    max = spending[0];
    for (int i = 1; i < days; i++) {
        if (spending[i] < min) {
            min = spending[i];
        }
        if (spending[i] > max) {
            max = spending[i];
        }
    }
}

// Обчислює загальну суму витрат за допомогою рекурсії
double findSum(double spending[], int days) {
    if (days == 0) {
        return 0;
    }

    // Додає витрати останнього дня до суми витрат попередніх днів
    return spending[days - 1] + findSum(spending, days - 1);
}

// Перевіряє, на якому дні накопичені витрати перевищать місячний бюджет
void findBudgetExhaustion(double spending[], int days, int monthly_budget) {
    int day = 0;
    double normal_spending = 0.0;
    bool budget_exceeded = false;

    // Послідовно додає витрати кожного дня до загальної суми
    while (day < days) {
        normal_spending += spending[day];

        // Якщо сума стала більшою за бюджет, припиняє перевірку
        if (normal_spending > monthly_budget) {
            budget_exceeded = true;
            break;
        }
        day++;
    }

    // Виводить результат перевірки бюджету
    if (budget_exceeded) {
        cout << "Бюджет вичерпано на дні " << day + 1 << ", накопичено " << fixed << setprecision(2) << normal_spending << " грн" << endl;
    } else {
        cout << "Бюджету вистачило на всі дні" << endl;
        cout << "Залишок бюджету: " << fixed << setprecision(2) << monthly_budget - normal_spending << " грн" << endl;
    }

}

// Виводить основну статистику витрат за період
void showStatistics(double spending[], int days, int monthly_budget) {
    double min_spending;
    double max_spending;
    double budget_overrun = monthly_budget - findSum(spending, days);
    int days_with_spending = 0;
    double average_spending = 0;
    findMinMax(spending, days, min_spending, max_spending); 
    cout << "Мінімальні витрати за день: " << fixed << setprecision(2) << min_spending << " грн" << endl;
    cout << "Максимальні витрати за день: " << fixed << setprecision(2) << max_spending << " грн" << endl;
    cout << "Сумарні витрати: " << fixed << setprecision(2) << findSum(spending, days) << " грн" << endl; // Обчислює та виводить загальну суму витрат
    cout << "Перевитрата понад бюджет: " << fixed << setprecision(2) << abs(budget_overrun) << " грн" << endl; // Виводить модуль різниці між бюджетом і сумарними витратами
    
    // Підраховує дні, у які витрати були більшими за нуль
    for (int i = 0; i < days; i++) {
        if (spending[i] == 0 ) {
            continue;  // Пропускає дні без витрат
        } else {
            days_with_spending++;
            average_spending = findSum(spending, days) / days_with_spending; // Обчислює середні витрати серед днів із покупками
        }
    }
    cout << "Днів з покупками:  " << days_with_spending << endl;
    cout << "Середні витрати за такий день: " << fixed << setprecision(2) << average_spending << endl;
    findBudgetExhaustion(spending, days, monthly_budget);
}

// Виводить дні, у які витрати перевищили встановлений ліміт. Якщо ліміт не передано, за замовчуванням він становить 1000 грн
void findDaysOverLimit(double spending[], int days, double daily_limit = 1000) {
    int count = 0;
    cout << "Ліміт: " << fixed << setprecision(2) << daily_limit << " грн" << endl;

    for (int i = 0; i < days; i++) {
        if (spending[i] > daily_limit) {
            cout << "  день " << i + 1 << ": " << spending[i] << " грн" << endl;
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}

// Запитує у користувача денний ліміт і викликає відповідну функцію
void findDailyLimitExceeded(double spending[], int days) {
    double daily_limit;
    cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
    cin >> daily_limit;
    if (daily_limit == 0) { 
        findDaysOverLimit(spending, days);  // Викликає функцію без третього аргументу: ліміт буде 1000 грн
    } else if (daily_limit > 0) {
        findDaysOverLimit(spending, days, daily_limit);   // Використовує ліміт, введений користувачем
    } else if (daily_limit < 0) {
        cout << "Помилка. Денний ліміт не може бути від'ємним" << endl;
    }
}

// Знаходить три найбільші значення витрат
void findTopThree(double spending[], int days) {
    double sorted_spending[31] = {0};
    for (int i = 0; i < days; i++) {
        sorted_spending[i] = spending[i];
    }

    // Сортує витрати за спаданням методом бульбашки, більші значення поступово переміщуються на початок масиву
    for (int i = 0; i < days - 1; i++) {
        for (int j = 0; j < days - 1; j++) {
            if (sorted_spending[j] < sorted_spending[j+1]) {
                // Міняємо сусідні елементи місцями
                double temporary = sorted_spending[j];
                sorted_spending[j] = sorted_spending[j+1];
                sorted_spending[j+1] = temporary;
            }
        }
    }
    int count;
    if (days < 3) {
        count = days;
    } else {
        count = 3;
    }
    cout << "Топ-3 витрат: " << endl;
    // Виводить три найбільші витрати або меншу кількість, якщо днів мало
    for (int i = 0; i < count; i++) {
        cout << "  " << i + 1 << ". " << fixed << setprecision(2) << sorted_spending[i] << " грн" << endl;
    }
}


int main() {
    int monthly_budget = 0;
    // Вводимо місячний бюджет і перевіряємо правильність значення
    cout << "Бюджет на місяць(грн): ";
    while (!(cin >> monthly_budget) || monthly_budget <= 0) {
        // Очищаємо стан помилки та пропускаємо некоректне введення
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка. Бюджет має бути додатнім числом: ";
    }

    int days = 0;
    // Вводимо кількість днів обліку: від 0 до 31
    cout << "Кількість днів обліку: ";
    while (!(cin >> days) || days < 0 || days > 31) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка. Кількість днів обліку повинна бути від 0 до 31: ";
    }

    double spending[31] = {0};
    cout << "Витрати по днях (грн): ";
    // Вводимо витрати для кожного дня та не допускаємо від'ємних значень
    for (int i = 0; i < days; i++) {
        while (!(cin >> spending[i]) || spending[i] < 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка. Витрати мають бути додатнім числом або 0: ";
        }
    } 

    int choice;

    // Цикл do-while повторює показ меню, доки користувач не вибере 0
    do {
    menu:
        cout << "Пункт" << "     Операція" << endl;
        cout << "1" << "        Показати витрати по днях" << endl;
        cout << "2" << "        Статистика витрат" << endl;
        cout << "3" << "        Дні з перевищенням денного ліміту" << endl;
        cout << "4" << "        Три найдорожчі дні" << endl;
        cout << "0" << "        Вийти" << endl;

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка. Потрібно ввести число." << endl;
            goto menu;  // Повертає до повторного показу меню
        }

        if (choice < 0 || choice > 4) {
            cout << "Помилка. Такого пункту меню немає." << endl;
            goto menu;
        }

        cout << " " << endl;

        // Виконує дію відповідно до вибраного пункту меню
        switch (choice) {
            case 1: dailyExpenses(spending, days); break;
            case 2: showStatistics(spending, days, monthly_budget); break;
            case 3: findDailyLimitExceeded(spending, days); break;
            case 4: findTopThree(spending, days); break; 
        }
        cout << " " << endl;

    } while (choice != 0);  // Завершує роботу, якщо вибрано 0

    return 0;
}