
/* 
Задача: Аналізатор місячного бюджету 
Дохнюк Богдан 
Ші-14 
 */

#include <iostream>
#include <iomanip>
using namespace std;

//ВВедення витрат за днями 
void showSpending(double spending[], int n) {
    cout << "\nДень\tВитрати, грн\n";

    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << spending[i] << "\n";
    }
}

//Рекурсивне обчислення суми витрат
double totalSpending(double spending[], int n) {
    if (n == 0) {
        return 0;
    }

    return spending[n - 1] + totalSpending(spending, n - 1);
}

//Функція max min
void findMinMax(double a[], int n, double &mn, double &mx) {
  mn = a[0];
  mx = a[0];
  for (int i = 1; i < n; i++) {
    if (a[i] < mn) mn = a[i];
    if (a[i] > mx) mx = a[i];
  }
}


// 2. Статистика витрат 
void showStatistics(double spending[], int n, double budget) {
    double minSpend;
    double maxSpend;
    findMinMax(spending, n, minSpend, maxSpend);

    double total = totalSpending(spending, n);
    double balance = budget - total;

    cout << "\nМінімальні витрати: " << minSpend << " грн\n";
    cout << "Максимальні витрати: " << maxSpend << " грн\n";
    cout << "Сумарні витрати: " << total << " грн\n";

    if (balance < 0) {
        cout << "Перевитрата понад бюджет: "
             << -balance << " грн\n";
    } else {
        cout << "Залишок бюджету : " << balance << " грн\n";
    }

    // Середні витрати за дні з покупками 
    double sumPurchases = 0;
    int daysWithPurchases = 0;

    for (int i = 0; i < n; i++) 
	{
        if (spending[i] == 0) {
            continue;
        }

        sumPurchases += spending[i];
        daysWithPurchases++;
    }

    cout << "Днів з покупками: " << daysWithPurchases << "\n";

    if (daysWithPurchases > 0) {
        cout << "Середні витрати за день з покупками: "
             << sumPurchases / daysWithPurchases << " грн\n";
    } else {
        cout << "Немає днів з покупками.\n";
    }

    // Пошук дня перевищення бюджету
    double accumulated = 0;
    int i = 0;
    bool exceeded = false;

    while (i < n) {
        accumulated += spending[i];

        if (accumulated > budget) {
            cout << "Бюджет перевищено на дні " << i + 1
                 << ", накопичено " << accumulated << " грн\n";
            exceeded = true;
            break;
        }

        i++;
    }

    if (!exceeded) {
        cout << "Бюджет не перевищено. Залишок: "
             << budget - accumulated << " грн\n";
    }
}

// 3. Дні з перевищенням денного ліміту 
void showLimitDays(double spending[], int n, double limit = 1000) {
    int count = 0;

    cout << "\nДенний ліміт: " << limit << " грн\n";

    for (int i = 0; i < n; i++) {
        if (spending[i] > limit) {
            cout << "День " << i + 1 << ": "
                 << spending[i] << " грн\n";
            count++;
        }
    }

    cout << "Кількість днів з перевищенням: "
         << count << "\n";
}

// 4. Три найдорожчі дні 
void showTopThree(double spending[], int n) {
    double copy[31];

    // копіюємо масив
    for (int i = 0; i < n; i++) {
        copy[i] = spending[i];
    }

    // Сортування за спаданням
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (copy[j] < copy[j + 1]) {
                double temp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = temp;
            }
        }
    }

    int count = 3;

    if (n < 3) {
        count = n;
    }

    cout << "\nТоп витрат: ";

    for (int i = 0; i < count; i++) {
        cout << copy[i] << " ";
    }

    cout << "грн\n";
}

int main() {

    double budget;
    int n;
    double spending[31];
    cout<<fixed<<setprecision(2);
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;

    if (cin.fail() || budget < 0) {
        cout << "Помилка введення бюджету.\n";
        return 0;
    }

    cout << "Кількість днів обліку (1-31): ";
    cin >> n;

    if (cin.fail() || n < 1 || n > 31) {
        cout << "Помилка: кількість днів має бути від 1 до 31.\n";
        return 0;
    }

    cout << "Витрати по днях: ";

    for (int i = 0; i < n; i++) {
        cin >> spending[i];

        if (cin.fail() || spending[i] < 0) {
            cout << "Помилка введення витрат.\n";
            return 0;
        }
    }

    int choice;

menu:
    do {
        cout << "\n========== Меню ==========\n";
        cout << "1. Показати витрати по днях\n";
        cout << "2. Статистика витрат\n";
        cout << "3. Дні з перевищенням денного ліміту\n";
        cout << "4. Три найдорожчі дні\n";
        cout << "0. Вийти \n";
        cout << "Ваш вибір: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка введення. Спробуйте ще раз.\n";
            goto menu;
        }
        

        switch (choice) {
            case 1:
                showSpending(spending, n);
                break;

            case 2:
                showStatistics(spending, n, budget);
                break;

            case 3: {
                double limit;

                cout << "Денний ліміт (0 = 1000 грн): ";
                cin >> limit;

                if (cin.fail() || limit < 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Неправильний ліміт.\n";
                    goto menu;
                }

                if (limit == 0) {
                    showLimitDays(spending, n);
                } else {
                    showLimitDays(spending, n, limit);
                }

                break;
            }

            case 4:
                showTopThree(spending, n);
                break;

            case 0:
                cout << "Роботу завершено.\n";
                break;

            default:
                cout << "Неправильний пункт меню.\n";
                goto menu;
        }

    } while (choice != 0);

    return 0;
}