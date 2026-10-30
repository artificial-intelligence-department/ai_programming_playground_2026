#include <iostream>
#include <iomanip>
#include <cmath> 
using namespace std;

void printDailySpending(float arr[], int n);    // вивід витрат по днях
void findMinMax(float arr[], int n, float &min, float &max);   // пошук мін і макс
float calculateTotalRecursive(float arr[], int n);      // рекурсивна сума
void averageSpendings(float arr[], int n, float &average_spendings, int &count); // середні витрати
void checkBudgetExceeded(float arr[], int n, float budget);   // перевірка вичерпання бюджету
void printStatistics(float arr[], int n, float budget);    // статистика витрат
void printlimitExceeded(float arr[], int n, float limit = 1000.00);  // перевищення ліміту (дефолт 1000)
void dailyLimitMenu(float arr[], int n);        // ввід ліміту користувачем
void printTop3Spending(const float arr[], int n);    // топ-3 витрат
   

int main(){
float budget;
int N;
cout << fixed << setprecision(2);

cout << "Введіть бюджет на місяць: ";
cin >> budget;
if(cin.fail() || budget <= 0 ) {
    cout << "Бюджет має бути додатнім числом\n";
    return 1;
}

cout << "Введіть кількість днів обліку: ";
cin >> N;
if (cin.fail() || N < 1 || N > 31){
    cout << "Кількість днів обліку має бути додатнім числом.\n";
    return 1;
}

float spending[1000];
cout << "Введіть витрати по днях: ";
for (int i = 0; i < N; i++){
    cin >> spending[i];
    if(cin.fail() || spending[i] < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << " Витрати мають бути невід'ємними числами\n";
            return 1;
    }
}

int choice;

do {
    menu: // мітка, на яку повертає goto
            cout << "\n===== МЕНЮ =====\n";
            cout << "1. Показати витрати по днях\n";
            cout << "2. Статистика витрат\n";
            cout << "3. Дні з перевищенням денного ліміту\n";
            cout << "4. Три найдорожчі дні\n";
            cout << "0. Вихід\n";
            cout << "Ваш вибір: ";
            cin >> choice; 

            if(cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n'); 
                cout << "Помилка: введіть число від 0 до 4.\n";
                goto menu;
            }

            if (choice < 0 || choice > 4){
                cout << "Помилка: такого пункту меню немає.\n";
                goto menu;
            }

            switch (choice){
                case 1 : printDailySpending(spending, N); break;
                case 2 : printStatistics(spending, N, budget); break;
                case 3 : dailyLimitMenu(spending, N); break;
                case 4 : printTop3Spending( spending, N); break;
                case 0: cout << "Ви здійснили вихід.\n"; break;
            }

    } while (choice != 0);

    return 0;
}

// 1 витрати по днях
void printDailySpending(float arr[], int n){
    cout << fixed << setprecision(2);
    cout << "День   Витрати, грн" << endl;
    for (int i = 0; i < n; i++){
        cout << i+1 << "       " << arr[i] << endl;
    }
}
// пошук мінімума і максимума
void findMinMax(float arr[], int n, float &min, float &max){
    min = arr[0];
    max = arr[0];
    for (int i = 0; i < n; i++){
        if (arr[i] < min ){
            min = arr[i];
        }
        if (arr[i] > max){
            max = arr [i];
        }    
    }
}
// сумаррні витрати рекурсивно
float calculateTotalRecursive(float arr[], int n){
    if(n <= 0) return 0;
    return arr[n - 1] + calculateTotalRecursive(arr, n-1);
}
// середні витрати
void averageSpendings(float arr[], int n, float &average_spendings, int &count ){
    float total_sum = calculateTotalRecursive(arr, n);

    count = 0;
    for (int i = 0; i < n; i++){
        if (arr[i] == 0 ) continue;
        else count++;
    }
    if (count == 0) average_spendings = 0.0;
    else average_spendings = total_sum / count;
}
// день коли бюджет вичерпано
void checkBudgetExceeded(float arr[], int n, float budget){
    float sum = 0;
    int lim = -1; // означає не перевищено
    int i = 0;

    while(i < n){
        sum += arr[i];

        if (sum > budget){
            lim = i+1;
            break;
        }
        i++;
    }
    if (lim != -1){
        cout << "Бюджет вичерпано на дні " << lim << ", накопичено " << sum << " грн.\n";
    } 
    else {
        float remaining = budget - sum;
        cout << "Бюджету вистачило на всі дні! Залишок: " << remaining << " грн\n";
    }
}
// 2 статистика витрат
void printStatistics(float arr[],int n, float budget){
    // min i max
    float min, max;
    findMinMax(arr, n, min, max);
    cout << "Мінімальні витрати: " << min << endl;
    cout << "Максимальні витрати: " << max << endl;

    //сумарні витрати
    float totalsum = calculateTotalRecursive(arr, n);
    cout << "Сумарні витрати: " << totalsum << " грн\n";

    // залишок бюджету
    float remaining = budget - totalsum;
    if (remaining < 0){
        float overspend = fabs(remaining); // модуль від'ємного залишку
        cout << "Перевитрата понад бюджет: "  << overspend << " грн\n";
    } else {
        cout << "Залишок бюджету: " << remaining << " грн\n";
    }
    
    // середні витрати
    float average_spendings;
    int count;
    averageSpendings(arr, n, average_spendings, count );
    cout << "Днів з покупками: " << count << endl;
    cout << "Середні витрати за такий день: " << average_spendings << " грн\n";

    // день коли бюджет вичерпано
    checkBudgetExceeded(arr, n, budget);
}
//дні з перевищенням денного ліміту
void printlimitExceeded(float arr[], int n, float limit){
    int count = 0;
    cout << fixed << setprecision(2);
    cout << "Ліміт: " << limit << " грн\n";

    for (int i = 0; i < n; i++) {
        if (arr[i] > limit) {
            cout << "   день " << i + 1 << ": " << arr[i] << " грн\n";
            count++;
        }
    }

    cout << "Разом днів з перевищенням: " << count << "\n";
}
// 3 ліміт від користувача
void dailyLimitMenu(float arr[], int n){
    float limit_input;

    cout << "\nДенний ліміт (грн, 0 = за замовчуванням): ";
    cin >> limit_input;

    // валідація, якщо limit < 0 повертаємось у меню
    if (cin.fail() || limit_input < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ліміт має бути числом не менше 0\n";
        return;
    }

    if (limit_input == 0) {
        printlimitExceeded(arr, n); 
    } else {
        printlimitExceeded(arr, n, limit_input); 
    }
}
//три найдорожчі дні
void printTop3Spending(const float arr[], int n) {
    
    // cтворення копії масиву
    float arr1[1000];
    for (int i = 0; i < n; i++) {
        arr1[i] = arr[i];
    }

    // за спаданням (метод бульбашки)
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (arr1[j] < arr1[j + 1]) {
                float temp = arr1[j];
                arr1[j] = arr1[j + 1];
                arr1[j + 1] = temp;
            }
        }   
    }

    if( n > 3){
        n = 3;
    }

    cout << "\nТоп-3 витрат: " << endl;
    for (int i = 0; i < n; i++){
        cout  << arr1[i] << " грн" << "," ;
    }
} 