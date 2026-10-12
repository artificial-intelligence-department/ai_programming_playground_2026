/* 
    Class Practice task 
    Соломія Королюк 
    ШІ-13
*/

#include <iostream>
#include <iomanip>
#include <cmath> 

using namespace std;

void expansesTable(float arr[], int n); // Прототип функції для виведення таблиці витрат
void expansesMinMax(float arr[], int n, float &min_exp, float &max_exp); // Прототип функції для пошуку максимальної та мінімальної витрати за день
float totalSum(float arr[], int n); //Прототип функції для пошуку сумарних витрат 
void averageSpendings(float arr[], int n, float &average_spendings, int &c); // Прототип функції обчислення середніх витрат 
void checkBudgetExceeded(float arr[], int n, float budget); // Прототип функції перевірки дня, коли бюджет вичерпано
void checkDailyLimit(float arr[], int n, float limit = 1000.0f); // Прототип функції перевірки днів з перевищенням денного ліміту
void printTop3Days(const float arr[], int n); // Прототип функції для пошуку трьох найдорожчих днів 
void showStatistics(float arr[], int n, float budget); // Прототип функції пункту меню "Статистика витрат"
void dailyLimitMenu(float arr[], int n); // Прототип функції пункту меню "Денний ліміт"

int main(){

    float budget;
    int N;

    cout << fixed << setprecision(2);
    
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    if (cin.fail() || budget <= 0 ) {
        cout << "Бюджет має бути додатнім числом";
        return 1;
    }

    cout << "Кількість днів обліку: "; 
    cin >> N;
    if (cin.fail() || N < 1 || N > 31){
        cout << "Кількість днів має бути цілим числом від 1 до 31";
        return 1;
    }

    float spending[N];

    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < N; i++){
        cin >> spending[i];

        if (cin.fail() || spending[i] < 0){
            cout << " Витрати мають бути невід'ємними числами";
            return 1;
        }
    }

    int choice;

    do {
    menu: // мітка, на яку повертає goto
        cout << "\n===== МЕНЮ =====" << endl;
        cout << "1. Показати витрати по днях" << endl;
        cout << "2. Статистика витрат" << endl;
        cout << "3. Дні з перевищенням денного ліміту" << endl;
        cout << "4. Три найдорожчі дні" << endl;
        cout << "0. Вихід" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        if (cin.eof() && cin.fail()) return 0; // введення закінчилось

        // Якщо нечислове введення (або зайві символи після числа), то назад до меню
        if (cin.fail() || (cin.peek() != '\n' && !cin.eof())) {
            cin.clear();               // скидаємо помилку
            cin.ignore(10000, '\n');   // викидаємо неправильні символи, щоб не було зациклення
            cout << "Помилка: введіть число від 0 до 4" << endl;
            goto menu;
        }

        // Якщо введено неіснуючий пункт меню, то назад до меню
        if (choice < 0 || choice > 4) {
            cout << "Помилка: такого пункту меню немає" << endl;
            goto menu;
        }

        switch (choice) {
            case 1: expansesTable(spending, N); break;
            case 2: showStatistics(spending, N, budget); break;
            case 3: dailyLimitMenu(spending, N); break;
            case 4: printTop3Days(spending, N); break;
            case 0: cout << "Ви здійснили вихід." << endl; break;
        }

    } while (choice != 0);

    return 0;
}

//Функція для виконання пункту 1: Показати витрати по днях
void expansesTable(float arr[], int n){

    cout << "\n";
    cout << "День" << "     " << "Витрати, грн" << endl;

    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++){
        cout << setw(4) << i+1 << setw(17) << arr[i] << endl;
    }

}

