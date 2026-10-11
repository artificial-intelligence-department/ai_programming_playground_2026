
/*
    Class Practice Work, Олексій Рубаха, ШІ-13
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

// Функція для обчислення суми витрат за всі дні
int countSum(int expenses[], int days){
    // Базовий випадок: якщо днів немає, повертаємо 0
    if (days == 0) {
        return 0;
    }

    // Рекурсивно обчислюємо суму витрат, додаючи витрати за поточний день до суми попередніх днів
    return countSum(expenses, days - 1) + expenses[days - 1];
}

// Функція для виведення таблиці витрат по днях
void expensesTable(int expenses[], int days){
    cout << "День     Витрати, грн" << endl;

    // Проходимо по всіх днях і виводимо номер дня та відповідні витрати
    for (int i = 0; i < days; i++){
        cout << fixed << setprecision(2) << setw(3) << i + 1 
        << setw(10) << double(expenses[i]) << endl;
    }
}

// Функція для обчислення статистики витрат
void expensesStats(int expenses[], int days, int budget, int& min, int& max){
    int overlimit = 0; // Змінна для зберігання перевитрати бюджету
    double average = 0; // Змінна для зберігання середніх витрат за день
    double sum = countSum(expenses, days); // сума витрат за всі дні
    int spendDays = 0; // Лічильник днів з покупками
    int runOutDay = 0; // Змінна для зберігання дня, коли бюджет вичерпано
    double remaining = budget - sum; // Змінна для зберігання залишку бюджету після витрат

    min = expenses[0];
    max = expenses[0];

    // Якщо залишок бюджету від'ємний, обчислюємо перевитрату
    if (remaining < 0)
        overlimit = abs(remaining);

    double shoppingSum = 0;

    // Проходимо по всіх днях і обчислюємо мінімальні та максимальні витрати, 
    // суму витрат та кількість днів з покупками
    for (int i = 0; i < days; i++){
        // Оновлюємо максимальні витрати, якщо поточні витрати більші за поточний максимум
        if (expenses[i] > max){
            max = expenses[i];
        }

        // Оновлюємо мінімальні витрати, якщо поточні витрати менші за поточний мінімум
        if (expenses[i] < min){
            min = expenses[i];
        }

        // Пропускаємо дні без витрат
        if (expenses[i] == 0){
            continue;
        }

        shoppingSum += expenses[i]; // Додаємо витрати за день до загальної суми витрат
        spendDays++; // Збільшуємо лічильник днів з покупками
    }

    // Обчислюємо середні витрати за день, якщо були дні з покупками
    if (spendDays > 0){
        average = shoppingSum / spendDays;
    }

    int i = 0;
    double spends = 0;

    // Проходимо по всіх днях і обчислюємо день, коли бюджет вичерпано
    while (i < days){
        spends += expenses[i];

        if (spends > budget){
            runOutDay = i + 1;
            break;
        }
        i++;
    }

    // Виводимо статистику витрат
    cout << fixed << setprecision(2) << "Мінімальні витрати за день:       " 
    << double(min) << " грн" << endl;

    cout << fixed << setprecision(2) << "Максимальні витрати за день:      " 
    << double(max) << " грн" << endl;

    cout << fixed << setprecision(2) << "Сумарні витрати:                  " 
    << sum << " грн" << endl;

    // Виводимо залишок бюджету або перевитрату, залежно від того, чи залишок від'ємний
    if (remaining < 0){
        cout << fixed << setprecision(2) << "Перевитрата понад бюджет:         " 
        << overlimit << " грн" << endl;
    }else{
        cout << fixed << setprecision(2) << "Залишок бюджету:                  " 
        << remaining << " грн" << endl;
    }

    cout << "Днів з покупками:                  " << spendDays << endl;
    cout << fixed << setprecision(2) << "Середні витрати за такий день:     " 
    << average << " грн" << endl;

    // Виводимо день, коли бюджет вичерпано, або повідомляємо, що бюджету вистачило на всі дні
    if (runOutDay > 0){
        cout << fixed << setprecision(2)
             << "Бюджет вичерпано на дні " << runOutDay
             << ", накопичено " << spends << " грн." << endl;
    }else{
        cout << fixed << setprecision(2)
             << "Бюджету вистачило на всі дні. Залишок: "
             << remaining << " грн" << endl;
    }
}

// Функція для виведення днів, коли витрати перевищили денний ліміт
void overlimit(int expenses[], int days, int defLimit = 1000){
    int limit;

    // Запитуємо користувача про денний ліміт витрат
    do {
        cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
        cin >> limit;
        // Перевіряємо, чи введене значення є від'ємним
        if (limit < 0) {
            cout << "Ліміт не може бути від'ємним." << endl;
        }
    } while (limit < 0);

    // Якщо користувач не ввів ліміт (0), використовуємо значення за замовчуванням
    if (limit == 0)
        limit = defLimit;

    int overlimitDays = 0; // Лічильник днів, коли витрати перевищили ліміт
    cout << fixed << setprecision(2) << "Ліміт: " << double(limit) << " грн" << endl;

    // Проходимо по всіх днях і виводимо дні, коли витрати перевищили ліміт
    for (int i = 0; i < days; i++){
        if (expenses[i] > limit){
            cout << fixed << setprecision(2) << "День " << i + 1 << ": " 
            << double(expenses[i]) << " грн" << endl;

            overlimitDays++;
        }
    }

    cout << "Разом днів з перевищенням: " << overlimitDays << endl;
}

// Функція для виведення трьох найбільших витрат за місяць
void topThree(int expenses[], int days){
    int sorted[31], buffer; // Масив для зберігання відсортованих витрат та буферна змінна для обміну значень

    // Копіюємо витрати у масив sorted для сортування
    for (int i = 0; i < days; i++){
        sorted[i] = expenses[i];
    }

    // Сортуємо масив sorted у порядку спадання за допомогою алгоритму бульбашки
    for (int i = 0; i < days - 1; i++){
        for (int j = 0; j < days - 1 - i; j++){
            if (sorted[j] < sorted[j + 1]){
                buffer = sorted[j + 1];
                sorted[j + 1] = sorted[j];
                sorted[j] = buffer;
            }
        }
    }

    int topCount = days; // Кількість днів, які будуть виведені (максимум 3)

    // Якщо кількість днів менша за 3, виводимо всі дні, інакше обмежуємо вивід до 3 днів
    if (topCount > 3){
        topCount = 3;
    }

    // Виводимо трійку найбільших витрат за місяць
    cout << fixed << setprecision(2) << "Топ-" << topCount << " витрат: ";
    // Проходимо по відсортованому масиву та виводимо витрати у порядку спадання
    for (int i = 0; i < topCount; i++){
        cout << double(sorted[i]);

        // Додаємо кому після кожної витрати, крім останньої
        if (i < topCount - 1){
            cout << ", ";
        }
    }

    cout << " грн" << endl;
}

int main(){
    int budget, days;

    // Запитуємо користувача про бюджет на місяць та кількість днів обліку
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    if (budget < 0){
            cout << "Бюджет не може бути від'ємним. Введіть невід'ємне число: ";
            cin >> budget;
    }

    // Запитуємо користувача про кількість днів обліку та перевіряємо, 
    // чи введене значення знаходиться в допустимому діапазоні
    cout << "Кількість днів обліку: ";
    cin >> days;
    if (days < 1 || days > 31){
        cout << "Кількість днів повинна бути від 1 до 31. Введіть коректне число: ";
        cin >> days;
    }

    int expenses[31];

    // Запитуємо користувача про витрати по днях та перевіряємо, 
    // чи введене значення є невід'ємним числом
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < days; i++){
        cin >> expenses[i];
        if (expenses[i] < 0) {
            cout << "Витрати не можуть бути від'ємними. Введіть невід'ємне число: ";
            cin >> expenses[i];
        }
    }

    int choice;
    int min = expenses[0];
    int max = expenses[0];


    // Головне меню програми, яке дозволяє користувачу обирати різні операції
    do{
        menu:
        cout << endl << "Пункт    Операція" << endl;
        cout << "1        Показати витрати по днях" << endl;
        cout << "2        Статистика витрат" << endl;
        cout << "3        Дні з перевищенням денного ліміту" << endl;
        cout << "4        Три найдорожчі дні" << endl;
        cout << "0        Вийти" << endl;
        cout << "Пункт: ";

        // Перевіряємо, чи введене значення є числом, і якщо ні, 
        // очищаємо потік вводу та виводимо повідомлення про помилку
        if (!(cin >> choice)){
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка! Введіть номер пункту меню." << endl;
            goto menu;
        }

        cout << endl;

        // Перевіряємо, чи введене значення знаходиться в допустимому діапазоні
        if (choice < 0 || choice > 4){
            cout << "Неправильний пункт меню!" << endl;
            goto menu;
        }

        // Виконуємо відповідну операцію залежно від вибору користувача
        switch (choice){
            case 1:
                expensesTable(expenses, days);
                break;

            case 2:
                expensesStats(expenses, days, budget, min, max);
                break;

            case 3:
                overlimit(expenses, days);
                break;

            case 4:
                topThree(expenses, days);
                break;

            case 0:
                cout << "Вихід..." << endl;
                break;
        }
    }while(choice != 0);

    return 0;
}