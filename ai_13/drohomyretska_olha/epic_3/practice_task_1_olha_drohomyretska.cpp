// Завдання: Аналізатор місячного бюджету
// Авторка: Дрогомирецька Ольга
// Група: ШІ-13

#include <iostream> 
#include <cmath>
#include <iomanip>

using namespace std;

const int MAX_DAYS = 31; //максимальна кількість днів обліку протягом одного місяця.

void showSpending (double spending[], int n) // функція виводить номер дня та витрати за цей день
{ 
    cout << "День\tВитрати, грн" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << spending[i] << endl;
    }
}

void minMax (double spending[], int n, double &mn, double &mx) //записує мінімум і макс у змінні виклику через посилання.
{
mn = spending[0];
mx = spending[0];
for (int i = 1; i < n; i++) {
    if (spending[i] < mn) mn = spending[i];
    if (spending[i] > mx) mx = spending[i];
}
}

double total(double spending[], int n) { //рекурсивно обчислює суму
        if (n == 0) { return 0;}
        return spending[n - 1] + total(spending, n - 1);
    }

void showStatistics(double spending[], int n, double budget) { //показує статистику витрат і перевіряє достатність бюджету
    double mn;
    double mx;

    minMax (spending, n, mn, mx);

    cout << "Мінімальні витрати за день: " << mn << fixed << setprecision(2) << " грн" << endl;
    cout << "Мaксимальні витрати за день: " << mx << fixed << setprecision(2) << " грн" << endl;

    double sum = total (spending, n);
    double balance = budget - sum;
    cout << "Сумарні витрати: " << sum << fixed << setprecision(2) << " грн" << endl;
    if (balance < 0){
        cout << "Перевитрата понад бюджет: " << fabs(balance) << fixed << setprecision(2) << " грн" << endl;
    } else {
        cout << "Залишок бюджету: " << balance << fixed << setprecision(2) << " грн" << endl;
    }

    int daysPurchases = 0; 
    for (int i = 0; i < n; i++){ //пропускаю нульові витрати й рахую лише дні з покупкою
    if (spending[i] == 0){
        continue;
    } 
        daysPurchases++;
    }
    cout << "Днів з покупками: " << daysPurchases << endl;

    if (daysPurchases > 0) { //запобігає діленню на нуль
        double average = sum / daysPurchases;
        cout << "Середні витрати за такий день: " << fixed << setprecision(2) << average << " грн" << endl;
    } else {
        cout << "Днів з покупками не було" << endl;
    }

    double accumulated = 0;
    int i = 0;
    while (i < n) { //накопичую витрати до першого перевищення бюджету.
    accumulated += spending[i];
    if (accumulated > budget) {
        cout << "Бюджет вичерпано на дні " << i + 1 << ", накопичено " << fixed << setprecision(2) << accumulated << " грн." << endl;
        break;
    }
    i++;
}
if (accumulated <= budget) {
    cout << "Бюджет не вичерпано." << endl;
    cout << "Залишок бюджету: " << fixed << setprecision(2) << budget - accumulated << " грн" << endl;
}
}

void showOverlimit(double spending[], int n, double limit = 1000) { //показує дні з перевищенням ліміту, типовий ліміт = 1000 грн
    int count = 0;

    cout << "Ліміт: " << fixed << setprecision(2) << limit << " грн" << endl;

    for (int i = 0; i < n; i++) {
        if (spending[i] > limit) {
            cout << " день " << i + 1 << ": " << spending[i] << " грн" << endl;  
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}

void showTopThree (double spending[], int n) {
    double copy[MAX_DAYS];
    //Спочатку повністю копіюю витрати
    for (int i = 0; i < n; i++){
        copy[i] = spending[i]; }
        //Тепер сортую копію за спаданням
        for (int i = 0; i < n - 1; i++){
            for (int j = 0; j < n - 1 - i; j++) {
                if (copy[j] < copy[j + 1]){
                double temp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp; }
                }
            }
            int count = 3;
            if (n < 3) {
                count = n;
            }

            cout << fixed << setprecision(2);
            cout << "Топ-" << count << " витрат: ";

            for (int i = 0; i < count; i++){
                cout << copy[i];
                if (i < count - 1) {
                    cout << ", "; 
                }
            }
            cout << " грн" << endl;
        }

int main() {
cout << fixed << setprecision(2);
    double budget;
//зчитуєм початкові дані та перевіряємо їх на умову
    budget_input:
    cout << "Бюджет на місяць (грн) : ";
    cin >> budget;

    if (cin.fail() || budget <= 0) {
        cout << "Помилка: введіть число більше нуля." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        goto budget_input;
    }

    int n;
    double spending[MAX_DAYS] = {0};

    days_input:
    cout << "Кількість днів обліку: "; 
    cin >> n;

    if (cin.fail() || n < 1 || n > MAX_DAYS) {
        cout << "Помилка: введіть ціле число від 1 до " << MAX_DAYS << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        goto days_input;
    }

    spending_input:
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < n; i++){
        cin >> spending[i];
    
    if (cin.fail() || spending[i] < 0) {
        cout << "Помилка: введіть невідʼємні числа." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        goto spending_input;
    }
}
    //повторюю меню до вибору пункту 0
    int choice;
    do {
    menu_input:
        cout << endl << "МЕНЮ" << endl;
        cout << "1 - Показати витрати по днях" << endl;
        cout << "2 - Статистика витрат" << endl;
        cout << "3 - Дні з перевищенням денного ліміту" << endl;
        cout << "4 - Три найдорожчі дні" << endl;
        cout << "0 - Вийти" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        if (cin.fail() || choice < 0 || choice > 4) {
        cout << "Помилка: виберіть пункт меню від 0 до 4." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        goto menu_input;
        }
        //викликаю функцію відповідно до вибраного пункту меню
        switch (choice) {
            case 1: 
            showSpending(spending, n);
            break;

            case 2: 
            showStatistics(spending, n, budget);
            break;

            case 3: {
                double limit;

                limit_input:
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                cin >> limit;

                if (cin.fail() || limit < 0) {
                cout << "Помилка: введіть невідʼємнe числo." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                goto limit_input;
                }

                if (limit == 0) {
                    showOverlimit(spending, n);
                } else { showOverlimit(spending, n, limit);
                }
                break;
            }
            case 4: 
                showTopThree(spending, n);
                break;
                
            case 0: 
            break;
            }

        } while (choice!= 0);
        return 0;
    }