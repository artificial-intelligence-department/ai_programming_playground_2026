// Підключення бібліотек
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
// Оголошення функцій
void MinMaxSpending(double spending[], int N, double &minSpending, double &maxSpending, double budget);
double SumOfList(double array[], int N);
void ShowExceededDays(double array[], int N,double limit_by_default=1000.0);
void SortedSpending(double array[], int N);
void Top3Spending(double array[], int N);
void ShowExpenses(double spending[], int N);

int main() {
    // Оголошення змінних
    double budget, minSpending, maxSpending;
    int N, choice;
    double limit;
    // Введення даних користувачем, та їхня валідація
    BUDGET:
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    if(budget <= 0 || cin.fail()) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Бюджет повинен бути більше нуля.Або бути числом" << endl;
        goto BUDGET;
    }
    DAYS:
    cout << "Кількість днів обліку: ";
    cin >> N;
    if(N <= 0 || cin.fail()) {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << "Кількість днів обліку повинна бути більше нуля.Або бути числом" << endl;
        goto DAYS;
    }
    else if(N > 31) {
        cout << "Кількість днів обліку не може перевищувати 31." << endl;
        goto DAYS;
    }
    double spending[N] = {0};
    SPENDINGS:
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < N; i++) {
        cin >> spending[i];
        if(spending[i] < 0 || cin.fail()) {
            cin.clear();
            cin.ignore(100000, '\n');
            cout << "Витрати не можуть бути від'ємними.Або не бути числом" << endl;
            goto SPENDINGS;
        }
    }
    // Створення меню для користувача
    MENU:
    do {
        // Виведення меню та обробка вибору користувача
        cout << "\nВиберіть дію: " << endl;
        cout << "1. Вивести витрати по днях" << endl;
        cout << "2. Вивести деталі витрат" << endl;
        cout << "3. Вивести інформацію про ліміт бюджету" << endl;
        cout << "4. Вивести топ 3 дні з найбільшими витратами" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(100000, '\n');
            goto MENU;
        }
        // Визначення вводу користувача та виклик відповідних функцій
        switch (choice) {
            case 1: {
                ShowExpenses(spending, N);
                break;
            } 
            case 2: {
                MinMaxSpending(spending, N, minSpending, maxSpending, budget);
                break;
            }
            case 3: {
                LIMIT:                    
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                cin >> limit;
                if (limit < 0 || cin.fail()){
                    cout << "Ліміт не може бути від'ємним. Або не бути числом." << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    goto LIMIT;
                }
                else if(limit ==0 ){
                    ShowExceededDays(spending, N);
                }
                else {
                    ShowExceededDays(spending, N, limit);;
                } 
                break;
            }
            case 4: {
                Top3Spending(spending, N);
                break;
            }
            case 0: {
                cout << "Вихід з програми." << endl;
                break;
            }
            // Випадок некоректного вводу користувача, перехід до меню
            default: {
                cout << "Введено некоректне значення, спробуйте ще раз" << endl;
                goto MENU;
                break;
            }
        }
    // Перевірка умови для повторного виконання циклу, якщо користувач не обрав вихід
    } while (choice != 0);

    return 0;
}
// Функція для визначення мінімальних та максимальних витрат, а також перевірки бюджету
void MinMaxSpending(double spending[], int N, double &minSpending, double &maxSpending,double budget) {
    minSpending = spending[0];
    maxSpending = spending[0];
    for (int i = 0; i < N; i++) {
        if (minSpending > spending[i]) {
            minSpending = spending[i];
        }
        if (maxSpending < spending[i]) {
            maxSpending = spending[i];
        }
    }
    double total_spending = SumOfList(spending, N);
        
    cout << fixed << setprecision(2);
    cout << "Мінімальні витрати за день: " << minSpending << " грн." << endl;
    cout << "Максимальні витрати за день: " << maxSpending << " грн." << endl;
    cout << "Сумарні витрати: " << total_spending << " грн." << endl;
    if (budget - total_spending < 0) {
        cout << "Перевитрата понад бюджет: " << fabs(budget - total_spending) << " грн." << endl; 
    }
    cout << "Днів з покупками: ";
    int days_with_purchases = 0;
    double average_spending = 0.0;
    for (int i = 0; i < N; i++) {
        if (spending[i] <= 0) {
            continue;
        } else {
            average_spending += spending[i];
            days_with_purchases += 1;
        }
        }
    cout << days_with_purchases << endl;
    cout << "Середні витрати за такий день: " << average_spending / days_with_purchases << " грн." << endl;
    
    double money_spent = 0;
    int i = 0;
    bool limit_exceeded = false;
    while (i < N) {
    money_spent += spending[i];
    if (money_spent > budget) {
        limit_exceeded = true;
        break;
    }
    i++;
    }  
    if (limit_exceeded) {
                
        cout << "Бюджет вичерпано на дні: " << (i + 1) << ", накопичено: " << money_spent << " грн." << endl;
    } else {
        cout << "Бюджет не вичерпано, залишок: " << budget - money_spent << " грн." << endl;
    }
}
// Функція для виведення витрат по днях
void ShowExpenses(double spending[], int N) {
    cout << fixed << setprecision(2);
    cout << "День" << "\t" << "Витрати, грн" << endl;
    int day = 1;
    for (int i = 0; i < N; i++) {  
        cout << day << "\t" << spending[i] << endl;
        day += 1;
    }
}
// Функція для обчислення суми елементів масиву рекурсивно
double SumOfList(double array[], int N) {
    if (N <= 0){ 
        return 0;
    }
    return array[N - 1] +  SumOfList(array, N - 1);
}
// Функція для виведення днів, коли витрати перевищили ліміт
void ShowExceededDays(double array[], int N,double limit_by_default){   
    cout << fixed << setprecision(2);
    cout << "Ліміт: " << limit_by_default << " грн." << endl;
    
    int sum_of_days_limit_exceeded = 0;
    for (int i = 0; i < N; i++) {
        if (array[i] > limit_by_default) {
            cout << "  день " << (i + 1) << ": " << array[i] << " грн" << endl;
            sum_of_days_limit_exceeded++;
        }
    }
    cout << "Разом днів з перевищенням: " << sum_of_days_limit_exceeded << endl;
}
// Функція для виведення топ 3, або менше днів з найбільшими витратами
void Top3Spending(double array[], int N) {
    double copy_array[N] = {0};
    for (int i = 0; i < N; i++) {
        copy_array[i] = array[i];
    }
    double most_spending[3] = {0};
    SortedSpending(copy_array, N);
    int items_to_show = (N < 3) ? N : 3;
    cout << fixed << setprecision(2);
    if (items_to_show < 3) {
        if (N == 2)
        {
            cout << "Топ-" << items_to_show << " витрати: ";
            most_spending[0] = copy_array[0];
            most_spending[1] = copy_array[1];
            cout << most_spending[0] << ", " << most_spending[1] << " грн." << endl;
        }
        else if (N == 1)
        {
            cout << "Топ-" << items_to_show << " витрата: ";
            most_spending[0] = copy_array[0];
            cout << most_spending[0] << " грн." << endl;
        }
    } else {
        most_spending[0] = copy_array[0];
        most_spending[1] = copy_array[1];
        most_spending[2] = copy_array[2];
        cout << "Топ-3 витрати: " << most_spending[0] << ", " << most_spending[1] << ", " << most_spending[2] << " грн." << endl;
    }
}
// Функція для сортування масиву витрат за спаданням, використовуючи алгоритм бульбашкового сортування 
void SortedSpending(double array[], int N) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (array[j] < array[j+1]) {
                double temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}
