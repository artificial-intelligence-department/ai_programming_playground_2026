/*
Аналізатор місячного бюджету
Цебуля Вадим
ШІ-12
*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const int MAX_DAYS = 31;

// Виведення таблиці витрат по днях
void Spending(double spending[], int N) {
        cout << "День  Витрати, грн" << endl;
        cout << fixed << setprecision(2);
        for (int i = 0; i < N; i++){
                cout << setw(6) << i + 1 << setw(14) << spending[i] << endl;
        }
}

// Знаходження мінімальних та максимальних витрат
void MinMaxSpending(double spending[], int N, double &minspending, double &maxspending) {
        minspending = spending[0];
        maxspending = spending[0];
        for (int i = 0; i < N; i++){
                if (spending[i] < minspending ) minspending = spending[i];
                if (spending[i] > maxspending) maxspending = spending[i];
        }
}

// Рекурсивне обчислення суми витрат
double SumSpending (double spending[], int N){
        if (N == 0) return 0;
        return spending[N - 1] + SumSpending(spending, N - 1);
}

// Виведення загальної статистики та перевірка бюджету
void Stats(double spending[], int N, double budget){
        double minspending, maxspending;
        MinMaxSpending(spending, N, minspending, maxspending);
        double TotalSpending = SumSpending(spending, N);
        
        cout << fixed << setprecision(2);
        cout << "Мінімальні витрати за день:  " << setw(9) << minspending << " грн" << endl;
        cout << "Максимальні витрати за день: " << setw(9) << maxspending << " грн" << endl;
        cout << "Сумарні витрати:             " << setw(9) << TotalSpending << " грн" << endl;

        if (TotalSpending > budget)
                cout << "Перевитрата понад бюджет:    " << setw(9) << fabs(budget - TotalSpending) << " грн" << endl;

        int SpendingDays = 0;
        for(int i = 0; i < N; i++){
                if(spending[i] == 0) continue; // Пропускаємо нульові витрати, щоб рахувати тільки дні з покупками
                SpendingDays++;
        }
        cout << "Днів з покупками:            " << setw(9) << SpendingDays << endl;

        double AvgSpending = 0;
        if(SpendingDays > 0){
                AvgSpending = TotalSpending / SpendingDays;
        }
        cout << "Середні витрати за такий день: " << setw(8) << AvgSpending << " грн" << endl;
        
        int count = 0;
        double sum = 0;

        while (count < N){
                sum += spending[count];
                count++;

                if (sum > budget) {
                        cout << "Бюджет вичерпано на дні " << count << ", накопичено " << sum << " грн." << endl;
                        break;
                }
        }

        if (sum <= budget)
                cout << "Бюджету вистачило на всі дні. Залишок: " << budget - sum << " грн." << endl;
}

// Пошук днів із перевищенням денного ліміту 
void OverspendingDays(double spending[], int N, double limit = 1000){
        int limitdays = 0;
        cout << fixed << setprecision(2);
        cout << "Ліміт: " << limit << " грн" << endl;

        for (int i = 0; i < N; i++) {
                if (spending[i] > limit) {
                        cout << "  день " << i + 1 << ": " << spending[i] << " грн" << endl;
                        limitdays++;
                }
        }
        cout << "Разом днів з перевищенням: " << limitdays << endl;
}

// Введеня денного ліміту
void Limit(double spending[], int N){
        double limit;
        cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
        if (!(cin >> limit) || limit < 0) {
                cout << "Помилка, введіть число не менше 0";
                cin.clear();
                cin.ignore(6769, '\n');
        }
        else if (limit == 0) OverspendingDays(spending, N);
        else OverspendingDays(spending, N, limit);
}

// Виведення топ-3 найбільших витрат
void TopThreeSpendingDays(double spending[], int N) {
        double copy_spending[MAX_DAYS];
        for (int i = 0; i < N; i++) {
                copy_spending[i] = spending[i];
        }
        
        // Сортування спаданням
        for (int i = 0; i < N - 1; i++) {
                for (int j = i + 1; j < N; j++) {
                        if (copy_spending[j] > copy_spending[i]) {
                                double sort = copy_spending[i];
                                copy_spending[i] = copy_spending[j];
                                copy_spending[j] = sort;
                        }
                }
        }

        int threedays = (N < 3) ? N : 3;
        cout << fixed << setprecision(2);
        cout << "Топ-3 витрат: ";
        for (int i = 0; i < threedays; i++) {
                cout << copy_spending[i];
                if (i < threedays - 1) cout << ", ";
        }
        cout << " грн" << endl;
}

int main() {
        double budget;
        int N;
        double spending[MAX_DAYS];
        int choice;

        cout << "Бюджет на місяць (грн): ";
        if (!(cin >> budget) || budget <= 0) {
                cin.clear();  
                cin.ignore(6769, '\n'); //Очищуємо потік і помилку, інакше без цього буде нескінченне зациклення
                cout << "Помилка: бюджет має бути числом, більшим за нуль." << endl;
                return 1;
        }

        cout << "Кількість днів обліку: ";
        if (!(cin >> N) || N < 1 || N > MAX_DAYS) {
                cin.clear();
                cin.ignore(6769, '\n');
                cout << "Помилка: кількість днів має бути числом від 1 до 31." << endl;
                return 1;
        }

        cout << "Витрати по днях (грн): ";
        for (int i = 0; i < N; i++) {
                if (!(cin >> spending[i]) || spending[i] < 0) {
                        cin.clear();
                        cin.ignore(6769, '\n');
                        cout << "Помилка: витрати мають бути числами не менше нуля." << endl;
                        return 1;
                }
        }

        do {
        menu: 
                cout << "\n--- МЕНЮ ---" << endl;
                cout << "1. Показати витрати по днях" << endl;
                cout << "2. Статистика витрат" << endl;
                cout << "3. Дні з перевищенням денного ліміту" << endl;
                cout << "4. Три найдорожчі дні" << endl;
                cout << "0. Вийти" << endl;
                cout << "Ваш вибір: ";

                if (!(cin >> choice)) {
                        cout << "Помилка: оберіть пункт меню від 0 до 4." << endl;
                        cin.clear();
                        cin.ignore(6769, '\n');
                        goto menu;
                }

                switch (choice) {
                case 1: 
                        Spending(spending, N); 
                        break;
                case 2: 
                        Stats(spending, N, budget); 
                        break;
                case 3: 
                        Limit(spending, N);
                        break;
                case 4: 
                        TopThreeSpendingDays(spending, N); 
                        break;
                case 0: 
                        cout << "Вихід з програми" << endl;
                        break;
                default:
                        cout << "Невірний пункт!" << endl;
                        cin.clear();
                        cin.ignore(6769, '\n');
                        goto menu;
                }
        } while (choice != 0);

        return 0;
}