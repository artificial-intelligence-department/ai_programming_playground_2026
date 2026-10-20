/*Practice Task 1 
Цьона Олена
ШІ-12 */

#include <iostream>
#include <iomanip>   // setw, setprecision, fixed
#include <cmath>     // abs 

using namespace std;

const int MAX_DAYS = 31;  // найбільша можлива кількість днів обліку

double sumRecursive(const double a[], int N);
void findMinMax(const double a[], int N, double &minValue, double &maxValue);
void showSpending(const double a[], int N);
void showStatistics(const double a[], int N, double budget);
void showOverLimit(const double a[], int N, double limit = 1000);
void showTop3(const double a[], int N);


int main() {
    cout << fixed << setprecision(2);   

    double budget;                // бюджет на місяць, грн
    int N;                        // кількість днів обліку
    double spending[MAX_DAYS];    // витрати по днях 
    int choice;                   // пункт меню, який вибрав користувач

    // Введення бюджету з перевіркою 
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    while (cin.fail() || budget <= 0) {
        cin.clear();                
        cin.ignore(10000, '\n');    
        cout << "Помилка! Введіть число більше 0: ";
        cin >> budget;
    }

    // Введення кількості днів з перевіркою 
    cout << "Кількість днів обліку: ";
    cin >> N;
    while (cin.fail() || N < 1 || N > MAX_DAYS) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка! Введіть ціле число від 1 до " << MAX_DAYS << ": ";
        cin >> N;
    }

    // Введення витрат по днях з перевіркою 
    cout << "Витрати по днях (грн), " << N << " чисел: ";
    for (int i = 0; i < N; i++) {   
        cin >> spending[i];
        while (cin.fail() || spending[i] < 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка! День " << i + 1 << " - введіть число не менше 0: ";
            cin >> spending[i];
        }
    }

    
    do {
    menu:   
        cout << "\n МЕНЮ \n"
             << "1 - Показати витрати по днях\n"
             << "2 - Статистика витрат\n"
             << "3 - Дні з перевищенням денного ліміту\n"
             << "4 - Три найдорожчі дні\n"
             << "0 - Вийти\n"
             << "Ваш вибір: ";

        cin >> choice;

        if (cin.fail()) {                // ввели не число
            cin.clear();
            cin.ignore(10000, '\n');     
            cout << "Помилка: потрібно ввести цифру!\n";
            goto menu;
        }

        switch (choice) {
            case 1:
                showSpending(spending, N);
                break;
            case 2:
                showStatistics(spending, N, budget);
                break;
            case 3: {
                double limit;   // денний ліміт
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                cin >> limit;
                while (cin.fail() || limit < 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Помилка! Введіть число не менше 0: ";
                    cin >> limit;
                }
                if (limit == 0) {
                    showOverLimit(spending, N);          // береться 1000
                } else {
                    showOverLimit(spending, N, limit);   // береться введений
                }
                break;
            }
            case 4:
                showTop3(spending, N);
                break;
            case 0:
                cout << "До побачення!\n";
                break;
            default:
                cout << "Помилка: такого пункту немає!\n";
                goto menu;
        }
    } while (choice != 0);

    return 0;
}



//сума усіх витрат, обчислена за допомогою рекурсії
double sumRecursive(const double a[], int N) {    // a - масив витрат
                                                  // N - кількість днів обліку 
    if (N == 0) return 0;                       
    return a[N - 1] + sumRecursive(a, N - 1);   
}

//пошук мінімального та максимального значення за допомогою порівняння
void findMinMax(const double a[], int N, double &minValue, double &maxValue) {
    minValue = a[0];   
    maxValue = a[0];   
    for (int i = 1; i < N; i++) {   
        if (a[i] < minValue) minValue = a[i];
        if (a[i] > maxValue) maxValue = a[i];
    }
}

// витрати по днях 
void showSpending(const double a[], int N) {
    for (int i = 0; i < N; i++) {   
        cout << "День " << i + 1 << ": " << a[i] << " грн" << endl;
    }
}

// статистика 
void showStatistics(const double a[], int N, double budget) {
    // 1) мінімум і максимум
    double minValue;   
    double maxValue;   
    findMinMax(a, N, minValue, maxValue);
    cout << "Мінімальні витрати за день:  " << setw(10) << minValue << " грн\n";
    cout << "Максимальні витрати за день: " << setw(10) << maxValue << " грн\n";

    // 2) сума (рекурсія)
    double total = sumRecursive(a, N);   // сума витрат за всі дні
    cout << "Сумарні витрати:             " << setw(10) << total << " грн\n";

    // 3) залишок або перевитрата
    double rest = budget - total;   // залишок бюджету (може бути від'ємним)
    if (rest < 0) {
        cout << "Перевитрата:    " << setw(10) << abs(rest) << " грн\n";
    } else {
        cout << "Залишок бюджету:             " << setw(10) << rest << " грн\n";
    }

    // 4) середні витрати за дні з покупками
    int countDays = 0;   
    double sum = 0;      
    for (int i = 0; i < N; i++) {   
        if (a[i] == 0) continue;    
        sum += a[i];
        countDays++;
    }
    cout << "Днів з покупками:            " << setw(10) << countDays << "\n";
    if (countDays > 0) {
        cout << "Середні витрати за такий день: " << sum / countDays << " грн\n";
    } else {
        cout << "Hе було покупок.\n";
    }

    // 5) день, коли бюджет вичерпано 
    double accumulated = 0;   
    int day = 0;              
    while (day < N) {
        accumulated += a[day];
        if (accumulated > budget) break;   // бюджет перевищено - зупиняємось одразу
        day++;
    }
    if (day < N) {
    
        cout << "Бюджет вичерпано на дні " << day + 1
             << ", накопичено " << accumulated << " грн.\n";

    } else {
        
        cout << "Бюджету вистачило на всі дні. Залишок: "
             << budget - accumulated << " грн.\n";
    }
}

// дні з перевищенням ліміту 
void showOverLimit(const double a[], int N, double limit = 1000) {  // limit - денний ліміт (якщо не передати, буде 1000)
    cout << "Ліміт: " << limit << " грн\n";
    int count = 0;   // скільки днів перевищили ліміт
    for (int i = 0; i < N; i++) {   // i - індекс дня
        if (a[i] > limit) {
            cout << "  день " << i + 1 << ": " << a[i] << " грн\n";
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << "\n";
}

// три найдорожчі дні
void showTop3(const double a[], int N) {
    double copy[MAX_DAYS];   // копія масиву, її ми сортуємо
    for (int i = 0; i < N; i++) {   
        copy[i] = a[i];
    }

    // Сортування за спаданням вкладеними циклами
    for (int i = 0; i < N - 1; i++) {          
        for (int j = i + 1; j < N; j++) {      
            
            if (copy[i] < copy[j]) {
                double temporary = copy[i];    
                copy[i] = copy[j];
                copy[j] = temporary;
            }
        }
    }

    // Виводимо три найбільші (або менше, якщо днів менше трьох)
    int count = N;       
    if (count > 3) count = 3;

    cout << "Топ-" << count << " витрат: ";
    for (int i = 0; i < count; i++) {   
        cout << copy[i];
        if (i < count - 1) cout << ", ";
    }
    cout << " грн\n";
}
