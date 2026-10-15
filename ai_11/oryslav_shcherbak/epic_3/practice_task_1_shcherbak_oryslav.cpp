#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
using namespace std;


/* Задача: Practice task 1
* Щербак Орислав
* Група ШІ - 11
*/

const int max_days = 31;
void findminmax(double spending[], int n, double &min_spending, double &max_spending){
    // перший день вважаємо і мінімумом, і максимумом
    min_spending = spending[0];
    max_spending = spending[0];
    // перевіряємо всі наступні дні
    for (int i = 1; i < n; ++i){
        if (spending[i] < min_spending){
            // знайшли новий мінімум
            min_spending = spending[i];
        }
        if (spending[i] > max_spending){
            // знайшли новий максимум
            max_spending = spending[i];
        }
    }
}
double totalspending(const double spending[], int n){
    // якщо днів більше немає, сума дорівнює нулю
    if (n == 0){
        return 0;
    }
    // додаємо витрати останнього дня до суми попередніх днів
    return spending[n - 1] + totalspending(spending, n - 1);
}
void countdays(double spending[], int n, int &count){
    // на початку днів з витратами немає
    count = 0;
    // перевіряємо кожен день
    for (int i = 0; i < n; ++i){
        if (spending[i] <= 0){
            // пропускаємо день без покупок
            continue;
        }
        // якщо витрати більше нуля, рахуємо день
        count++;
    }
}
void showspending(double spending[], int n){
    // показуємо витрати по днях
    for(int i = 0; i < n; ++i){
        cout << "День " << (i + 1) << ": " << spending[i] << " грн" << endl;
    }
}
void showstatistics(double spending[], int n, double budget){
    double min_spending, max_spending;
    findminmax(spending, n, min_spending, max_spending);
    // виводимо мінімальні та максимальні витрати
    cout << "Мінімальні витрати: " << min_spending << " грн" << endl;
    cout << "Максимальні витрати: " << max_spending << " грн" << endl;
    // рахуємо суму всіх витрат
    double total_spending = totalspending(spending, n);
    // виводимо суму всіх витрат
    cout << "Сумарні витрати: " << total_spending << " грн" << endl;
    // рахуємо різницю між витратами та бюджетом
    double difference = total_spending - budget;
    // порівнюємо витрати з бюджетом
    if (difference > 0) {
        cout << "Перевитрата понад бюджет: " << fabs(difference) << " грн" << endl;
    } else {    
        cout << "Залишок бюджету: " << fabs(difference) << " грн" << endl;
    }   
    int count = 0;
    countdays(spending, n, count);
    // виводимо кількість днів з витратами
    cout << "Кількість днів з витратами: " << count << endl;
    // рахуємо середні витрати за день з витратами
    if (count > 0) {
        cout << "Середні витрати за такий день: " << (total_spending / count) << " грн" << endl;
    } else {
        cout << "Середні витрати за такий день: 0 грн" << endl;
    }
    double accumulated = 0;
    int day = 0;
    bool exceeded = false;
    // накопичуємо витрати день за днем, доки не буде вичерпано бюджет
    while (day < n) {
        accumulated += spending[day];
        if (accumulated > budget) {
            cout << "Бюджет вичерпано на дні " << (day + 1) << ", накопичено " << accumulated << " грн" << endl;
            exceeded = true;
            // зупиняємо цикл одразу на дні перевищення
            break; 
        }
        ++day;
    }
    // якщо бюджет не перевищено
    if (!exceeded) {
        cout << "Бюджет не перевищено протягом усього періоду. Залишок бюджету: " << (budget - accumulated) << " грн" << endl;
    }
}
void showdaysoverlimit(double spending[], int n, double daybudget = 1000){
    int countlimit = 0;
    cout << "Ліміт: " << daybudget << " грн" << endl;
    // перевіряємо кожен день
    for (int i = 0; i < n; ++i) {
        if (spending[i] > daybudget) {
            // якщо витрати більше ліміту, рахуємо день
            countlimit++;
            cout << "День " << (i + 1) << ": " << spending[i] << " грн" << endl;
        }
    }
    cout << "Кількість днів з перевищенням денного ліміту: " << countlimit << endl;
}
void showthreemostexpensivedays(double spending[], int n){
    double copy[max_days];
    int index[max_days];
    // робимо копію масиву, щоб не змінювати оригінал
    for (int i = 0; i < n; ++i){
        copy[i] = spending[i];
        index[i] = i;
    }
    // сортуємо копію масиву за спаданням вкладеними циклами
    for (int i = 0; i < n - 1; ++i){
        for (int j = 0; j < n - 1 - i; ++j){
            if (copy[j] < copy[j + 1]){
                // міняємо місцями витрати
                double temp_spending = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp_spending;
                // міняємо місцями номери днів
                int temp_index = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp_index;
            }
        }
    }
    cout << "Три найдорожчі дні: " << endl;
    // виводимо три найдорожчі дні
    for (int i = 0; i < 3 && i < n; ++i){
        cout << "День " << (index[i] + 1) << ": " << copy[i] << " грн" << endl;
    }
}
int main(){
    double budget;
    int n;
    double spending[max_days];
    // вводимо бюджет і перевіряємо його
    while(true){
        cout << "Бюджет на місяць (грн): ";
        if(cin >> budget && budget >= 0){
            break;
        }
        cout << "Помилка: бюджет не може бути від'ємним.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // вводимо кількість днів і перевіряємо її
    while(true){
        cout << "Кількість днів в обліку (1-" << max_days << "): ";
        if(cin >> n && n >= 1 && n <= max_days){
            break;
        }
        cout << "Помилка: введіть ціле число від 1 до " << max_days << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // вводимо витрати за кожен день
    for (int i = 0; i < n; ++i){
        while(true){    
            cout << "Витрати за день " << (i + 1) << " (грн): ";
            if(cin >> spending[i] && spending[i] >= 0){
                break;
            }
            cout << "Помилка: витрати не можуть бути від'ємними.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    int choice;
    do {
        menu:
        // показуємо меню
        cout << "1. Показати витрати по днях" << endl;
        cout << "2. Статистика витрат" << endl;
        cout << "3. Дні з перевищенням денного ліміту" << endl;
        cout << "4. Три найдорожчі дні" << endl;
        cout << "0. Вихід" << endl;
        // якщо ввели не число, просимо ввести знову
        if (!(cin >> choice)) {
            cout << "Помилка: введіть номер пункту." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto menu;
        }
        switch (choice){
        case 1:
            // показуємо витрати по днях
            showspending(spending, n);
            break;
        case 2:
            // Статистика витрат
            showstatistics(spending, n, budget);
            break;
        case 3: {
            double daybudget;
            // вводимо денний ліміт і перевіряємо його
            while(true){
                cout << "Денний ліміт (грн, 0 = за замовчуванням 1000): ";
                if(cin >> daybudget && daybudget >= 0){
                    break;
                }
                cout << "Помилка: денний ліміт не може бути від'ємним.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            // якщо ввели 0, ставимо ліміт 1000
            if(daybudget == 0){
                daybudget = 1000;
            }
            // показуємо дні з перевищенням ліміту
            showdaysoverlimit(spending, n, daybudget);
            break;
        }
        case 4:
            // показуємо три найдорожчі дні
            showthreemostexpensivedays(spending, n);
            break;
        case 0:
            // вихід з програми
            cout << "Роботу завершено." << endl;
            break;
        default:
            // якщо ввели неправильний номер
            cout << "Помилка: введіть номер пункту." << endl;
            goto menu;
        }
    } while (choice != 0);
    return 0;
}