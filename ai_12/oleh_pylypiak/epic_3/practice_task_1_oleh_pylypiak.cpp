/*  Practise task 
    Автор:Пилип'як Олег Васильович
    Група: ШІ-12, 3-тя група*/
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// 1. Показати витрати по днях
int tabl (int N, double spending []) {
    cout << "День\t" << "Витрати,грн" << endl;
    for (int i=0; i<N; i++) {
        cout << i+1 << "\t" << spending[i] << endl;
    }
    return 0;
} 
// 2. Статистика витрат
void findMinMax(int N, double spending[],double &min, double &max){
    min=spending[0];
    max=spending[0];
    for (int i=0; i<N; i++){
        if(spending[i] < min) min = spending[i];
        if(spending[i] > max) max = spending[i];
    }
    cout << "Мінімальні витрати за день: " << min << "грн" << endl;
    cout << "Максимальні витрати за день: " << max << "грн" << endl;
}
double totalspnd(int N, double spending[]){
    if(N<=0) return 0;
    return spending[N-1] + totalspnd(N-1,spending);
}
double remaining(double budget, double total){
    return fabs (budget - total);
}
void avgspnd(int N, double spending [],double total, double average){
    int count=0;
    for (int i=0; i<N; i++){
        if(spending[i]==0) continue;
        count++;
    }
    if(count>0) average=total/count;
    cout << "Днів з попуками: " << count << endl;
    cout << "Середні витрати за такий день: "<< average << "грн" << endl;
}

void Statsperevytraty(int N,double budget, double spending[],double total,double average,double min, double max){
    findMinMax(N, spending, min, max);
    double sum=0;
    int i=0,d=1;
    while(i<N){
    sum+=spending[i];
    if(sum>budget){
        cout << "Сумарні витрати: " << total << " грн" << endl;
        cout <<"Перевитрати понад бюджет: " << remaining(budget, total)<< " грн" << endl;
        avgspnd(N, spending, total, average);
        cout << "Бюджет вичерпано на дні " << d << ", накопичено " << sum << " грн." << endl;
        break;
    }
    i++;
    d++;
    }
    if(sum<=budget){
        cout << "Сумарні витрати: " << sum << " грн" << endl;
        avgspnd(N, spending, total, average);
        cout << "Залишок: "<< remaining(budget, total) << " грн" << endl;
    }
}
// 3. Дні з перевищенням денного ліміту
void Dlimits(int N, double spending[], double limit=1000){
    int count=0;
    cout << "Денний ліміт (грн, 0 = за замовчуванням): "<< endl;
    while (!(cin >> limit) || limit < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Помилка! Введіть невід'ємне число для ліміту: " << endl;
    }
    if (limit==0) limit=1000;
    for(int i=0; i<N; i++){
        if (spending[i]>limit){
            cout << "День " << i+1 <<": " << spending[i] << " грн"<< endl;
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count << endl;
}
// 4.Три найдорожчі дні
void Top3(int N,double spending[]){
    double spdcopy[31];
    for (int i=0; i<N; i++){
        spdcopy[i]=spending[i];
    }
    double temp;
    for(int i=0; i<N; i++){
        for(int j=0; j<N-1; j++){
            if(spdcopy[j] < spdcopy[j+1]){
                temp=spdcopy[j];
                spdcopy[j]=spdcopy[j+1];
                spdcopy[j+1]=temp;
            }
        }
    }
    cout << "Топ-3 витрат: ";
    for(int i=0; i<3; i++){
        if (i>=N) continue;
        cout << spdcopy[i];
        if (i<2 && i<N-1) cout << ", ";
    }
    cout << " грн" <<endl;
}

int main (){
    cout << fixed << setprecision(2);
    double budget;
    int N;
    double spending[31];
    double min, max;
    cout << "Бюджет на місяць(грн): " << endl;
    while (!(cin>> budget) || budget <0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка! Введіть додатне число для бюджету." << endl;
        }
    cout << "Кількість днів обліку: " << endl;
    while (!(cin >> N) || N <=0 || N > 31) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка! Введіть натуральне число менше 32." << endl;
        }
    cout << "Витрати по днях (грн): " << endl;
    for (int i=0; i<N; i++){
        while (!(cin>> spending[i]) || spending[i] <0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Помилка! Введіть додатне число для витрат." << endl;
        }
    }
    double total=totalspnd(N,spending);
    double average=0;
    double sum=0;
    int choise;
//меню
menu:
    do{
    cout<< "Меню"<< endl;
    cout<< "Пункт\tОперація"<<endl;
    cout<< "1\t"<<"Показати витрати по днях" <<endl;
    cout<< "2\t" <<"Статистика витрат" <<endl;
    cout<< "3\t" <<"Дні з перевищенням денного ліміту" <<endl;
    cout<< "4\t" <<"Три найдорожчі дні" <<endl;
    cout<< "0\t" <<"Вийти" <<endl;
    cin >> choise;
    if (cin.fail() || choise < 0 || choise > 4) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Помилка вводу! Введіть число від 0 до 4" << endl;
        goto menu;
        }
        switch (choise){
            case 1:
                tabl(N,spending);
                break;
            case 2:
                Statsperevytraty(N, budget, spending, total, average, min, max);
                break;
            case 3:
                Dlimits(N, spending);
                break;
            case 4:
                Top3(N, spending);
                break;
            case 0:
                cout << "Вихід з програми." << endl;
                break;
            default:
                goto menu;
        }
    }
    while(choise!=0); 
    return 0;
}