//Функції для виконання пункту 2: Статистика витрат 
void showStatistics(float arr[], int n, float budget){

    //Вивід мінімальних та максимальних витрат за день
    float min_exp, max_exp;
    expansesMinMax(arr, n, min_exp, max_exp);

    cout << "\nМінімальні витрати за день:" << setw(11) << min_exp << " грн" << endl; 
    cout << "Максимальні витрати за день:" << setw(10) << max_exp << " грн" << endl;

    // Вивід загальних витрат
    float total_spending = totalSum(arr, n);
    cout << "Сумарні витрати:" << setw(22) << total_spending << " грн" << endl;

    //Перевірка залишку бюджету 
    float remaining = budget - total_spending;

    if (remaining < 0) {
        float overspend = fabs(remaining); // модуль від'ємного залишку
        cout << "Перевитрата понад бюджет:" << setw(13) << overspend << " грн" << endl;
    } else {
        cout << "Залишок бюджету:" << setw(22) << remaining << " грн" << endl;
    }

    //Обчислення середніх витрат за дні з покупками
    float average_spendings;
    int c;
    averageSpendings(arr, n, average_spendings, c);

    cout << "Днів з покупками:" << setw(21) << c << endl;
    cout << "Середні витрати за такий день:" << setw(8) << average_spendings << " грн" << endl;

    //Перевірка дня, коли бюджет вичерпано
    checkBudgetExceeded(arr, n, budget);
}

//Пошук мін та мак витраченої суми за день 
void expansesMinMax(float arr[], int n, float &min_exp, float &max_exp){
    min_exp = arr[0];
    max_exp = arr[0];

    for (int i = 0; i < n; i++){
        if (arr[i] > max_exp) max_exp = arr[i];
        if (arr[i] < min_exp) min_exp = arr[i];
    }
}

//Обчислення сумарних витрат рекурсивно 
float totalSum(float arr[], int n){
    if (n <= 0) return 0;

    return arr[n - 1] + totalSum(arr, n - 1);
}

//Обчислення середніх витрат за дні з покупками
void averageSpendings(float arr[], int n, float &average_spendings, int &c){

    float total_sum = totalSum(arr, n);

    c = 0;
    for (int i = 0; i < n; i++){
        if (arr[i] == 0 ) continue;
        else c++;
    }
    if (c == 0) average_spendings = 0.0;
    else average_spendings = total_sum / c;
    
}

// Перевірка дня, коли бюджет вичерпано
void checkBudgetExceeded(float arr[], int n, float budget){

    float accumulated = 0;
    int day_exceeded = -1; // означає не перевищено 

    int i = 0;
    while (i < n){

        accumulated += arr[i];

        if (accumulated > budget){
            day_exceeded = i+1;
            break;
        }
        i++;
    }

    if (day_exceeded != -1){
        cout << "Бюджет вичерпано на дні " << day_exceeded << ", накопичено " << accumulated << " грн." << endl;
    } 
    else {
        float remaining = budget - accumulated;
        cout << "Бюджету вистачило на всі дні! Залишок: " << remaining << " грн" << endl;
    }
}

//Функція для виконання пункту 3: Дні з перевищенням денного ліміту
void dailyLimitMenu(float arr[], int n){
    float limit_input;

    cout << "\n";
    cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
    cin >> limit_input;

    // Валідація: число, не менше 0. Інакше повертаємось у меню
    if (cin.fail() || limit_input < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ліміт має бути числом не менше 0" << endl;
        return;
    }

    if (limit_input == 0) {
        checkDailyLimit(arr, n); 
    } else {
        checkDailyLimit(arr, n, limit_input); 
    }
}

void checkDailyLimit(float arr[], int n, float limit){
    int count = 0;

    cout << fixed << setprecision(2);
    cout << "Ліміт: " << limit << " грн" << endl;

    for (int i = 0; i < n; i++) {
        if (arr[i] > limit) {
            cout << "  день " << i + 1 << ": " << arr[i] << " грн" << endl;
            count++;
        }
    }

    cout << "Разом днів з перевищенням: " << count << endl;
}

// Функція для виконання пункту 4: Три найдорожчі дні
void printTop3Days(const float arr[], int n) {
    
    // Створення копії масиву
    float copy[n];
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }

    // Сортування копії за спаданням (метод бульбашки)
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (copy[j] < copy[j + 1]) {
                float temp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp;
            }
        }   
    }

    int count = (n < 3) ? n : 3;

    cout << "\n";
    cout << "Топ-3 витрат: ";
    for (int i = 0; i < count; i++){
        cout << copy[i] << (i == count - 1 ? "" : ", "); 
    }
    cout << " грн" << endl;
}

