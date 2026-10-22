
// Аналізатор місячного бюджету
// Челяда Андрій ШІ-13

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int MAX_DAYS = 31; // Максимальна кількість днів для обліку витрат

// Оголошення функцій, які використовуються в програмі
void printSpendings(double spending[], int N);
void minMax(double spending[], int N, double &minSpending, double &maxSpending);
double spendingsSum(double spending[], int N);
void spendingStatistics(double spending[], int N, double budget);
void limitOverrun(double spending[], int N, double limit = 1000.0);
void bubbleSort(double arr[], int N);
void topThree(double spending[], int N);

int main() {
    double budget;
    double limit;
    int N, choice;

Budget:
    cout << "Введіть бюджет на місяць: ";
    cin >> budget;

    // Перевіряємо правильність введення та додатне значення бюджету
    if (cin.fail() || budget <= 0) {
        cin.clear(); // Скидаємо стан помилки введення
        cin.ignore(10000, '\n'); // Очищаємо неправильне введення
        cout << "   Бюджет має бути числом більшим за нуль!!!" << endl;
        goto Budget; // Повертаємося до повторного введення бюджету
    }

Limit:
    cout << "Введіть ліміт: " << endl;
    cin >> limit;

    // Денний ліміт не може бути від'ємним
    if (cin.fail() || limit < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "   Неможливе значення ліміту!!!" << endl;
        goto Limit;
    }

    if (limit == 0) {
        limit = 1000.0; // Якщо введено 0, використовуємо стандартний ліміт
    }

Days:
    cout << "Введіть к-сть днів обліку: ";
    cin >> N;

    // Кількість днів повинна бути в межах від 1 до 31
    if (cin.fail() || N <= 0 || N > MAX_DAYS) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "   Некоректно введена к-сть днів!!!" << endl;
        goto Days;
    }

    double spending[MAX_DAYS] = {0}; // Масив для зберігання щоденних витрат

    cout << "Введіть витрати по днях: " << endl;

    // Послідовно вводимо витрати за кожен день
    for (int i = 0; i < N; i++) {
    Spendings:
        cout << "День " << i + 1 << ": ";
        cin >> spending[i];

        // Витрати не можуть бути від'ємними
        if (cin.fail() || spending[i] < 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "   Некоректно введені витрати!!!" << endl;
            goto Spendings; // Повторюємо введення для цього дня
        }
    }

Menu:
    // Меню повторюється, поки користувач не вибере вихід
    do {
        cout << "------Меню-------" << endl;
        cout << "1) Статистика" << endl;
        cout << "2) Витрати по днях" << endl;
        cout << "3) Найдорожчі дні" << endl;
        cout << "4) Дні, коли ліміт було перевищено" << endl;
        cout << "0) Вихід" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        // Перевіряємо, чи введено число
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "   Введіть число!" << endl;
            goto Menu;
        }

        // Викликаємо функцію відповідно до вибраного пункту меню
        switch (choice) {
            case 1:
                spendingStatistics(spending, N, budget);
                break;

            case 2:
                printSpendings(spending, N);
                break;

            case 3:
                topThree(spending, N);
                break;

            case 4:
                limitOverrun(spending, N, limit);
                break;

            case 0:
                cout << "Вихід з програми." << endl;
                break;

            default:
                cout << "   Немає такого пункту меню!!!" << endl;
                goto Menu;
        }
    } while (choice != 0);

    return 0; // Завершуємо програму
}

// Знаходимо мінімальні та максимальні витрати.
// Результати повертаємо через параметри-посилання.
void minMax(double spending[], int N, double &minSpending, double &maxSpending) {
    // Спочатку вважаємо, що перший елемент є і мінімумом, і максимумом
    minSpending = spending[0];
    maxSpending = spending[0];

    for (int i = 0; i < N; i++) {
        if (minSpending > spending[i]) {
            minSpending = spending[i]; // Оновлюємо мінімальне значення
        }

        if (maxSpending < spending[i]) {
            maxSpending = spending[i]; // Оновлюємо максимальне значення
        }
    }
}

// Рекурсивно обчислюємо суму витрат за всі дні
double spendingsSum(double spending[], int N) {
    if (N <= 0) {
        return 0; // Базовий випадок: елементів для додавання більше немає
    }

    // Додаємо останній елемент до суми попередніх N - 1 елементів
    return spending[N - 1] + spendingsSum(spending, N - 1);
}

