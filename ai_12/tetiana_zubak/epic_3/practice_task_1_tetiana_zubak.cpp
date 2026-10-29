/*
Аналізатор місячного бюджету
Зубак Тетяна
ШІ-12
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <locale>

using namespace std;

const int max_day = 31;          
const double defLim = 1000;

//введення і тд
 float bg(){
    bool error = false;
    float budget = 0;
    do{
    error = false;
    cout << "Введіть бюджет на місяць, грн: ";
    cin >> budget;
    if(budget < 0){ 
    cout << "Значення бюджету не може бути менше 0." << endl;
    error = true;
    }
    }
    while(error == true);
    return budget;
 }

 double bug = bg();

 int track(){
    bool error = false;
    int N = 0;
    do{
    error = false;
    cout << "Введіть кількість днів обліку: ";
    cin >> N;
    if(N <= 0){ 
    cout << "Кількість днів не може бути менше 1." << endl;
    error = true;
    }
    else if(N > max_day){ 
    cout << "Кількість днів не може бути більше 31." << endl;
    error = true;
    }
    }
    while(error == true);
    return N;
 }

 void cost(double spending[], int N);

 int a = 0;
 bool done = true;

 void spendTrue(double spending[], int N, bool &spend1, bool &spend2, bool &spend3, int getl2, int &a){
    bool coma = false;

    if(spend1 == true){
    spend1 = false;
    cout << "Введіть коректне значення для дня ";
    for(int i = 0; i < N; i++){
    if(spending[i] == -1){ 
    if(coma == true) cout << ", ";
    cout << i + 1;
    coma = true;
    done = true;
    }
    }
    
    cout << ": ";
    for(int i = 0; i < N; i++){
        if(spending[i] == -1){ 
        cin >> spending[i];
        if(spending[i] < 0){ 
        spending[i] = -1;
        spend1 = true;
        }
        }
    }
    a = 1;
    cost(spending, N);
    }

    if(spend2 == true && done == false){
        int x = N - getl2;
        cout <<  "Додайте " << x << " значень: ";
        a = 1;
        cost(spending, N);
    }

    if(spend3 == true && done == false){
        int y = getl2 - N;
        cout <<  "Приберіть " << y << " лишні значення: ";
        a = 1;
        cost(spending, N);
    }
 }

 int getlin(string getl1);

 void cost(double spending[], int N){
    bool spend1, spend2, spend3;
    string getl1;
    int getl2 = 0;
    string trash;

    if(a == 0) getline(cin, trash);
    do{
    spend1 = false;
    spend2 = false;
    spend3 = false;
    done = true;
    if(a == 0)cout << "Введіть витрати по днях, грн: ";
    getline(cin, getl1);
    getl2 =  getlin(getl1);

    if(getl2 < N){
        spend2 = true;
        done = false;
    }
    else if(getl2 > N){
        spend3 = true;
        done = false;
    }
    else{
    cout << "Перевірку на співпадіння кількості днів і значень витрат пройдено, скопіюйте рядок: ";
    for(int i = 0; i < N ; i++){
        cin >> spending[i];
        if(spending[i] < 0){
            spending[i] = -1;
            spend1 = true;
            done = false;
        }
    }
    getline(cin, trash);
    }

    spendTrue(spending, N, spend1, spend2, spend3, getl2, a);
    }
    while((spend1 == true || spend2 == true || spend3 == true) && done == false);
 }

 int getlin(string getl1){
    int getl2 = 0;
    bool word = false;

    for(int i = 0; i < getl1.length(); i++){
        if(getl1[i] == ' ') word = false;
        else if(word == false){
            word = true;
            getl2++;
        }
    }
    return getl2;
}

//меню
 void arr(double spending[], int N, double minmax[], int max_day);

 int maxLen(double spending[], int N){
    double minmax[max_day];
    arr(spending, N, minmax, max_day);
    int len3 = minmax[N - 1];
    int len4 = 1;
    if(len3 == 0) len4 = 1;
    while(len3 > 0){
        len3 /= 10;
        len4++;
    }
    return len4;
 }

 void expenses(double spending[], int N){
    int length = maxLen(spending, N) + 12;
    
    cout << setw(8) << "День"  << setw(length + 10) << "Витрати, грн" << endl;
    cout << fixed << setprecision(2);
    for(int i = 0; i < N; i++){
        cout << setw(4) << i + 1 << endl << setw(length) << spending[i] << endl;
    }
 }

 //статистика 
  void MinMax(double spending[], int N, double &min, double &max){
    double minmax[max_day];
    arr(spending, N, minmax, max_day);
    min = minmax[0];
    max = minmax[N-1];
  }

  void arr(double spending[], int N, double minmax[], int max_day){
    for(int i = 0; i < N; i++){
        minmax[i] = spending[i];
    }

    for(int i = 1; i < N; i++){
        for(int j = 1; j < N; j++){
            if(minmax[j-1] > minmax[j]) swap(minmax[j-1], minmax[j]);
        }
    }
  }

  double sumSpend(double spending[], int N){
    if(N == 0) return 0;
    return spending[N-1] + sumSpend(spending, N-1);
  }

  void balance(double spending[], int N){
    double sum = sumSpend(spending, N);
    double diff = 0;
    if(bug > sum){
        diff = bug - sum;
        cout << left << setw(30) << "Залишок становить " << right << setw(10) << diff << " грн" << endl;
    }
    else if(bug == sum) cout << "Всі кошти витрачено." << endl;
    else{
        diff = abs(bug - sum);
        cout << left << setw(30) << "Перевитрата становить " << right << setw(10) << diff << " грн" << endl;
    }
  }
  
  double mid(double spending[], int N, int &k){
    double middle = 0;
    for(int i = 0; i < N; i++){
        if(spending[i] == 0) continue;
        k++;
    }
    if(k == 0){
        cout << "Відсутні витрати протягом вказаних днів.";
        middle = 0;
    }
    else{
    double sum = sumSpend(spending, N);
    middle = sum/k;
    }
    return middle;
  }

  void dayLim(double spending[], int N){
    double sum = 0;
    int i = 0;
    while(i < N){
        sum += spending[i];
        if(sum > bug) break;
        i++;
    }

    balance(spending, N);
    if(sum <= bug){
        cout << " Бюджету вистачило на всі дні.";
        balance(spending, N);
    }
    else cout << " Бюджет скінчився на " << i + 1 << " дні" << endl;
  }

 void statistic(double spending[], int N){
    double min = 0, max = 0;
    int k = 0;
    MinMax(spending, N, min, max);
    double Mid = mid(spending, N, k);

    cout << fixed << setprecision(2);
    cout << left << setw(30) <<  "Мінімальні витрати за день: " << right << setw(10) << min << " грн" <<endl;
    cout << left << setw(30) <<  "Максимальні витрати за день: " << right << setw(10) << max << " грн" <<endl;
    cout << left << setw(30) <<  "Сумарні витрати: " << right << setw(10) << sumSpend(spending, N) << " грн" <<endl;
    balance(spending, N);
    cout << left << setw(30) <<  "Днів з покупками: " << right << setw(10) << k <<endl;
    cout << left << setw(30) <<  "Середні витрати за такий день: " << right << setw(10) << Mid << " грн" <<endl;
    dayLim(spending, N);
 }

 void Lim(double spending[], int N){
    double lim;
    int pen = 0;

    cout << "Денний ліміт(грн, 0 = за замовчуванням): ";
    cin >> lim;
    if(lim == 0) lim = defLim;

    cout << "Ліміт: " << lim << " грн" << endl;

    for(int i = 0; i < N; i++){
    if(spending[i] > lim){ 
    cout << "день" << i + 1 << ": " << spending[i] << " грн" << endl;
    pen++;
    }
    if(lim == 0) cout << " - " << endl;
    cout << endl << "Разом днів з перевищенням:" << pen << endl;
 }
 }

 void top(double spending[], int N){
    double minmax[max_day];
    arr(spending, N, minmax, max_day);
    int k = 3;
    if(N < k) k = N;
    cout << fixed << setprecision(2);
    cout << "Топ-3 витрат: " << endl;
    for(int i = 0; i< k; i++){
        cout << minmax[N -1 -i];
        if(i < k - 1) cout <<", ";
        else cout << " грн";;
    }
 }

 void status(double spending[], int N, int &def){
    int menu = 0;

  menu:
    cout << endl << "1 - Показати витрати по днях " << endl << "2 - Статистика витрат " << endl << "3 - Дні з перевищенням денного ліміту " << endl << "4 - Три найдорожчі дні" << endl << "0 - Вийти " << endl;
    cin >> menu;
    switch(menu){
                case 1:
                    expenses(spending, N);
                    break;
                case 2:
                    statistic(spending, N);
                    break;
                case 3:
                    Lim(spending, N);
                    break;
                case 4:
                    top(spending, N);
                    break;          
                case 0:
                    def = 1;
                    break;
                default:{
                    cout << "Введіть одне з запропонованих значень!" << endl;
                    goto menu;
                }
            }
 }

int main(){
    setlocale(LC_ALL, "uk_UA");
    float budget = 0;
    double spending[max_day];
    int def = 0;

    const int N = track();
    cost(spending, N);

    do{
        status(spending, N, def);
    }
    while(def != 1);

    return 0;
}