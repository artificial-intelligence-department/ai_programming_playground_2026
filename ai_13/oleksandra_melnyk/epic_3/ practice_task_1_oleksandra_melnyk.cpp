/*
Practice Task Мельник Олександра ШІ-13
*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>  
using namespace std;
//загальна сума витрат за допомогою рекурсії
double getSum(double arr[], int n) {
    if (n <= 0) return 0.0;
    return arr[n - 1] + getSum(arr, n - 1);
}
//функція для визначення максимально і мінімального значень витрат
int minmax(double arr[], int n, double &minarr, double &maxarr) {
    minarr = arr[0];
    maxarr = arr[0];
    for (int i = 0; i < n; i++) {
        if (minarr > arr[i]) {
            minarr = arr[i];
        }
        if (arr[i] > maxarr) {
            maxarr = arr[i];
        }
    }
    return 0;
}
//детальна статистика витрат
int showstat(double arr[], int n, double budget) {
    //викликаємо функцію для отримання мінімуму і максимуму
    double mymin = 0;
    double mymax = 0;
    minmax(arr, n, mymin, mymax);
    
    cout << "Мінімум: " << mymin << "  Максимум: " << mymax << endl;
    //отримуємо загальну суму витрат 
    double total = getSum(arr, n);
    cout << "Сума: " << total << endl;
    //перевірка на перевитрати
    if (total>budget)
    {
        cout<<"Перевитрата: "<<abs(budget-total)<<" грн"<<endl;
    }
    //перевірка днів коли були покупки
    int days=0;
    for (int i=0; i<n; i++)
    {
        if (arr[i]==0)
        {
            continue;
        }
        days++;
    }
    cout << "Днів з покупками: " << days << endl;
    //рахуємо середню суму витрат коли були покупки
    if (days>0)
    {
        cout<<"Середні витрати: "<<total/days<<" грн"<<endl;
    }
    double currentsum = 0;
    int index = 0;
    //змінна для зберігання днів коли був вичерпано бюджет
    int exhaustedDay = -1; 
    //для визначення дня коли були вичерпано бюджет
    while (index < n) {
        currentsum += arr[index];
        if (currentsum > budget) {
            exhaustedDay = index + 1; 
            break;                   
        }
        index++;
    }
    if (exhaustedDay != -1) {
        cout << "Бюджет вичерпано на дні " << exhaustedDay << ", накопичено " << currentsum << " грн" << endl;
    } else {
        cout << "Грошей вистачило на всі дні. Залишок: " << budget - total << " грн" << endl;
    } 
    return 0;

}
//функція для виведення щоденних витрат
int showspending(double arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " " << arr[i] << endl;
    }
    return 0;
}
//функція для виведення днів з перевищенням ліміту
int showlimit(double arr[], int n, double limit = 1000) {  
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > limit) {
            count++;
            cout << "день:" << i + 1 << " " << arr[i] << "грн" << endl;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
    return 0;
}
//функція для виведення найбільш перевищених днів по ліміту
int showmax(double arr[], int n) {
    //копія масиву 
    double copyArr[n];
    for (int i = 0; i < n; i++) {
        copyArr[i] = arr[i];
    }
    //сортування (метод бульбашки)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (copyArr[j] > copyArr[i]) {
                double temp = copyArr[i];
                copyArr[i] = copyArr[j];
                copyArr[j] = temp;
            }
        }
    }
    cout << "Топ-3 витрат: ";
    for (int i = 0; i < 3; i++) {
        cout << copyArr[i] << " грн ";
    }
    cout << endl;
    return 0;
}
int main() 
{
    //формат виведення 2 знаки після коми 
    cout << fixed << setprecision(2); 
    double budget;
    int N;
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    //перевірка на коректність вводу всіх змінних
    if (cin.fail() || budget < 0) {
        cout << "Помилка: бюджет не може бути від'ємним!" << endl;
        return 1;
    }
    cout << "Кількість днів обліку: ";
    cin >> N;
    if (cin.fail() || N <= 0 || N > 31) { 
        cout << "Помилка: невірна кількість днів!" << endl;
        return 1;
    }
    //витрати щоденні масивом
    double spending[N];
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < N; i++) {
        cin >> spending[i];
        if (cin.fail() || spending[i] < 0) {  
            cout << "Помилка: витрати не можуть бути від'ємними!" << endl;
            return 1;
        }
    }
    int choice;
//мітка для повернення у разі некоректного вводу
menu_start:
    if (cin.fail()) {
        cin.clear(); 
        string dummy;
        cin >> dummy; 
    }
    do {
        cout << "--- Меню ---" << endl;
        cout << "1 Показати витрати по днях" << endl;
        cout << "2 Статистика витрат" << endl;
        cout << "3 Дні з перевищенням денного ліміту" << endl;
        cout << "4 Три найдорожчі дні" << endl;
        cout << "0 Вийти" << endl;
        cout << "Ваш вибір: ";
        //перевірка на коректність вводу меню
        if (!(cin >> choice)) {
            cout << "Помилка вводу! Спробуйте ще раз." << endl;
            goto menu_start; 
        }

        if (choice == 1) {
            showspending(spending, N);
        } else if (choice == 2) {
            showstat(spending, N, budget);
        } else if (choice == 3) {
            double limit;
            cout << "Введіть ліміт: ";
            if (!(cin >> limit)) {
                cout << "Помилка вводу ліміту!" << endl;
                goto menu_start;
            }
            if (limit < 0) { 
                cout << "Помилка: ліміт не може бути від'ємним!" << endl;
                goto menu_start;
            }
            if (limit == 0) {
                showlimit(spending, N);
            } else {
                showlimit(spending, N, limit);
            }
        } else if (choice == 4) {
            showmax(spending, N);
        } else if (choice == 0) {
            cout << "Вихід..." << endl;
        } else {
            cout << "Неправильний пункт меню!" << endl;
            goto menu_start;
        }
    } while (choice != 0);
    return 0;
}