/*
Робота з практичного завдання 1
Пилипець Остап ШІ-12
*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void vitratipodn(double spendings[], int n);
void expensesstats(double spendings[], int n, double budget);
void dailylimit(double spendings[], int n, double daily_limit = 1000);
void themostexpensive(double spendings[], int n);
void findMinMax(double spendings[], int n, double &minSpend, double &maxSpend);
double recursiveSum(double spendings[], int n);

int main() {
    double budget, spendings[31];
    int n;
    bool shouldExit = false;

    //вводимо значення та перевірямо на правильінсть вводу
    cout << "Бюджет на місяць (грн): ";
    while (!(cin >> budget) || budget < 0 || cin.peek() != '\n') {
        cout << "Помилка вводу.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Бюджет на місяць (грн): ";
    }
    

    //вводимо значення та перевірямо на правильінсть вводу
    cout << "Кількість днів обліку: ";
    while (!(cin >> n) || n < 1 || n > 31 || cin.peek() != '\n') {
        cout << "Помилка: кількість днів має бути цілим числом від 1 до 31.\n";
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Кількість днів обліку: ";
    }
    

    //вводимо значення та перевірямо на правильінсть вводу
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < n; i++) {
        while (!(cin >> spendings[i]) || spendings[i] < 0 || cin.peek() != '\n') {
            cout << "Помилка: витрати мають бути невід'ємними числами.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Введіть витрати за день " << i + 1 << ": ";
        }
    }
    
    //блок з меню та вибором дії
    do {
    mainMenu:
        cout << "\n1. Показати витрати по днях\n";
        cout << "2. Статистика витрат\n";
        cout << "3. Дні з перевищенням денного ліміту\n";
        cout << "4. Три найдорожчі дні\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";

        int choice;

        if (!(cin >> choice) || cin.peek() != '\n') {
            cout << "Помилка: введіть число від 0 до 4.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            goto mainMenu;
        }
        
        //за допомогою switсh вибираємо потрібну дію
        switch (choice) {
            case 1:
                vitratipodn(spendings, n);
                break;

            case 2:
                expensesstats(spendings, n, budget);
                break;

            case 3:
                dailylimit(spendings, n);
                break;

            case 4:
                themostexpensive(spendings, n);
                break;

            case 0:
                shouldExit = true;
                break;

            default:
                cout << "Помилка: введіть число від 0 до 4.\n";
                goto mainMenu;
        }

    } while (shouldExit == false);

    return 0;
}
//вункціявиводить витрати за всі дні
void vitratipodn(double spendings[], int n) {
    cout << "День\tВитрати, грн\n";

    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << spendings[i] << endl;
    }
}
//функція виводить статистику
void expensesstats(double spendings[], int n, double budget) {
    double minSpend, maxSpend;
    //отримуємо minSpemd та maxSpend
    findMinMax(spendings, n, minSpend, maxSpend);

    cout << "Мінімальні витрати за день: " << minSpend << " грн" << endl;
    cout << "Максимальні витрати за день: " << maxSpend << " грн" << endl;
    //присвоюємо рекурсивне значення змінній
    double total = recursiveSum(spendings, n);
    cout << "Сумарні витрати: " << total << " грн" << endl;

    double balance = budget - total;
    //перевіряємо чи залишився бюджет
    if (balance >= 0) {
        cout << "Залишок бюджету: " << balance << " грн" << endl;
    } else {
        cout << "Витрати перевищили бюджет на: " << fabs(balance) << " грн" << endl;
    }

    double purchasesTotal = 0;
    int daysWithPurchases = 0;
    //рахуємо дні з покупками
    for (int i = 0; i < n; i++) {
        if (spendings[i] == 0) {
            continue;
        }

        purchasesTotal += spendings[i];
        daysWithPurchases++;
    }

    cout << "Днів з покупками: " << daysWithPurchases << endl;
    //виводимо середнє
    if (daysWithPurchases > 0) {
        double average = purchasesTotal / daysWithPurchases;

        cout << "Середні витрати за такий день: " << average << " грн" << endl;
    } else {
        cout << "Покупок не було.\n";
    }

    double accumulated = 0;
    int day = 0;
    bool exceeded = false;
    //рахуємо накопичення та чи перевищено бюджет
    while (day < n) {
        accumulated += spendings[day];
        day++;

        if (accumulated > budget) {
            cout << "Бюджет вичерпано на дні " << day
                 << ", накопичено " << accumulated << " грн." << endl;

            exceeded = true;
            break;
        }
    }

    if (!exceeded) {
        cout << "Бюджету вистачило на всі дні.\n";
        cout << "Залишок: " << budget - accumulated << " грн" << endl;
    }
}
//рекурсивна сума
double recursiveSum(double spendings[], int n) {
    if (n == 0){
        return 0;
    }
    return spendings[n - 1] + recursiveSum(spendings, n - 1);
}
//знаходимо мінімальне та максимальне значення
void findMinMax(double spendings[], int n, double &minSpend, double &maxSpend) {
    minSpend = spendings[0];
    maxSpend = spendings[0];

    for (int i = 1; i < n; i++) {
        if (spendings[i] < minSpend) {
            minSpend = spendings[i];
        }

        if (spendings[i] > maxSpend) {
            maxSpend = spendings[i];
        }
    }
}
//блок який перевіряє чи не було перевищено ліміт
void dailylimit(double spendings[], int n, double daily_limit) {
    double enteredLimit;

    cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
    //перевіряємо на правильність вводу
    if (!(cin >> enteredLimit) || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка: потрібно ввести число.\n";
        return;
    }
    cin.ignore(10000, '\n');

    if (enteredLimit < 0) {
        cout << "Помилка: денний ліміт не може бути від'ємним.\n";
        return;
    } else if (enteredLimit != 0) {
        daily_limit = enteredLimit;
    }

    cout << "Ліміт: " << daily_limit << " грн" << endl;

    int count = 0;
    //в який день перевищено ліміь
    for (int i = 0; i < n; i++) {
        if (spendings[i] > daily_limit) {
            cout << "день " << i + 1 << ": " << spendings[i] << " грн" << endl;
            count++;
        }
    }

    cout << "Разом днів з перевищенням: " << count << endl;
}
//фунція рахує найдорожчі дні
void themostexpensive(double spendings[], int n) {
    double spendingscp[31];

    for (int i = 0; i < n; i++) {
        spendingscp[i] = spendings[i];
    }
    //сортуємо значення в копію маисву
    for (int i = 0; i < n - 1; i++) {
        for (int q = 0; q < n - 1 - i; q++) {
            if (spendingscp[q] < spendingscp[q + 1]) {
                double temp = spendingscp[q];
                spendingscp[q] = spendingscp[q + 1];
                spendingscp[q + 1] = temp;
            }
        }
    }

    int count = n < 3 ? n : 3;

    cout << "Топ-" << count << " витрат: ";
    //виводимо значеня
    for (int i = 0; i < count; i++) {
        cout << spendingscp[i];
        if (i < count - 1) {
            cout << ", ";
        }
    }

    cout << " грн" << endl;
}