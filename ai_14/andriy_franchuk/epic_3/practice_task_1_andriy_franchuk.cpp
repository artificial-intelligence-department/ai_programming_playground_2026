/*
Аналізатор місячного бюджету
Франчук Андрій
ШІ-14 (ai_14)
*/
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Прототипи функцій
void option1(const int spending[], int N);
void option2(const int spending[], int N, double budget);
void option3(const int spending[], int N, int limit = 1000);
void option4(const int spending[], int N);

void Min(int &min, const int spending[], int N);
void Max(int &max, const int spending[], int N);

int calculateTotal(const int spending[], int N);

void validateInput(double &value);
void validateInput(int &value);


int main() {
    double budget = 0;  // Місячний бюджет
    int N = 0;          // Кількість днів обліку

    // Введення місячного бюджету з перевіркою
    cout << "Бюджет на місяць (грн): ";
    validateInput(budget);

    // Введення кількості днів з перевіркою діапазону
    do {
        cout << "Кількість днів обліку: ";
        validateInput(N);

        if (N < 1 || N > 31) {
            cout << "Помилка. Кількість днів має бути від 1 до 31."
                 << endl;
        }
    } while (N < 1 || N > 31);

    // Створення динамічного масиву витрат
    int* spending = new int[N];

    cout << "Витрати по днях (грн): ";

    // Введення витрат за кожен день з перевіркою
    for (int i = 0; i < N; i++) {
        validateInput(spending[i]);
    }

    int choice;  // Вибір пункту меню

    // Мітка для повторного виведення меню
    MENU:

    do {
        // Виведення головного меню
        cout << "МЕНЮ:" << endl;
        cout << "1 - Показати витрати по днях" << endl;
        cout << "2 - Статистика витрат" << endl;
        cout << "3 - Дні з перевищенням денного ліміту" << endl;
        cout << "4 - Три найдорожчі дні" << endl;
        cout << "0 - Вийти" << endl;
        cout << "Ваш вибір: ";

        // Перевірка правильності введення пункту меню
        if (!(cin >> choice)) {
            cout << "Помилка, введіть числове значення від 0 до 4."
                 << endl;

            cin.clear();  // Скидання стану помилки потоку

            // Очищення некоректного введення
            while (cin.get() != '\n');

            goto MENU;  // Повторне виведення меню
        }

        // Виконання вибраного пункту меню
        switch (choice) {
            case 0: {
                // Завершення роботи програми
                break;
            }

            case 1: {
                // Виведення витрат за кожен день
                option1(spending, N);
                break;
            }

            case 2: {
                // Виведення статистики витрат
                option2(spending, N, budget);
                break;
            }

            case 3: {
                // Введення користувацького денного ліміту
                int user_limit;

                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";

                // Перевірка введеного ліміту
                if (!(cin >> user_limit) || user_limit < 0) {
                    cin.clear();

                    // Очищення некоректного введення
                    while (cin.get() != '\n');

                    user_limit = 0;
                }

                // Якщо ліміт дорівнює 0, використовується значення 1000
                if (user_limit == 0) {
                    option3(spending, N);
                } else {
                    option3(spending, N, user_limit);
                }

                break;
            }

            case 4: {
                // Виведення трьох найбільших витрат
                option4(spending, N);
                break;
            }

            default: {
                // Повідомлення про неправильний пункт меню
                cout << "Неправильний пункт меню." << endl;
                break;
            }
        }

    } while (choice != 0);

    // Звільнення пам'яті динамічного масиву
    delete[] spending;

    return 0;  // Завершення програми
}


// Рекурсивне обчислення загальної суми витрат
int calculateTotal(const int spending[], int N) {
    // Умова завершення рекурсії
    if (N == 0) {
        return 0;
    }

    // Додавання останнього елемента до суми попередніх
    return spending[N - 1] + calculateTotal(spending, N - 1);
}


// Пошук мінімальних витрат за день
void Min(int &min, const int spending[], int N) {
    min = spending[0];  // Початкове мінімальне значення

    // Перебір усіх елементів масиву
    for (int i = 1; i < N; i++) {
        if (min > spending[i]) {
            min = spending[i];
        }
    }
}


// Пошук максимальних витрат за день
void Max(int &max, const int spending[], int N) {
    max = spending[0];  // Початкове максимальне значення

    // Перебір усіх елементів масиву
    for (int i = 1; i < N; i++) {
        if (max < spending[i]) {
            max = spending[i];
        }
    }
}


// Виведення витрат за кожен день
void option1(const int spending[], int N) {
    cout << "День     Витрати, грн" << endl;

    // Виведення номера дня та відповідних витрат
    for (int i = 0; i < N; i++) {
        cout << setw(4) << (i + 1)
             << "           " << setw(7) << spending[i] << endl;
    }
}