// Обчислюємо та виводимо основну статистику витрат
void spendingStatistics(double spending[], int N, double budget) {
    double total = spendingsSum(spending, N); // Загальна сума витрат
    double accumulated = 0; // Витрати, накопичені від першого дня
    int i = 0;

    // Шукаємо перший день, після якого накопичені витрати перевищать бюджет
    while (i < N) {
        accumulated = accumulated + spending[i];

        if (accumulated > budget) {
            break; // Негайно припиняємо цикл після перевищення бюджету
        } else {
            i++; // Переходимо до наступного дня
        }
    }

    if (i < N) {
        cout << "Бюджет перевищено у " << i + 1 << " день" << endl;
        cout << "Накопичена сума: " << accumulated << endl;
    } else {
        cout << "Бюджет не перевищено" << endl;
    }

    double minSpending, maxSpending;
    double average = total / N; // Середні витрати за всі дні обліку

    // Рахуємо дні, у які витрати були більшими за нуль
    int daysWithSpending = 0;

    for (int i = 0; i < N; i++) {
        if (spending[i] == 0) {
            continue; // Пропускаємо день без витрат
        }

        daysWithSpending++;
    }

    // Обчислюємо середні витрати лише за дні з покупками
    if (daysWithSpending == 0) {
        cout << "Днів із витратами немає" << endl;
    } else {
        double averageWithSpending = total / daysWithSpending;
        cout << fixed << setprecision(2) << "Середні витрати за дні з покупками: "
             << averageWithSpending << endl;
    }

    // Визначаємо залишок бюджету або суму перевитрати
    double balance = budget - total;

    if (balance < 0) {
        cout << "Перевитрата склала: " << fabs(balance) << endl;
    } else {
        cout << "Залишок бюджету: " << balance << endl;
    }

    // Отримуємо мінімальні та максимальні витрати за допомогою окремої функції
    minMax(spending, N, minSpending, maxSpending);

    cout << "Загальні витрати: " << total << endl;
    cout << "Мінімальні витрати за день: " << minSpending << endl;
    cout << "Максимальні витрати за день: " << maxSpending << endl;
    cout << "Середні витрати за день: " << average << endl;

    if (total > budget) {
        cout << "   Допустимий бюджет перевищено!!!" << endl;
    }
}

// Виводимо витрати за кожен день без зміни масиву
void printSpendings(double spending[], int N) {
    for (int i = 0; i < N; i++) {
        cout << "День " << i + 1 << ": " << spending[i] << endl;
    }
}

// Знаходимо дні, коли витрати перевищили заданий денний ліміт
void limitOverrun(double spending[], int N, double limit) {
    int daysOverLimit = 0; // Лічильник днів із перевищенням ліміту

    for (int i = 0; i < N; i++) {
        if (spending[i] > limit) {
            cout << "День " << i + 1 << ": " << spending[i] << endl;
            daysOverLimit++;
        }
    }

    // Якщо лічильник залишився нульовим, перевищень не було
    if (daysOverLimit == 0) {
        cout << "Перевищень ліміту немає" << endl;
    }

    cout << "Кількість днів із перевищенням ліміту: "
         << daysOverLimit << endl;
}

// Сортуємо масив за зростанням методом бульбашки
void bubbleSort(double arr[], int N) {
    // Зовнішній цикл визначає кількість проходів сортування
    for (int i = 0; i < N - 1; i++) {
        // Внутрішній цикл порівнює сусідні елементи
        for (int j = 0; j < N - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Міняємо елементи місцями, якщо вони стоять у неправильному порядку
                double temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Виводимо три найбільші суми, не змінюючи початковий масив витрат
void topThree(double spending[], int N) {
    // Для визначення трьох найбільших значень потрібно щонайменше 3 дні
    if (N < 3) {
        cout << "Неможливо порахувати 3 дні з найбільшими витратами" << endl;
        return; // Завершуємо функцію, якщо днів недостатньо
    }

    double copySpending[MAX_DAYS] = {0};

    // Створюємо копію масиву, щоб сортування не змінило початкові дані
    for (int i = 0; i < N; i++) {
        copySpending[i] = spending[i];
    }

    bubbleSort(copySpending, N); // Сортуємо копію за зростанням

    // Три найбільші значення розташовані в кінці відсортованого масиву
    cout << "Три найбільші суми витрат: "
         << copySpending[N - 1] << ", "
         << copySpending[N - 2] << ", "
         << copySpending[N - 3] << endl;
}