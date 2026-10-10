
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void showSpending(double arr[], int n) {
    cout << "День     Витрати, грн" << endl;
    cout << fixed << setprecision(2);
    for (int i = 0; i < n; i++) {
        cout << setw(4) << i + 1 << setw(17) << arr[i] << endl;
    }

}

void showOverLimit(double arr[], int n, double limit = 1000) {
    cout << fixed << setprecision(2);
    cout << "Ліміт: " << limit << " грн" << endl;

    int count = 0;

    for (int i = 0; i < n; i++) {
    if (arr[i] > limit) {
    cout << "  день " << i + 1 << ": " << arr[i] << " грн" << endl;
    count++;
    }
    }

    cout << "Разом днів з перевищенням: " << count << endl;

}

void showTop3(double arr[], int n) {
    double copy[31];

    // копіюємо числа
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (copy[j] > copy[i]) {
                double temp = copy[i];
                copy[i] = copy[j];
                copy[j] = temp;
            }
        }
    }

    int k = 3;
    if (n < 3) k = n;

    cout << fixed << setprecision(2);
    cout << "Топ-3 витрат: ";
    for (int i = 0; i < k; i++) {
        if (i > 0) cout << ", "; // кома перед усіма, крім першого
        cout << copy[i];
    }
    cout << " грн" << endl;
}

// функція міняє самі змінні з showStats, а не їхні копії
void minMax(double arr[], int n, double &minVal, double &maxVal) {
    minVal = arr[0];
    maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
}
 
double sumRec(double arr[], int n) {
    if (n == 0) return 0;
    return arr[n - 1] + sumRec(arr, n - 1);
}

void showStats(double arr[], int n, double budget) {
    cout << fixed << setprecision(2);

    double mn, mx;
    minMax(arr, n, mn, mx);
    cout << "Мінімальні витрати за день: " << setw(10) << mn << " грн" << endl;
    cout << "Максимальні витрати за день: " << setw(9) << mx << " грн" << endl;

    // сума рекурсією
    double total = sumRec(arr, n);
    cout << "Сумарні витрати: " << setw(21) << total << " грн" << endl;

    double rest = budget - total;
    if (rest < 0) {
        cout << "Перевитрата понад бюджет: " << setw(12) << fabs(rest) << " грн" << endl;
    } else {
        cout << "Залишок бюджету: " << setw(21) << rest << " грн" << endl;
    }

    int days = 0;
    double sum = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) continue; // день без покупок пропускаю, йду до наступного
        sum += arr[i];
        days++;
    }
    cout << "Днів з покупками: " << setw(20) << days << endl;
    if (days > 0) {
        cout << "Середні витрати за такий день: " << sum / days << " грн" << endl;
    }

    
    int day = 0;
    double acc = 0;
    while (day < n) {
        acc += arr[day];
        if (acc > budget) break;
        day++;
    }
    if (day < n) {
        cout << "Бюджет вичерпано на дні " << day + 1 << ", накопичено " << acc << " грн." << endl;
    } else {
        cout << "Бюджету вистачило на всі дні, залишок: " << budget - acc << " грн." << endl;
    }
}

int main() {

    double budget = 0;

    do {
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); budget = -1; }
    if (budget <= 0) cout << "Помилка: бюджет має бути більшим за 0." << endl;
    } while (budget <= 0);

    int n;

    do {
        cout << "Кількість днів обліку: ";
        cin >> n;
        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); n = -1; }
        if (n < 1 || n > 31) cout << "Помилка: не більше місяця" << endl;
    } while (n < 1 || n > 31);

    double spending[31];

    cout << "Витрати по днях (грн): ";

    for (int i = 0; i < n; i++) {
        do {
        cin >> spending[i];
        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); spending[i] = -1; }
        if (spending[i] < 0) cout << "Помилка: витрата за день " << i + 1 << " не може бути від'ємною" << endl;
        } while (spending[i] < 0);
    }

    char choice;
    double limit;

    do {
        menu:
    cout << "1 - Показати витрати по днях" << endl;
    cout << "2 - Статистика витрат" << endl;
    cout << "3 - Дні з перевищенням денного ліміту" << endl;
    cout << "4 - Три найдорожчі дні" << endl;
    cout << "0 - Вийти" << endl;
    cout << "Ваш вибір: ";
    cin >> choice;
    cin.ignore(1000, '\n');

    switch (choice) {
        case '1': 
        showSpending(spending, n);
        break;
        case '0':
        cout << "Завершення роботи" << endl;
        break;
        case '2':
        showStats(spending, n, budget);
        break;
        case '3':
        do {
            cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
            cin >> limit;
        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); limit = -1; }

            if (limit < 0) cout << "Помилка: ліміт не може бути від'ємним." << endl;

        } while (limit < 0);

        if (limit == 0) {
            showOverLimit(spending, n);
            } else {
                showOverLimit(spending, n, limit);
            }
        break;
        case '4':
        showTop3(spending, n);
        break;
        default:
        cout << "Помилка: оберіть пункт від 0 до 4. " << endl;
        goto menu;
       }

    } while (choice != '0');

    return 0;
}