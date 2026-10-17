#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
/* Аналізатор місячного бюджету
   Тимофій Сідлецький ШІ-13
*/

void dayspendings (float *A,int days); // функція виводу витрат по днях
void minmaxspendings (float *A, int days, float& minimum, float& maximum); // пошук мінімальних та максимальних витрат
float sumSpending(float *A, int x); // рекурсивна функція для підрахунку сумарних витрат
void budgetleftover(float *A, int days, float budget); // функція для підрахунку залишку бюджету або перевитрати
void avgspending (float *A, int days); // функція для підрахунку середніх витрат на день та кількості днів з покупками
void budgetoverspent (float *A, int days, float budget); // функція для підрахунку дня, коли бюджет вичерпано або залишку бюджету
void daylimit(float *A, int days, int limit); // функція для підрахунку днів з перевищенням денного ліміту
void mostexpensivedays(float *A, int days); // функція для підрахунку трьох найдорожчих днів

int main() {
    float budget;
    float spending[30];
    int n, action, newlimit;
    float min, max, newlimit;

    // введення даних та валідація
    cout << "Бюджет на місяць(грн): ";
    cin >> budget;
    if (budget <= 0 || cin.fail()) {
        cout << "Неправильно введений бюджет" << endl;
        return 1;
    }

    cout << "Кількість днів обліку: ";
    cin >> n;
    if (n <= 0 || cin.fail()) {
        cout << "Неправильно введена к-сть днів" << endl;
        return 1;
    }

    cout << "Витрати по днях(грн): ";
    for (int i = 0; i < n; i++) { // цикл для наповнення масиву
        cin >> spending[i];
        if (spending[i] < 0 || cin.fail()) {
            cout << "Неправильно введені витрати" << endl;
            return 1;
        }
    }

    cout << fixed << setprecision(2);

    // повторення меню циклом do-while
    do {
        menustart: // goto мітка
        cout << "1      Показати витрати по днях" << endl;
        cout << "2      Статистика витрат" << endl;
        cout << "3      Дні з перевищенням денного ліміту" << endl;
        cout << "4      Три найдорожчі дні" << endl;
        cout << "0      Вийти" << endl;
        cin >> action;
        // валідація та повернення на початок меню у випадку помилки
        if (cin.fail() || action < 0 || action > 4) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Неправильно введена дія" << endl;
            goto menustart;
        }
        switch (action) {
            case 1:
                dayspendings(spending, n);
                cout << endl;
                break;
            case 2:
                minmaxspendings(spending, n, min, max);
                cout << endl;
                cout << "Мінімальні витрати: " << min << " грн" << endl;
                cout << "Максимальні витрати: " << max << " грн" << endl;
                cout << "Сумарні витрати: " << sumSpending(spending, n) << " грн" << endl;
                budgetleftover(spending, n, budget);
                avgspending(spending, n);
                budgetoverspent(spending, n, budget);
                break;
            case 3:
                cout << endl;
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                cin >> newlimit;
                if (newlimit == 0) {
                    newlimit = 1000;
                }
                daylimit(spending, n, newlimit);
                break;
            case 4:
                mostexpensivedays(spending, n);
                break;
        }
    } while (action != 0);
    return 0;
}

void dayspendings (float *A,int days) {
    cout << endl;
    cout << "День        Витрати, грн"; 
    for (int i = 0; i < days; i++) {
        cout << endl << i + 1 << "          " << A[i];
    }
    cout << endl;
}

// функція пошуку мінімальної та максимальної витрати та повернення параметром-посалинням
void minmaxspendings (float *A, int days, float& minimum, float& maximum) {
    float min = A[0];
    float max = A[0];
    for (int i = 0; i < days; i++) {
        if (A[i] < min) {
            min = A[i];
        }
        if (A[i] > max) {
            max = A[i];
        }
    }
    minimum = min;
    maximum = max;
}

float sumSpending(float *A, int x) // рекурсивна функція для підрахунку сумарних витрат
{
    if (x == 0)
        return 0;
    return A[x - 1] + sumSpending(A, x - 1);
}

void budgetleftover(float *A, int days, float budget) {
    float spendsum = 0;
    for (int i = 0; i < days; i++) {
        spendsum += A[i];
    }
    if (spendsum < budget) {
        budget = budget - spendsum;
        cout << "Залишок бюджету: " << budget << endl;
    }
    if (spendsum > budget) {
        budget = abs(budget - spendsum);
        cout << "Перевитрата понад бюджет: " << budget << endl;
    }
}

void avgspending (float *A, int days) {
    float sum = 0;
    int daycount = 0;
    for (int i = 0; i < days; i++) {
        if (A[i] == 0) {
            continue;
        }
        sum += A[i];
        daycount++;
    }
    float avg = sum / daycount;
    cout << "Днів з покупками: " << daycount << endl;
    cout << "Середні витрати на день: " << avg << endl;
}

void budgetoverspent (float *A, int days, float budget) {
    float sum = 0;
    int i = 0;
    bool budgetExceeded = 0;
    while (sum <= budget && i < days) {
        sum += A[i];
        i++;
        if (sum > budget) {
            cout << "Бюджет вичерпано на " << i << " день, накопичено " << sum << " грн" << endl;
            budgetExceeded = 1;
            break;
        }
    }
    if (budgetExceeded == 0) {
        cout << "Бюджет не вичерпано, залишок " << budget - sum << " грн" << endl;
    }
    cout << endl;
}

void daylimit(float *A, int days, float limit = 1000) {
    int daycount = 0;
    cout << "Ліміт: " << limit << " грн" << endl;
    for (int i = 0; i < days; i++) {
        if (A[i] > limit) {
            cout << "   день " << i + 1 << ": " << A[i] << " грн" << endl;
            daycount++;
        }
    }
    cout << "Разом днів з перевищенням: " << daycount << endl;
    cout << endl;
}

void mostexpensivedays(float *A, int days) {
    float B[days];
    for (int i = 0; i < days; i++) {
        B[i] = A[i];
    }
    for (int i = 0; i < days - 1; i++) {
        for (int j = 0; j < days - i - 1; j++) {
            if (B[j] < B[j + 1]) {
                int temp = B[j];
                B[j] = B[j + 1];
                B[j + 1] = temp;
            }
        }
    }
    cout << endl;
    if (days > 2){
        cout << "Топ-3 витрат: " << B[0] << ", " << B[1] << ", " << B[2] << " грн" << endl;
    }
    if (days < 3) {
        cout << "Топ витрат: ";
        for (int i = 0; i < days; i++) {
            cout << B[i];
        }
        cout << " грн" << endl;
    }
    cout << endl;
}