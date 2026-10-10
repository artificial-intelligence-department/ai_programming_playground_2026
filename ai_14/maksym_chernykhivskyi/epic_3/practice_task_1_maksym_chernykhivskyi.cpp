/*Epic 3 - Аналізатор місячного бюджету
Чернихівський Максим
Ші - 14*/

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <climits>

using namespace std;

// Прототипи функцій
void showExpenses(const int spending[], int N);
void getMinMax(const int spending[], int N, int &minVal, int &maxVal);
int calculateTotal(const int spending[], int N);
void showStatistics(const int spending[], int N, double budget);
void checkDailyLimit(const int spending[], int N, double limit = 1000);
void showTopThree(const int spending[], int N);
void validateInput(double &value, const string &prompt);
void validateInput(int &value, const string &prompt);

int main(){
    cout << fixed << setprecision(2); // Вивід чисел з 2 знаками після коми

    double budget;
    int N;
    // Ввід та валідація даних
    cout << "=== Аналізатор місячного бюджету ===" << endl;

    validateInput(budget, "Бюджет на місяць (грн): ");

    do {
        validateInput(N, "Кількість днів обліку: ");
        if (N < 1 || N > 31){
            cout << "Помилка. Кількість днів має бути від 1 до 31." << endl;
        }
    } while (N < 1 || N > 31);

    int* spending = new int [N]; // Динамічний масив витрат

    cout << "Витрати по днях (грн): ";

    // Зчитування витрат за кожен день з валідацією
    for (int i = 0; i < N; i++) {
        validateInput(spending[i], "");
    }

    int choice;
    // Мітка для goto
    MENU:

    do {
        // Вивід меню
        cout << "\n-----------------------------------" << endl;
        cout << "МЕНЮ:" << endl;
        cout << "1 - Показати витрати по днях" << endl;
        cout << "2 - Статистика витрат" << endl;
        cout << "3 - Дні з перевищенням денного ліміту" << endl;
        cout << "4 - Три найдорожчі дні" << endl;
        cout << "0 - Вийти" << endl;
        cout << "Ваш вибір: ";

        // Перевірка на нечисловий ввід
        if (!(cin >> choice)){
            cout << "Помилка, введіть числове значення від 0 до 4" << endl;
            cin.clear();                  // Скидання стану помилки потоку
            while (cin.get() != '\n');    // Очищення буфера вводу
            goto MENU;                    // Повернення до меню
        }

        // Перевірка діапазону пункту меню
        if (choice < 0 || choice > 4){
            cout << "Помилка, неправильний пункт меню, введіть числове значення від 0 до 4" << endl;
            goto MENU;
        }

        // Виклик функції відповідно до вибору
        if (choice == 1){
            showExpenses(spending, N);
        }
        else if (choice == 2){
            showStatistics(spending, N, budget);
        }
        else if (choice == 3){
            double user_limit;
            cout << "Денний ліміт (грн, 0 = за замовчуванням): ";

            // Некоректний або від'ємний ліміт трактується як 0
            if (!(cin >> user_limit) || user_limit < 0){
                cin.clear();
                while (cin.get() != '\n');
                user_limit = 0;
            }
            // 0 означає ліміт за замовчуванням (1000 грн)
            if (user_limit == 0){
                checkDailyLimit(spending, N);
            } else {
                checkDailyLimit(spending, N, user_limit);
            }
        }
        else if (choice == 4) {
            showTopThree(spending, N);
        }

    } while (choice != 0); // Працюємо, доки не обрано вихід

    if (choice == 0){
        delete[] spending; // Звільнення пам'яті
        return 0;
    }
}

// Виводить таблицю "день - витрати"
void showExpenses(const int spending[], int N){
    cout << "День     Витрати, грн" << endl;

    for (int i = 0; i < N; i++){
        // Вирівнювання за допомогою setw() з бібліотеки <iomanip>
        cout << setw(4) << (i + 1) << "           " << setw(7) << (double)spending[i] << endl;
    }
}

// Знаходить мінімум і максимум (повертає через параметри-посилання)
void getMinMax(const int spending[], int N, int &minVal, int &maxVal){
    minVal = spending[0];
    maxVal = spending[0];

    for (int i = 1; i < N; i++){
        if (spending[i] < minVal){
            minVal = spending[i];
        }
        if (spending[i] > maxVal){
            maxVal = spending[i];
        }
    }
}

// Рекурсивно рахує суму витрат
int calculateTotal(const int spending[], int N){
    if (N == 0){ // Базовий випадок
        return 0;
    }
    return spending[N - 1] + calculateTotal(spending, N - 1);
}

