/*
Аналізатор місячного бюджету
Небеснюк Маркіян
ШІ-12
*/

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// Вивід таблиці витрат по днях
void Menu_1(double spending[], int N) {
    cout << "День\t" << "Витрати, грн" << endl;
    for (int i = 0; i < N; i++) {
        cout << i + 1 << "\t" << spending[i] << endl;
    }
}

// Пошук мінімуму та максимуму
void minMax(double spending[], int N, double &minVal, double &maxVal) {
    minVal = maxVal = spending[0];
    for (int i = 1; i < N; i++){
        if (spending[i] < minVal) minVal = spending[i];
        if (spending[i] > maxVal) maxVal = spending[i];
    }
}

// Рекурсивне обчислення сумарних витрат
double spendings_sum(double spending[], int N) {
    if (N == 0) return 0;
    return spending[N - 1] + spendings_sum(spending, N - 1);
}

// Повна статистика
void Menu_2 (double spending[], int N, int budget) {
    double minS, maxS;
    minMax(spending, N, minS, maxS);
    cout << "Мінімальні витрати за день:\t\t" << minS << " грн" << endl;
    cout << "Максимальні витрати за день:\t\t" << maxS << " грн" << endl;

    double total = spendings_sum(spending, N);
    cout << "Сумарні витрати:\t\t\t" << total << " грн" << endl;

    double remainder = budget - total;
    if (remainder < 0) {
        cout << "Перевитрата бюджету:\t\t\t" << abs(remainder) << " грн" << endl;
    }
    else {
        cout << "Залишок бюджету:\t\t\t" << remainder << " грн" << endl;
    }
    
    // Підрахунок днів з реальними покупками для коректного середнього значення за день
    double sum = 0;
    int count = 0;
    for (int i = 0; i < N; i++){
        if (spending[i] == 0) continue;
        sum += spending[i];
        count++;
    }
    cout << "Днів з покупками:\t\t\t" << count << endl;
    if (count > 0) {
        cout << "Середні витрати за день з покупками:\t" << sum / count << " грн" << endl;
    }
    else {
        cout << "Середні витрати за день з покупками:\t" << "0.00 грн" << endl;
    }

    // Пошук дня, коли витрати перевищили початковий бюджет
    double spent = 0;
    int day = 0;
    while (day < N) {
        spent += spending[day];
        if (spent > budget) break;
        day++;
    }
    if (day < N) {
        cout << "Бюджет вичерпано на дні " << day + 1 << ", накопичено " << spent << " грн." << endl;
    }
    else {
        cout << "Бюджету вистачило на всі дні, залишок:\t" << remainder << " грн" << endl;
    }
}

// Вивід днів, коли витрати перевищили ліміт
void Menu_3(double spending[], int N, double limit = 1000){
    cout << "Ліміт: " << limit << " грн" << endl;
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (spending[i] > limit) {
            cout << "  день " << i + 1 << ": " << spending[i] << " грн" << endl;
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}

// Пошук та вивід 3 найбільших витрат
void Menu_4(double spending[], int N) {
    double a[N]; // Копіюємо масив, щоб не змінити оригінальний порядок днів
    for (int i = 0; i < N; i++) {
        a[i] = spending[i];
    }
    // Сортування бульбашкою за зростанням
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                double temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    // Вивід останніх елементів (найбільших), враховуючи розмір масиву
    if (N >= 3) cout << "Топ-3 витрат: " << a[N-1] << ", " << a[N-2] << ", " << a[N-3] << " грн" << endl;
    else if (N == 2) cout << "Топ-2 витрат: " << a[N-1] << ", " << a[N-2] << " грн" << endl;
    else cout << "Топ-1 витрат: " << a[N-1] << " грн" << endl;
}

int main() {
    cout << fixed << setprecision(2);

    int budget;
    validation1:
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    // Валідація вводу
    if (cin.fail() || budget < 0) {
        cout << "Помилка: введіть дійсне значення." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto validation1;
    }

    int N;
    validation2:
    cout << "Кількість днів обліку: ";
    cin >> N;
    // Валідація кількості днів
    if (cin.fail() || N <= 0 || N > 31) {
        cout << "Помилка: введіть дійсне значення." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        goto validation2;
    }

    double spending[31];
    validation3:
    cout << "Витрати по днях (грн): ";
    // Ввід витрат для кожного дня
    for (int i = 0; i < N; i++) {
        cin >> spending[i];

        // Валідація витрат
        if(cin.fail() || spending[i] < 0) {
            cout << "Помилка: введіть дійсне значення." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto validation3;
        }
    }

    int menu;
    // Головне меню
    do {
        menu_start:
        cout << endl;
        cout << "Меню" << endl;
        cout << "1 Покази витрат по днях" << endl;
        cout << "2 Статистика витрат" << endl;
        cout << "3 Дні з перевищенням денного ліміту" << endl;
        cout << "4 Три найдорожчі дні" << endl;
        cout << "0 Вийти" << endl;
        
        cin >> menu;
        // Перевірка на вибір неіснуючого пункту меню
        if (cin.fail() || menu < 0 || menu > 4) {
            cout << "Помилка: введіть дійсне значення." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto menu_start;
        }

        // Обробка вибраного пункту
        switch (menu) {
        case 1:
            cout << endl;
            Menu_1(spending, N);
            break;

        case 2:
            cout << endl;
            Menu_2(spending, N, budget);
            break;

        case 3:
            cout << endl;
            double limit;
            cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
            cin >> limit;
            if (limit == 0) {
                Menu_3(spending, N);
            }
            else {
                Menu_3(spending, N, limit);
            }
            break;

        case 4:
            cout << endl;
            Menu_4(spending, N);
            break;

        case 0:
            break;
        }

    } while (menu != 0);

    return 0;
}