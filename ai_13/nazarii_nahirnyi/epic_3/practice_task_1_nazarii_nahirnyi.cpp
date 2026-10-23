/*
    Задача: Статистика витрат
    Автор: Нагірний Назарій
    Група: СШІ-13
*/
#include <iostream>
#include <iomanip>
using namespace std;

void input(double &budget, int &n, double spending[]) { 
    cout<<"Введіть бюджет на місяць, грн ";
    cin >> budget;
    if(cin.fail()||budget<=0){
        cout<<"Помилка, введіть числове значення бюджету";
        return;
    }
    cout<<"Введіть кількість днів обліку ";
    cin >> n;
    if(cin.fail()||n<=0||n>31){
        cout<<"Помилка, введіть коректну кількість днів";
        return;
    }
    cout<<"Введіть витрати по днях, грн ";
    for(int i=0; i<n; i++) {
    cin >> spending[i];
    if(cin.fail()||spending[i]<0){
        cout<<"Помилка, введіть числові значення витрат";
        return;
    }
    }
}
void punkt1(double spending[], int n) {
    cout << "День\t\t Витрати, грн\n";
    for (int i=0; i<n; i++) {
        cout << "День "<< i + 1 << "\t\t" << fixed << setprecision(2) << spending[i] << "\n";
    }
}

void maxmin (int n, double &max, double &min, double spending[])
{
    max=spending[0];
    min=spending[0];
for (int i=0; i<n; i++){
if(spending[i]>max){max=spending[i];}
if(spending[i]<min){min=spending[i];}
}
}

double suma(int n, double spending[]){
if (n<=0) {return 0;}
return spending[n - 1] + suma(n-1, spending);
}

void punkt2(double budget, int n, double spending[]){
    double min=0;
    double max=0;
    double sum=0;
    double overspend=0;
    int spenddays=0;
    double average=0;
    maxmin (n, max, min, spending);
    sum = suma( n, spending);
    cout <<"Мінімальні витрати за день:\t"<<min<<"грн"<< endl;
    cout <<"Максимальні витрати за день:\t"<<max<<"грн"<< endl;
    cout <<"Сумарні витрати:\t\t"<< sum <<"грн"<< endl;
    if (sum > budget) {cout <<"Перевитрата понад бюджет:\t"<< abs(budget-sum) <<"грн"<< endl;}
    int d=0;
    for(int i = 0; i<n; i++){
        if (spending[i]==0) {continue;}
        average +=spending[i];
        d++;
    }
    cout <<"Днів з покупками:\t\t"<< d << endl;
    average /= d;
    cout <<"Середні витрати за такий день:\t"<< average << "грн" << endl;
    int i=0;
    sum=0;
    while(i<n) {
        if(budget>sum) {
        sum+=spending[i];
        i++;
        }
        else {break;}
    }
    cout <<"Бюджет вичерпано на дні "<< i << ", накопичено " << sum << " грн." << endl;
 }

void punkt3(int n, double spending[]){
double limit=0;
cout << "Введіть денний ліміт ";
cin >> limit;
if (cin.fail()||limit<=0) {limit=1000;}
cout <<"Ліміт: "<< limit << " грн." << endl;
int c=0;
for (int i=0; i < n; i++) {
    if(spending[i]>limit){
    cout <<"день "<< i+1 << ": " << spending[i] << " грн" << endl;
    c++;
    }
}
cout <<"Разом днів з перевищенням: "<< c << endl;
}

void punkt4(int n, double spending[]){
    double spending2[31];
    for (int i=0; i<n; i++) {
        spending2[i]=spending[i];
    }
    double z =0;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if(spending2[i]>spending2[j]){
                z=spending2[j];
                spending2[j]=spending2[i];
                spending2[i]=z;
            }
        }
    }
    cout << "Топ-3 витрат: " << spending2[0];
    if(n>1){
    cout << ", " << spending2[1];}
    if(n>2){
    cout << ", " << spending2[2];}
} 

int main() {
    double budget;
    int n;
    double spending[31];
    char action; 

    input(budget, n, spending);

act:
    do {
        cout << "\n--- МЕНЮ ---\n";
        cout << "1\t" << "Показати витрати по днях" << endl;
        cout << "2\t" << "Статистика витрат" << endl;
        cout << "3\t" << "Дні з перевищенням денного ліміту" << endl;
        cout << "4\t" << "Три найдорожчі дні" << endl;
        cout << "0\t" << "Вийти" << endl;
        cout << "Виберіть дію: ";
        
        cin >> action;

        switch(action) {
            case '1':
                punkt1(spending, n);
                break;
            case '2':
                punkt2(budget, n, spending);
                break;
            case '3':
                punkt3(n, spending);
                break;
            case '4':
                punkt4(n, spending);
                break;
            case '0':
                cout << "Ви завершили програму" << endl;
                break;
            default:
                cout << "Такої дії не існує!" << endl;
                goto act;
        }
    } while (action != '0');

    return 0;
}