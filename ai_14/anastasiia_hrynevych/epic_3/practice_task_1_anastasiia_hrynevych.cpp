#include <iostream>
#include <iomanip>
using namespace std;

void minmax(int n, double a[]) {
    double max = 0, min = 1000000;
    for (int i = 0; i < n; i++) {
        if ( a[i] > max ) max = a[i];
        if ( a[i] < min ) min = a[i];
    }
    cout << "Мінімальні витрати за день:" << "\t" << fixed << setprecision(2) << min << " грн" << "\n"; 
    cout << "Максимальні витрати за день:" << "\t" << fixed << setprecision(2) << max << " грн" << "\n"; 
}

double findsum(int n, double a[]) {
    if (n == 0) return 0;
    return a[n-1] + findsum(n-1, a);
}

void exceedinglimit(int n, double a[], double limit = 1000) {
    int exceedingdays = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > limit) {
        cout << "  день " << i+1 << ":\t" << fixed << setprecision(2) << a[i] << "\n";
        exceedingdays++;
        }
    }
    cout << "Разом днів з перевищенням: " << exceedingdays << "\n";
}

void topthree(int n, double a[]) {
    double copy[100]; 
    for (int i = 0; i < n; i++) {
        copy[i] = a[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++)
        if (copy[j] < copy[j+1]) {
            double t = copy[j];
            copy[j] = copy[j+1];
            copy[j+1] = t;
        }
    }
    cout << "Три найбільші витрати за день: " << fixed << setprecision(2) << copy[0] << " " << copy[1] << " " << copy[2] << "\n";
}

void toptwo(int n, double a[]) {
  double copy[n];
    for (int i = 0; i < n; i++) {
        copy[i] = a[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++)
        if (copy[j] < copy[j+1]) {
            double t = copy[j];
            copy[j] = copy[j+1];
            copy[j+1] = t;
        }
    }
    cout << "Три найбільші витрати за день: " << fixed << setprecision(2) << copy[0] << " " << copy[1] << "\n";
}

int main() {
    int N;
    int option;
    double budget;
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    if (budget < 0) {
        cout << "Бюджет не може бути від'ємним числом."; 
        return 0;
    }
    cout << "Кількість днів обліку: ";
    cin >> N;
    if (N <= 0 || N > 31) {
        cout << "Кількість днів повинна лежати в межах від 1 до 31"; 
        return 0;
    }
    double spending[N];
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i < N; i++) {
        cin >> spending[i];
        if (spending[i] < 0) {
        cout << "Витрати не можуть бути від'ємним числом."; 
        return 0;
    }
    }
    do {
    menu: 
        cout << "1" << "\t" << "Показати витрати по днях" << "\n";
        cout << "2" << "\t" << "Статистика витрат" << "\n";
        cout << "3" << "\t" << "Дні з перевищенням денного ліміту" << "\n";
        cout << "4" << "\t" << "Три найдорожчі дні" << "\n";
        cout << "0" << "\t" << "Вийти" << "\n";
        cout << "> "; 
        if (!(cin >> option)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Неіснуючий тип! Перенаправляємо в головне меню." << "\n";
        goto menu;
    }
    
    switch(option) {
        case 1: {
        cout << "День" << "\t" << "Витрати, грн" << "\n";
        for (int i = 0; i < N; i++) {
        cout << i + 1 << "\t" << fixed << setprecision(2) << spending[i] << "\n";
        
        }
        break;
        }
        case 2: {
            minmax(N, spending);
            cout << "Сумарні витрати:" << "\t\t" << fixed << setprecision(2) << findsum(N, spending) << " грн" << "\n";
            if (findsum(N, spending) > budget) cout << "Перевитрата понад бюджет:\t";
            else cout << "Залишок з бюджету:\t\t";
            cout << fixed << setprecision(2) << abs(findsum(N, spending) - budget) << " грн" << "\n";
            int spent = 0;
            for (int i = 0; i < N; i++) {
                if ( spending[i] != 0 ) spent++;
                else continue;
            }
            cout << "Днів з покупками:\t\t" << fixed << setprecision(2) << spent << "\n";
            cout << "Середні витрати за такий день:\t" << fixed << setprecision(2) << findsum(N, spending)/spent << "\n";
            if (findsum(N, spending) < budget) {
                cout << "Бюджету вистачило на всі дні. Залишок: " << fixed << setprecision(2) << budget - findsum(N, spending) << "\n";
            }
            else {
                double remaining = budget, accumulated = 0;
                int days = 0;
                for (int i = 0; i < N; i++) {
                
                while (remaining > 0) {
                    remaining -= spending[i];
                    
                    days++;
                }
                break;
                }
                
                cout << "Бюджет вичерпано на дні " << days << ", накопичено " << fixed << setprecision(2) << findsum(days, spending) << " грн.\n";
            }
            break;
        }
        case 3: {
            double limit; 
            cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
            cin >> limit;
            if (limit < 0) { 
                cout << "Ліміт  не може бути від'ємним числом." << endl; 
                return 0; }
            else if (limit == 0) exceedinglimit(N, spending); 
            else if (limit > 0) exceedinglimit(N, spending, limit);
            break;
        }
        case 4: {
        if (N >= 3) topthree(N, spending);
        else if (N == 2) toptwo(N, spending);
        else if (N == 1) cout << fixed << setprecision(2) << spending[0];
        break;
        }
        case 0:
        cout << "Вихід з програми." << "\n";
        break;
        default:
        cout << "Неіснуючий тип! Перенаправляємо в головне меню." << "\n";
        goto menu;
        
    }
} while (option != 0); 
return 0;

}