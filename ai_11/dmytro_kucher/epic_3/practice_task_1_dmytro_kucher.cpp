/*
Епік 3. Практичне завдання: Аналізатор місячного бюджету
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;

void spendPerDay (double arr[], int N) {

    cout << "\n======= Витрати по днях =======";
    cout << "\nДень     Витрати, грн \n";

    for (int i = 0; i<N; i++) {
         cout << setw(2) << i+1 << setw(17) << arr[i] << endl;
    }
}

void findMinMax (double arr[], int N, double& min, double& max) {

    min = arr[0];
    max = arr[0];

    for (int i = 0; i<N; i++) {
        if (max < arr[i]) max = arr[i];
    }

    for (int i = 0; i<N; i++) {
        if (min > arr[i]) min = arr[i];
    }
}

double findSum (double arr[], int N) {

    if (N == 0) return 0;
    return arr[N-1] + findSum(arr, N-1);
}

void statistics (double arr[], int N, double budget) {

    double min = 0, max = 0;

    findMinMax(arr, N, min, max);

    cout << "\n======= Статистика витрат =======";
    cout << "\nМінімальна витрата за день: " << min << endl;
    cout << "Максимальна витрата за день: " << max << endl;

    double sum1 = findSum(arr, N);
    cout << "Сумарні витрати: " << sum1 << endl;

    double reshta = fabs(sum1 - budget);
    if (sum1 <= budget) cout << "Залишок бюджету: " << reshta << endl;
    else cout << "Перевитрата понад бюджет: " << reshta << endl;

    int count = 0;

    for (int i = 0; i<N; i++) {
        if (arr[i] == 0) continue;
        count++;
    }
    cout << "Днів з покупками: " << count << endl;
    if (count > 0)cout << "Середні витрати за дні з покупками: " << sum1/count << endl;

    double sum2 = 0;
    int n0 = 0;

    while (n0<N) {
        sum2 += arr[n0];
        n0++;

        if (sum2>budget) {
            cout << "Бюджет вичерпано на " << n0 << "-й день, накопичено " << sum2 << " грн \n"; 
            break;               
        }
    }
    
    if (sum2 <= budget && n0==N) {
        cout << "Бюджету вистачило на всі дні \n";
        cout << "Залишок: " << budget - sum2 << " грн \n";
    }
}

void checkLimits (double arr[], int N, double limit = 1000) {
    int count = 0;
    cout << "\n==== Дні з перевищенням денного ліміту ====\n";
    cout << "Ліміт: " << limit << " грн\n";
    cout << "Дні з перевищенням ліміту: ";

    for (int i = 0; i<N; i++) {
        if (arr[i] > limit) {
            cout << "\nДень " << i+1 << ": " << arr[i] << " грн. \n";
            count++;
        }
    }
    if (count == 0) cout << "немає \n";
    cout << "Кількість днів з перевищенням: " << count << endl << endl;
}

void limits (double arr[], int N) {

    double limit;
    cout << "Введіть денний ліміт (0 = 1000 грн): "; cin >> limit;

    if (cin.fail() || limit < 0) {
       cin.clear();
       cin.ignore(10000, '\n');
       cout << "Помилка! Введіть число, не менше за 0 \n";
       return;
    }

    if (limit == 0) checkLimits (arr, N);

    else checkLimits (arr, N, limit);
}

void showTop3 (double arr0[], int N) {
    double arrCopy[N];
    for (int i = 0; i<N; i++) {
        arrCopy[i] = arr0[i];
    }
    for (int i = 0; i<N; i++) {
        int maxIndex = i;
        for (int j = i; j<N; j++) {
            if (arrCopy[j] > arrCopy[maxIndex] ) maxIndex = j;
        }
        double tmp = arrCopy[i];
        arrCopy[i] = arrCopy[maxIndex];
        arrCopy[maxIndex] = tmp;
    }
    cout << "\n=========== Топ-3 витрат ===========\n";
    cout << "Топ-3 витрат: ";
    bool first = true;
    for (int i = 0; i<3 && i<N; i++) {
        if (!first) cout << ", ";
        cout << arrCopy[i];
        first = false;
    }
    cout << " грн\n";

}    

int main () {

    double budget;
    bool isAlive0 = true;
    int N, choice;
    const int daysMax = 31;

    cout << fixed << setprecision(2);

    cout << "\nВведіть бюджет на місяць, грн: "; cin >> budget;
    if (cin.fail() || budget < 0) {
        cout << "Помилка! Введіть число, не менше за 0 \n";
        return 1;
    }  

    cout << "Введіть кількість днів обліку: "; cin >> N;
    if (cin.fail() || N > daysMax || N < 1) {
        cout << "Помилка! Введіть натуральне число, не більше 31 \n";
        return 1;
    }

    double spending[N];

    for (int i = 0; i<N; i++){
        cout << "Введіть витрати в " << i+1 << " день, грн: "; cin >> spending[i];
        if (cin.fail() || spending[i] < 0) {
            cout << "Помилка! Введіть число, не менше за 0 \n";
            return 1;
        }
    }

    do {

        menu:
            cout << "\n========= Меню дій ========= \n";
            cout << "1    Показати витрати по днях\n";
            cout << "2    Статистика витрат\n";
            cout << "3    Дні з перевищенням денного ліміту\n";
            cout << "4    Три найдорожчі дні\n";
            cout << "0    Вийти\n";

            cout << "Виберіть операцію: "; cin >> choice;

        if (cin.fail () || (choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nПомилка! Введіть 1, 2, 3, 4 або 0. Спробуйте ще раз \n";
            goto menu;
        }

        else if (choice == 0) isAlive0 = 0;

        else if (choice == 1) spendPerDay (spending, N);

        else if (choice == 2) statistics(spending, N, budget);

        else if (choice == 3) limits(spending, N);
    
        else if (choice == 4) showTop3(spending, N);

    } while (isAlive0);
    
    return 0;
}