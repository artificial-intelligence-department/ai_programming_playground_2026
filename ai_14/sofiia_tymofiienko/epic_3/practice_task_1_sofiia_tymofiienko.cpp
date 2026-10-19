/* Tymofiienko Sofiia SHI-14*/ 

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int MAX_DAYS = 31; //Фіксуємо максимальну кількість днів у місяці
double calculateTotal(const double spending[], int n, int index = 0) {
    if (index >= n) return 0.0;                       // Закінчуємо виклик функції, так як елементи заінчились
    return spending[index] + calculateTotal(spending, n, index + 1); // Виклик рекурсії
}
void findMinMax(const double spending[], int n, double &minVal, double &maxVal) { //Використовуєм параметр посилання &
    minVal = spending[0];
    maxVal = spending[0];
    for (int i = 1; i < n; i++) {
        if (spending[i] < minVal) minVal = spending[i];
        if (spending[i] > maxVal) maxVal = spending[i];
    }
}
void showDaily(const double spending[], int n) {
    cout << endl << "День    Витрати, грн" << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(3) << i + 1 << setw(16) << spending[i] << endl;   
    }
}
void showStats(const double spending[], int n, double budget) { //Аналіз статистичних даних та порівняння мінімуму і максимуму через цикл for
    cout << endl;

    double minV, maxV;
    findMinMax(spending, n, minV, maxV);
    double total = calculateTotal(spending, n);

    cout << "Мінімальні витрати за день:  " << setw(10) << minV << " грн" << endl;
    cout << "Максимальні витрати за день: " << setw(10) << maxV << " грн" << endl;
    cout << "Сумарні витрати:             " << setw(10) << total << " грн" << endl;

    double balance = budget - total;
    if (balance < 0) {
        cout << "Перевитрата понад бюджет:    " << setw(10) << fabs(balance) << " грн" << endl;
    } else {
        cout << "Залишок бюджету:             " << setw(10) << balance << " грн" << endl;
    }
    int days = 0;
    double sum = 0;
    for (int i = 0; i < n; i++) {
        if (spending[i] == 0) continue;
        sum += spending[i];
        days++;
    }
    cout << "Днів з покупками:            " << setw(10) << days << endl;
    if (days > 0) {
        cout << "Середні витрати за такий день: " << sum / days << " грн" << endl;
    } else {
        cout << "Покупок не було, середнє порахувати неможливо." << endl;
    }
    double acc = 0;
    int day = 0;
    while (day < n) {
        acc += spending[day];
        day++;                       
        if (acc > budget) break;    
    }
    if (acc > budget) {
        cout << "Бюджет вичерпано на дні " << day << ", накопичено " << acc << " грн." << endl;
    } else {
        cout << "Бюджету вистачило на всі дні. Залишок: " << budget - total << " грн." << endl;
    }
}
void showLimit(const double spending[], int n, double limit = 1000.0) { //Аналіз ліміту бюджету
    cout << endl << "Денний ліміт (грн, 0 = за замовчуванням): ";
    double input;
    cin >> input;
    while (cin.fail() || input < 0) {
        if (cin.eof()) return;                 
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка! Ліміт має бути невід'ємним числом: ";
        cin >> input;
    }
    cin.ignore(10000, '\n');
    if (input > 0) limit = input;              

    int count = 0;
    cout << "Ліміт: " << limit << " грн" << endl;
    for (int i = 0; i < n; i++) {
        if (spending[i] > limit) {
            cout << "  день " << i + 1 << ": " << spending[i] << " грн" << endl;
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}
void showTop3(const double spending[], int n) { //Функція для сортування витрат за днями бульбашкою через вкладені цикли і копії масивів
    double copy[MAX_DAYS];                     
    for (int i = 0; i < n; i++) {
        copy[i] = spending[i];
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (copy[j] < copy[j + 1]) {
                double t = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = t;
            }
        }
    }

    int count = (n < 3) ? n : 3;               
    cout << endl << "Топ-3 витрат: ";
    for (int i = 0; i < count; i++) {
        cout << copy[i] << (i < count - 1 ? ", " : " грн");
    }
    cout << endl;
}

int main() { //Головна функція коду, здійснює форматування виведених даних та зчитування+валідацію ввідних даних
    cout << fixed << setprecision(2);          

    double budget;
    int n;
    do {
        cout << "Бюджет на місяць (грн): ";
        if (!(cin >> budget) || budget <= 0) {
            if (cin.eof()) return 0;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка! Бюджет має бути числом більше 0." << endl;
        } else {
            cin.ignore(10000, '\n');
            break;
        }
    } while (true); 
    do { //Цикл do while для пропуску тіла, перевірки умови після нього та очищення сміття у випадку некоректного вводу
        cout << "Кількість днів обліку (1-31): ";
        if (!(cin >> n) || n < 1 || n > MAX_DAYS) {
            if (cin.eof()) return 0;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка! Кількість днів має бути від 1 до 31." << endl;
        } else {
            cin.ignore(10000, '\n');
            break;
        }
    } while (true);

    double spending[MAX_DAYS];
    cout << "Витрати по днях:" << endl;
    for (int i = 0; i < n; i++) {
        do { //Валідація і очищення
            cout << "День " << i + 1 << ": ";
            if (!(cin >> spending[i]) || spending[i] < 0) {
                if (cin.eof()) return 0;
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Помилка! Витрата має бути числом не менше 0." << endl;
            } else {
                cin.ignore(10000, '\n');
                break;
            }
        } while (true);
    }
    int choice;
    do {
menu:
        cout << endl << "1. Витрати по днях" << endl;
        cout << "2. Статистика витрат" << endl;
        cout << "3. Дні з перевищенням ліміту" << endl;
        cout << "4. Топ-3 витрат: " << endl;
        cout << "0. Вихід" << endl;
        cout << "Вибір: ";

        if (!(cin >> choice)) {                
            if (cin.eof()) return 0;           
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка! Введіть число від 0 до 4." << endl;//Валідація вибору опцій меню та повернення до нього міткою goto
            goto menu;
        }
        cin.ignore(10000, '\n');               

        switch (choice) { //Свічкейс для підв'язки цифр до опцій меню
            case 1: showDaily(spending, n); break;
            case 2: showStats(spending, n, budget); break;
            case 3: showLimit(spending, n); break;
            case 4: showTop3(spending, n); break;
            case 0: cout << "Вихід!" << endl; break;
            default:
                cout << "Помилка! Такого пункту немає." << endl;
                goto menu;
        }
    } while (choice != 0);

    return 0;
}
