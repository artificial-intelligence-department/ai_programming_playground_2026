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
#include <sstream>

using namespace std;

const int max_day = 31;          
const double defLim = 1000;  
double bug = 0;                  
int getlin(string getl1);        

//введення і тд
 double bg(){
    bool error = false;
    double budget = 0;
    string trash;
    do{
    error = false;
    cout << "Введіть бюджет на місяць, грн: ";
    cin >> budget;
    if(cin.fail()){
    cout << "Введіть значення бюджету числом." << endl;
    cin.clear();
    getline(cin, trash);
    error = true;
    }
    else if(budget < 0){ 
    cout << "Значення бюджету не може бути менше 0." << endl;
    error = true;
    }
    }
    while(error == true);
    return budget;
 }

 int track(){
    bool error = false;
    int N = 0;
    string trash;
    do{
    error = false;
    cout << "Введіть кількість днів обліку: ";
    cin >> N;
    if(cin.fail()){
    cout << "Введіть кількість днів цілим числом." << endl;
    cin.clear();
    getline(cin, trash);
    error = true;
    }
    else if(N <= 0){ 
    cout << "Кількість днів не може бути менше 1." << endl;
    error = true;
    }
    else if(N > max_day){ 
    cout << "Кількість днів не може бути більше " << max_day << "." << endl;
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
    cout << "Некоректне значення для дня ";
    for(int i = 0; i < N; i++){
    if(spending[i] == -1){ 
    if(coma == true) cout << ", ";
    cout << i + 1;
    coma = true;
    done = true;
    }
    }
    
    cout << ". Введіть витрати знову:  ";
    a = 1;
    cost(spending, N);
    }

    if(spend2 == true && done == false){
        cout <<  "Замало значень: потрібно " << N << ", введено " << getl2 << ". Введіть витрати знову: ";
        a = 1;
        cost(spending, N);
    }

    if(spend3 == true && done == false){
        cout <<  "Забагато значень: потрібно " << N << ", введено " << getl2 << ". Введіть витрати знову: ";
        a = 1;
        cost(spending, N);
    }
 }

 void cost(double spending[], int N){
    bool spend1, spend2, spend3;
    string getl1;
    int getl2 = 0;
    if (a == 0) cin.ignore();
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
        stringstream ss(getl1);
        string word;
        double cash;
        int i = 0;
        while(i < N && ss >> word){
            stringstream num(word);
            num >> cash;
            
            if(num.fail() || !num.eof() || cash < 0){
                spending[i] = -1;
                spend1 = true;
            }
            else spending[i] = cash;
            i++;
        }
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
    int len4 = 0;
    if(len3 == 0) len4 = 1;
    while(len3 > 0){
        len3 /= 10;
        len4++;
    }
    return len4;
 }

 void expenses(double spending[], int N){
    int length = maxLen(spending, N) + 5;
    if (length < 12) length = 12;

    cout << setw(14) << "День"  <<"  "<< setw(length + 10) << "Витрати, грн" << endl;
    cout << fixed << setprecision(2);
    for(int i = 0; i < N; i++){
        cout << setw(10) << i + 1 <<"  " << setw(length) << spending[i] << endl;
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
    double diff = bug - sum;
    cout << fixed << setprecision(2);
    if(diff > 0){
        cout << left << "Залишок становить " << right << diff << " грн" << endl;
    }
    else if(diff == 0) cout << "Всі кошти витрачено." << endl;
    else{
        cout << left << "Перевитрата становить " << right << diff << " грн" << endl;
    }
  }
  
  double mid(double spending[], int N, int &k){
    double middle = 0;
    for(int i = 0; i < N; i++){
        if(spending[i] == 0) continue;
        k++;
    }
    if(k == 0){
        cout << "Відсутні витрати протягом вказаних днів." << endl;
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

    if(sum <= bug){
        cout << "Бюджету вистачило на всі дні." << endl;
    }
    else cout << "Бюджет скінчився на " << i + 1 << "-й день" << endl;
  }

 void statistic(double spending[], int N){
    double min = 0, max = 0;
    int k = 0;
    MinMax(spending, N, min, max);
    double Mid = mid(spending, N, k);

    cout << fixed << setprecision(2);
    cout << left <<  "Мінімальні витрати за день: " << right << min << " грн" <<endl;
    cout << left <<  "Максимальні витрати за день: " << right << max << " грн" <<endl;
    cout << left <<  "Сумарні витрати: " << right << sumSpend(spending, N) << " грн" <<endl;
    balance(spending, N);
    cout << left <<  "Днів з покупками: " << right << k <<endl;
    cout << left <<  "Середні витрати за день: " << right << Mid << " грн" <<endl;
    dayLim(spending, N);
 }

 void Lim(double spending[], int N){
    double lim = 0;
    int pen = 0;
    string trash;
  lim:
    cout << "Денний ліміт(грн, 0 = за замовчуванням): ";
    cin >> lim;
    if(cin.fail()){
        cout << "Введіть ліміт числом." << endl;
        cin.clear();
        getline(cin, trash);
        goto lim;
    }
    getline(cin, trash);
    if(lim < 0){
        cout << "Ліміт не може бути менше 0." << endl;
        goto lim;
    }
    if(lim == 0) lim = defLim;

    cout << "Ліміт: " << lim << " грн" << endl;

    for(int i = 0; i < N; i++){
    if(spending[i] > lim){ 
    cout << "день " << i + 1 << ": " << spending[i] << " грн" << endl;
    pen++;
    }
    }
    if(pen == 0) cout << " - " << endl;
    cout << endl << "Разом днів з перевищенням: " << pen << endl;
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
        else cout << " грн" << endl;
    }
 }

 void status(double spending[], int N, int &def){
    int menu = 0;
    string trash;

  menu:
    cout << endl << "1 - Показати витрати по днях " << endl << "2 - Статистика витрат " << endl << "3 - Дні з перевищенням денного ліміту " << endl << "4 - Три найдорожчі дні" << endl << "0 - Вийти " << endl;
    cin >> menu;
    if(cin.fail()){
        cout << "Введіть одне з запропонованих значень!" << endl;
        cin.clear();
        getline(cin, trash);
        goto menu;
    }
    
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
    double spending[max_day];
    int def = 0;
    bug = bg();
    const int N = track();
    cost(spending, N);

    do{
        status(spending, N, def);
    }
    while(def != 1);

    return 0;
}