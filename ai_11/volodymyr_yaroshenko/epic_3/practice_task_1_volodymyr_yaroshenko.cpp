/*  
Практичне завдання
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void MAX_MIN(int spending[], int N, int &max, int &min) {
    min = spending[0];
    max = spending[0];
    for(int i =1; i<N;i++) {
        if(min>spending[i]) {
            min = spending[i];
    }
    }
    for(int i =1; i<N;i++) {
        if(max < spending[i]) {
            max = spending[i];
}
}
}// Знаходить мінімальні та максимальні витрати за день

int sum(int spending[], int N) {
    if(N == 0) {
        return 0;
    }
    return spending[N-1] + sum(spending, N-1);
}// Рекурсивно обчислює суму витрат за всі дні

void limit(int spending[], int N, double limits) {
    int count = 0;
    if(limits == 0) {
        limits = 1000;
        }
    cout << fixed << setprecision(2);
    cout << "\nЛіміт: " << limits << " грн\n\n";
    for(int i = 0; i < N; i++) {
if(spending[i] > limits) {
    cout << "  день " << i+1 << ": " << fixed << setprecision(2)<< (double)spending[i] << " грн"<< endl;
    count++;
    }
    }
    cout << "\nРазом днів з перевищенням: " << count << endl;
}// Виводить дні, у які витрати перевищили заданий ліміт

void case1(int spending[], int N) {
    cout << "\n" << left << setw(10) << "День" << right << setw(15) << "       Витрати, грн" << '\n';
for(int i = 1; i <= N; i++) {
cout << left << setw(10) << i << right << setw(15) << fixed << setprecision(2) << (double)spending[i-1] << '\n';
}
}// Виводить витрати по днях

void case2(int days, int day, int suma, int mid, int spending[],double budget, double N, int &max, int &min) {
days = 0;
mid = 0;
day = 0;
suma = 0;
MAX_MIN(spending ,N , max, min);
cout << fixed << setprecision(2)<< "Мінімальні витрати за день:       " << (double)min << " грн"<< endl;    
cout << fixed << setprecision(2)<< "Максимальні витрати за день:   " << (double)max << " грн" << endl;
cout << fixed << setprecision(2)<< "Сумарні витрати:               " << (double)sum(spending , N) << " грн"<< endl;

if(sum(spending , N) > budget) {
     cout << fixed << setprecision(2)<< "Перевитрата понад бюджет:      " << abs(budget - sum(spending , N)) << " грн"<< endl;
}
for(int i = 0; i < N; i++) {
    if(spending[i] ==0) {
    continue;}
    days++;
    mid += spending[i];
}
cout << "Днів з покупками:                    " << days << endl;
cout << fixed << setprecision(2) << "Середні витрати за такий день: " << (double)mid/days << " грн" << endl;
while(day != N) {
    suma += spending[day];
    if(suma > budget) {
        cout << fixed << setprecision(2) << "Бюджет вичерпано на дні " << day+1 << ", накопичено " << suma << " грн." << endl;
        break;
    }
    else if(day == N-1) {
        cout << fixed << setprecision(2) << "Залишок: " << budget-sum(spending , N) << " грн" << endl;
    }
    day++;
}
}// Виводить статистику витрат, середнє значення та стан бюджету

void case3( int N, int spending[], double limits) {
cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
cin >> limits;
limit(spending, N, limits);
}// Зчитує денний ліміт і викликає функцію його перевірки

void case4(int spending[], int N, int sorted[]) {
for(int i = 0; i < N; i ++) {
    sorted[i] = spending[i];
    }
for(int i = N-1; i > 0; i--) {
  for(int j = N-1; j > 0; j--) {
    if(sorted[j-1] < sorted[j]) {       
        int temp = sorted[j];
        sorted[j] = sorted[j-1];
        sorted[j-1] = temp;
}
}
}
if(N<3) {
    cout << fixed << setprecision(2)<< "Топ-3 витрат: ";
    for(int i = 0; i <N; i++) {
        cout << (double)sorted[i] << ", ";
    }
    cout << " грн" << endl;
}
else{
    cout << "Топ-3 витрат: "<< fixed << setprecision(2) << (double)sorted[0] << ", " << (double)sorted[1] 
    << ", " << (double)sorted[2] << " грн" << endl;
}
}// Сортує витрати за спаданням і виводить три найбільші значення
int main() {
int choice, min, max;
double mid = 0;
int days = 0;
int day = 0;
double suma = 0;
double limits = 0;
double budget, N; 
int spending[31];
int sorted[31];
cout << "Введіть бюджет: " << endl;
if (!(cin >> budget)) {
    cin.ignore(10000, '\n');
    cout << "Введіть число!\n";
    return -1;
}
if(budget< 0 ) {
    cout << "Введіть коректнe значення!" << endl;
    return -1;
}

cout << "Введіть кількість днів: " << endl;
if (!(cin >> N)) {
    cin.ignore(10000, '\n');
    cout << "Введіть число!\n";
    return -1;
}
if(N <=0  || N> 31) {
    cout << "Введіть коректнe значення!" << endl;
    return -1;
}

cout << "Введіть витрати по днях: " << endl;
for(int i =0; i < N; i++) {
    if (!(cin >> spending[i])) {
    cin.ignore(10000, '\n');
    cout << "Введіть число!\n";
    return -1;
}
    if(spending[i] < 0 ) {
    cout << "Введіть коректнe значення!" << endl;
    return -1;
}
}
do{ menu: // Mеню та виклик функції за вибором
cout << "1) " << "Показати витрати по днях"<< endl;
cout << "2) " << "Статистика витрат"<< endl;
cout << "3) " << "Дні з перевищенням денного ліміту"<< endl;
cout << "4) " << "Три найдорожчі дні"<< endl;
cout << "0) " << "Вийти"<< endl;
if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Введіть число\n";
        goto menu;
    }
switch(choice) {
case 1: 
case1(spending, N);
break;

case 2: 
case2(days, day, suma, mid, spending, budget, N, max, min);
break;

case 3:
case3(N, spending, limits);
break;

case 4: 
case4(spending, N, sorted);
break;

default:
    cout << "Неправильний пункт меню!" << endl;
    break;
}
}

while(choice !=0);  
return 0;
}