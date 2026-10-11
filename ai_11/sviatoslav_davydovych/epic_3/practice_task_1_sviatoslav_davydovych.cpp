#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

void print_formatted(const string& text, int text_width, double value, int value_width, const string& tail) {
    int extra_bytes = 0;
    
    // рахуємо кількість кириличних символів:
    // другий байт кирилиці лежить в межах [128; 191]
    for (unsigned char c : text) {
        if (c >= 128 && c <= 191) {
            extra_bytes++;
        }
    }

    int corrected_text_width = text_width + extra_bytes;

    cout << left << setw(corrected_text_width) << text << right << setw(value_width) << value << tail << "\n";
}

// очищує потік cin для повторного вводу після помилки
void clean_cin() {
    cin.clear();
    cin.ignore(10000, '\n');
}

// 1 пункт меню
void show_spending(double spending[],int n){
    cout << "День      Витрати, грн\n";
    for (int i = 0; i<n; i++){
        cout << right << setw(5) << i+1 << setw(15) << spending[i] << "\n";
    }
}

// 2 пункт меню
void show_statystic(double min, double max, double sum, double overrun, int looses_days, double average, int critical_day, double critical_sum) {
    print_formatted("Мінімальні витрати за день: ", 35, min, 8, " грн");
    print_formatted("Максимальні витрати за день: ", 35, max, 8, " грн");
    print_formatted("Сумарні витрати ", 35, sum, 8, " грн");
    if (overrun>0) {
        print_formatted("Перевитрата понад бюджет: ", 35, overrun, 8, " грн");
    }
    cout << fixed << setprecision(0);
    print_formatted("Днів з покупками: ", 35, looses_days, 8 ," д.");
    cout << fixed << setprecision(2);

    print_formatted("Середні витрати за такий день: ", 35, average, 8 ," грн");
    if (overrun>0) {
        cout << "Бюджет вичерпано на дні " << critical_day << ", накопичено " << critical_sum << " грн\n";
    }
}

// 3 пункт меню
void show_limits(double spending[],int n, double limit = 1000){
    print_formatted("Ліміт", 10, limit, 5, " грн");
    for (int i = 1; i<=n; i++){
        if(spending[i-1]>limit) print_formatted("день "+to_string(i)+": ", 10, spending[i-1], 5, " грн");
    }
}

// 4 пункт меню
void show_max_spend(double spending[],int n){
    double copy[n];
    // копіюємо масив через цикл
    for (int i = 0; i<n; i++){
        copy[i]=spending[i];
    }
    // реалізація сортування вибором
    for (int i = 0; i<n; i++){
        int max_id = i;
        for (int j = i; j<n; j++){
            if (copy[j]>copy[max_id]) max_id=j;
        }
        double temp = copy[max_id];
        copy[max_id] = copy[i];
        copy[i] = temp;
    }

    cout << "топ-3 витрат: " << copy[0] << ", " << copy[1] <<", " << copy[2] << " грн\n";
}

void do_min_spend(double spending[],int n, double& p){
    double min = spending[0];
    for (int i = 0; i<n;i++){
        if (spending[i]<min) min = spending[i];
    }
    p = min;
}

void do_max_spend(double spending[],int n, double& p){
    double max = spending[0];
    for (int i = 0; i<n;i++){
        if (spending[i]>max) max = spending[i];
    }
    p = max;
}

double rec_sum_spending(const double spending[],int n, int index){
    if (index==n-1) return spending[index];

    return spending[index]+rec_sum_spending(spending,n,index+1);
}

void do_sum_spending(double spending[],int n, double& p){
    double sum = 0;
    p = rec_sum_spending(spending, n, 0);
}

void do_overrun(double cost, double budget, double& p){
    if (budget-cost>=0) p = 0;
    else p = abs(budget-cost);
}

void count_day(double spending[],int n, int& p){
    int c = 0;
    for (int i = 0; i<n;i++){
        if (spending[i]>0) c++;
    }
    p = c;
}

void do_average_cost(double sum,int days, double& p){
    p = sum/days;
}

void do_critical_data(double limit, double spending[],int n, int& p, double& sum){
    double acc = 0;
    for (int i = 1; i<=n;i++){
        acc+=spending[i-1];
        if (acc>limit) {
            p = i;
            break;
        };
    }
    if (acc<limit) p = -1;
    sum = acc;
}

int main() {
    // конструкція R"()" є аналогом багаторядкового тексту в c++
    const string MenuText = R"(Оберіть дію: 
    1 - Показати витрати по днях
    2 - Статистика витрат
    3 - Дні з перевищенням денного ліміту
    4 - Три найдорожчі дні
    0 - Вийти)";
    // встановлюємо точність виводу
    cout << fixed << setprecision(2);

    double budget;
    int N;
    double min_spend, max_spend, sum, overrun,average,critical_sum;
    int looses_days,critical_day;

    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    if (cin.fail() || budget<0 || budget>=1e10){
        cout << "Помилка вводу, введіть додатне число до 10 млрд.\n";
        return 1;
    }

    cout << "Кількість днів обліку: ";
    cin >> N;
    if (cin.fail() || N<1 || N>=31){
        cout << "Помилка вводу, введіть кількість від 1 до 31\n";
        return 1;
    }
    double spending[N];

    cout << "Витрати по днях (грн): ";
    for (int i = 0;i<N;i++){
        double spend;
        cin >> spend;
        if (cin.fail() || spend<0 || spend>=1e10){
            cout << "Помилка вводу, введіть додатне число до 10 млрд.\n";
            return 1;
        }
        spending[i] = spend;
    }

    do_min_spend(spending,N,min_spend);
    do_max_spend(spending,N,max_spend);
    do_sum_spending(spending,N,sum);
    do_overrun(sum, budget, overrun);
    count_day(spending,N,looses_days);
    do_average_cost(sum,looses_days,average);
    
    if (overrun>0){
        do_critical_data(budget,spending,N,critical_day,critical_sum);
    }

    int action;
    do{
        menu:
        cout << MenuText << "\n";
        cin >> action;
        if (cin.fail()){
            clean_cin();
            goto menu;
        }

        switch (action)
        {
        case 1:
            show_spending(spending, N);
            break;
        case 2:
            show_statystic(min_spend, max_spend, sum, overrun, looses_days, average, critical_day, critical_sum);
            break;
        case 3:
            cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
            double limit;
            cin >> limit;

            if (cin.fail()){
                clean_cin();
                goto menu;
            }

            if (limit == 0) show_limits(spending, N);
            else show_limits(spending, N, limit);

            break;
        case 4:
           show_max_spend(spending, N); 
        }
    } while (action!=0);

    return 0;
}