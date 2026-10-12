#include <iostream>
#include <cmath>

using namespace std;

// Сума витрат
double sum(double a[], int n) {
    if (n == 0)
        return 0;
// Рекурсивно обчислюємо суму
    return a[n - 1] + sum(a, n - 1);
}

// Мінімум і максимум
void minMax(double a[], int n, double& min, double& max) {
    min = a[0];
    max = a[0];

    for (int i = 1; i < n; i++) {
        if (a[i] < min)
            min = a[i];

        if (a[i] > max)
            max = a[i];
    }
}

// Показати витрати
void show(double a[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "День " << i + 1 << ": "
             << a[i] << " грн" << endl;
    }
}

// Статистика
void statistics(double a[], int n, double budget) {
    double min, max;
    minMax(a, n, min, max);

    double total = sum(a, n);

    cout << "Мінімальні витрати: " << min << " грн" << endl;
    cout << "Максимальні витрати: " << max << " грн" << endl;
    cout << "Сумарні витрати: " << total << " грн" << endl;
    // Перевірка перевитрати або залишку бюджету
    if (total > budget)
        cout << "Перевитрата: " << abs(total - budget) << " грн" << endl;
    else
        cout << "Залишок бюджету: " << budget - total << " грн" << endl;

    int days = 0;
    double shopping = 0;
    // Рахуємо середні витрати за дні, де були витрати
    for (int i = 0; i < n; i++) {
        if (a[i] == 0)
            continue;

        shopping += a[i];
        days++;
    }

    if (days > 0)
        cout << "Середні витрати: " << shopping / days << " грн" << endl;

    double current = 0;
    int day = 0;
    // Перевірка, на який день вичерпається бюджет
    while (day < n) {
        current += a[day];
        // Перевірка, чи перевищено бюджет
        if (current > budget) {
            cout << "Бюджет вичерпано на дні "
                 << day + 1 << endl;
            break;
        }

        day++;
    }

    if (day == n)
        cout << "Бюджету вистачило на всі дні." << endl;
}

// Перевищення ліміту
void limitDays(double a[], int n, double limit = 1000) {
    int count = 0;

    cout << "Дні з перевищенням:" << endl;
    // Виводимо дні, де витрати перевищують ліміт
    for (int i = 0; i < n; i++) {
        // Перевіряємо, чи витрати перевищують ліміт
        if (a[i] > limit) {
            cout << "День " << i + 1
                 << ": " << a[i] << " грн" << endl;

            count++;
        }
    }

    cout << "Разом: " << count << endl;
}

// Три найдорожчі дні
void topThree(double a[], int n) {
    double b[31];

    // Копіюємо масив
    for (int i = 0; i < n; i++)
        b[i] = a[i];

    // Сортування від більшого до меншого
    for (int i = 0; i < n - 1; i++) {
        // Знаходимо найбільший елемент у невідсортованій частині
        for (int j = i + 1; j < n; j++) {
            // Якщо елемент j більший за елемент i, міняємо їх місцями
            if (b[i] < b[j]) {
                double temp = b[i];
                b[i] = b[j];
                b[j] = temp;
            }
        }
    }

    int count = n;

    if (count > 3)
        count = 3;

    cout << "Топ-" << count << " витрат: ";

    for (int i = 0; i < count; i++) {
        cout << b[i];

        if (i < count - 1)
            cout << ", ";
    }

    cout << " грн" << endl;
}

int main() {
    double budget;
    int n;
    double spending[31];

    cout << "Бюджет на місяць: ";
    cin >> budget;

    cout << "Кількість днів: ";
    cin >> n;
    // Перевірка на помилку вводу
    if (n < 1 || n > 31) {
        cout << "Помилка!" << endl;
        return 0;
    }

    cout << "Витрати по днях:" << endl;

    for (int i = 0; i < n; i++)
        cin >> spending[i];

menu:

    int choice;

    cout << endl;
    cout << "===== МЕНЮ =====" << endl;
    cout << "1 - Показати витрати" << endl;
    cout << "2 - Статистика" << endl;
    cout << "3 - Перевищення ліміту" << endl;
    cout << "4 - Три найдорожчі дні" << endl;
    cout << "0 - Вийти" << endl;
    cout << "Ваш вибір: ";
    cin >> choice;

    // Перевірка на помилку вводу
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Помилка вводу!" << endl;
        goto menu;
    }

    // Виконання вибраної дії 
    switch (choice) {
        case 1:
            show(spending, n);
            break;

        case 2:
            statistics(spending, n, budget);
            break;

        case 3: {
            double limit;

            cout << "Денний ліміт (0 = 1000): ";
            cin >> limit;
            
            if (limit == 0)
                limitDays(spending, n);
            else
                limitDays(spending, n, limit);

            break;
        }

        case 4:
            topThree(spending, n);
            break;

        case 0:
            cout << "Програму завершено." << endl;
            return 0;

        default:
            cout << "Неправильний пункт меню!" << endl;
            goto menu;
    }
    goto menu;
    return 0;
}