// Виведення статистики витрат
void option2(const int spending[], int N, double budget) {
    int max, min;

    // Обчислення мінімальних і максимальних витрат
    Min(min, spending, N);
    Max(max, spending, N);

    cout << "Мінімальні витрати за день:       "
         << setw(7) << min << " грн" << endl;

    cout << "Максимальні витрати за день:      "
         << setw(7) << max << " грн" << endl;

    // Обчислення загальної суми витрат
    double total = calculateTotal(spending, N);

    cout << "Сумарні витрати:                  "
         << setw(7) << total << " грн" << endl;

    // Перевірка перевищення місячного бюджету
    if (total > budget) {
        double over = fabs(budget - total);

        cout << "Перевитрата понад бюджет:         "
             << setw(7) << over << " грн" << endl;
    }

    int days_pure = 0;  // Кількість днів із покупками
    double average = 0;  // Середні витрати за день із покупками

    // Підрахунок днів, коли були витрати
    for (int i = 0; i < N; i++) {
        if (spending[i] == 0) {
            continue;  // Пропуск днів без витрат
        }

        days_pure++;
    }

    cout << "Днів з покупками:                 "
         << days_pure << endl;

    // Обчислення середніх витрат за день із покупками
    if (days_pure == 0) {
        cout << "Середні витрати за такий день:    0.00 грн"
             << endl;
    } else {
        average = (double)total / days_pure;

        cout << "Середні витрати за такий день:    "
             << setw(7) << average << " грн" << endl;
    }

    int current_sum = 0;  // Накопичена сума витрат
    int i = 0;            // Лічильник днів

    // Визначення дня, коли витрати перевищили бюджет
    if (total > budget) {
        while (i < N) {
            current_sum += spending[i];
            i++;

            if (current_sum > budget) {
                cout << "Бюджет перевищено на дні " << i
                     << ", накопичено " << current_sum
                     << " грн." << endl;

                break;  // Завершення пошуку
            }
        }
    }
}


// Пошук днів, у які витрати перевищили денний ліміт
void option3(const int spending[], int N, int limit) {
    cout << "Ліміт: " << limit << " грн" << endl;

    int count = 0;  // Кількість днів із перевищенням ліміту

    // Перевірка витрат кожного дня
    for (int i = 0; i < N; i++) {
        if (spending[i] > limit) {
            cout << "День " << (i + 1)
                 << ": " << spending[i] << " грн" << endl;

            count++;
        }
    }

    // Виведення загальної кількості таких днів
    cout << "Разом днів з перевищенням: "
         << count << endl;
}


// Пошук трьох найбільших витрат
void option4(const int spending[], int N) {
    // Створення копії масиву, щоб не змінювати початкові дані
    int* temp = new int[N];

    for (int i = 0; i < N; i++) {
        temp[i] = spending[i];
    }

    // Сортування копії масиву за спаданням
    for (int i = 0; i < N - 1; i++) {
        int max_p = i;       // Індекс найбільшого елемента
        int max = temp[i];   // Поточне максимальне значення

        // Пошук найбільшого елемента в невідсортованій частині
        for (int j = i + 1; j < N; j++) {
            if (max < temp[j]) {
                max = temp[j];
                max_p = j;
            }
        }

        // Перестановка знайденого максимуму на поточну позицію
        max = temp[max_p];
        temp[max_p] = temp[i];
        temp[i] = max;
    }

    // Визначення кількості витрат для виведення
    int limit;

    if (N < 3) {
        limit = N;  // Якщо днів менше трьох, виводимо всі
    } else {
        limit = 3;  // Інакше виводимо три найбільші
    }

    cout << "Топ-" << limit << " витрат: ";

    // Виведення найбільших значень
    for (int i = 0; i < limit; i++) {
        cout << temp[i];

        if (i < limit - 1) {
            cout << ", ";
        }
    }

    cout << " грн" << endl;

    // Звільнення пам'яті копії масиву
    delete[] temp;
}


// Перевірка введення невід'ємного числа типу double
void validateInput(double &value) {
    while (true) {
        if (cin >> value && value >= 0) {
            break;  // Значення введено правильно
        } else {
            cout << "Помилка. Введіть коректне невід'ємне число або 0."
                 << endl;

            cin.clear();  // Скидання стану помилки

            // Очищення некоректного введення
            while (cin.get() != '\n');
        }
    }
}


// Перевірка введення невід'ємного цілого числа
void validateInput(int &value) {
    while (true) {
        if (cin >> value && value >= 0) {
            break;  // Значення введено правильно
        } else {
            cout << "Помилка. Введіть коректне невід'ємне ціле число."
                 << endl;

            cin.clear();  // Скидання стану помилки

            // Очищення некоректного введення
            while (cin.get() != '\n');
        }
    }
}