// Виводить статистику витрат
void showStatistics(const int spending[], int N, double budget){

    // Мінімум і максимум за день
    int minVal, maxVal;
    getMinMax(spending, N, minVal, maxVal);

    cout << "Мінімальні витрати за день:       " << setw(7) << (double)minVal << " грн" << endl;
    cout << "Максимальні витрати за день:      " << setw(7) << (double)maxVal << " грн" << endl;

    // Загальна сума
    int total = calculateTotal(spending, N);
    cout << "Сумарні витрати:                  " << setw(7) << (double)total << " грн" << endl;

    // Перевитрата (через fabs) або залишок бюджету
    if (total > budget){
        double over = fabs(budget - total);
        cout << "Перевитрата понад бюджет:         " << setw(7) << (double)over << " грн" << endl;
    } else {
        double rem = budget - total;
        cout << "Залишок бюджету:                  " << setw(7) << (double)rem << " грн" << endl;
    }

    // Обчислення середнього значення (оператор continue)
    int sum_pure = 0;   // Сума лише по днях з покупками
    int days_pure = 0;  // Кількість днів з покупками

    for(int i = 0; i < N; i++){
        if (spending[i] == 0){
            continue; // Пропускаємо дні без покупок
        }
        sum_pure += spending[i];
        days_pure++;
    }
     cout << "Днів з покупками:                " << (int)days_pure << endl;

     // Захист від ділення на нуль
     if (days_pure > 0){
        double average = (double)sum_pure / days_pure;
        cout << "Середні витрати за такий день:    " << setw(7) << (double)average << " грн" << endl;
     } else {
        cout << "Середні витрати за такий день:    0.00 грн" << endl;
     }

    // Пошук дня вичерпання бюджету
    int current_sum = 0;
    int i = 0;
    if (total > budget){
        while (i < N){
            current_sum += spending[i]; // Накопичуємо витрати
            if (current_sum > budget){
                cout << "Бюджет вичерпано на дні " << (i + 1) << ", накопичено " << (double)current_sum << " грн." << endl;
                break; // Зупиняємось одразу, як бюджет перевищено
            }
            i++;
        }
    } else {
        cout << "Бюджету вистачило на всі дні обліку." << endl;
    }
}

// Виводить дні, у які витрати перевищили ліміт
void checkDailyLimit(const int spending[], int N, double limit){
    cout << "Ліміт: " << limit << " грн" << endl;

    int count = 0; // Лічильник днів з перевищенням
    for (int i = 0; i < N; i++){
        if (spending[i] > limit){
            cout << "  день " << (i + 1) << ": " << (double)spending[i] << " грн" << endl;
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}

// Виводить три найбільші витрати
void showTopThree(const int spending[], int N){
    // Копія масиву, щоб не змінювати оригінал
    int* temp = new int[N];
    for (int i = 0; i < N; i++){
        temp[i] = spending[i];
    }
    // Сортування вкладеними циклами (за спаданням)
    for (int i = 0; i < N - 1; i++){
        for (int j = i + 1; j < N; j++){
            if (temp[i] < temp[j]){
                // Обмін елементів місцями
                int placeholder = temp[i];
                temp[i] = temp[j];
                temp[j] = placeholder;
            }
        }
    }

    // Якщо днів менше трьох — виводимо скільки є
    int limit;
    if (N < 3){
        limit = N;
    } else {
        limit = 3;
    }

    cout << "Топ-" << limit << " витрат: ";
    for (int i = 0; i < limit; i++){
        cout << (double)temp[i];
        if (i < (limit - 1)){
            cout << ", "; // Роздільник між значеннями
        }
    }
    cout << " грн" << endl;
    delete[] temp; // Звільнення пам'яті копії
    
}

// Валідація дробового числа (не менше 0)
void validateInput(double &value, const string &prompt){
    while (true){
        cout << prompt;
        if (cin >> value && value >= 0){
            break;
        } else {
            cout << "Помилка. Введіть коректне додатне число або 0." << endl;
            cin.clear();                // Скидання помилки потоку
            while (cin.get() != '\n');  // Очищення буфера
        }
    }
}

// Валідація цілого числа (не менше 0)
void validateInput(int &value, const string &prompt){
    while (true){
        cout << prompt;
        if (cin >> value && value >= 0){
            break;
        } else {
            cout << "Помилка. Введіть ціле число від 0 і більше." << endl;
            cin.clear();
            while (cin.get() != '\n');
        }
    }
}