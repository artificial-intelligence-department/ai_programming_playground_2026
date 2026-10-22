/*
Задача: Аналізатор місячного бюджету
Автор: Хробуст Андрій
Група ШІ-11 
*/
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//Виведення списку витрат(кнопка 1)
void showSpendings(double spendings[], int n) {
    cout<<"День   Витрати, грн"<<endl;
    for(int i=0;i<n;i++){
        cout<<i+1<<"   "<<fixed<<setprecision(2)<<spendings[i]<<endl;
    }
}

//Рекурсивне обчислення суми витрат(для кнопки 2)
double sumSpendings(double spendings[], int n) {
    if (n==0) {
        return 0;
    }
    return spendings[n-1] + sumSpendings(spendings,n-1);
}

//Пошук мінімуму та максимуму через посилання(для кнопки2)
void findMinMax(double spendings[],int n,double &min,double &max){
    min=spendings[0];
    max=spendings[0];
    for(int i=1;i<n;i++){
        if(spendings[i]<min) min=spendings[i];
        if(spendings[i]>max) max=spendings[i];
    }
}

//Загальна статистика бюджету(кнопка 2)
void showStats(double spendings[],int n,double budget){
    double sum=sumSpendings(spendings,n);
    double min;
    double max;
    findMinMax(spendings,n,min,max);
    double overspend=0;
    if(sum>budget){
        overspend=abs(sum-budget);
    }
    double shoppingSum=0;
    int purchaseDays=0;
    for(int i=0;i<n;i++){
        if(spendings[i]==0){
            continue;
        }

        shoppingSum+=spendings[i];
        purchaseDays++;
    }
    double average=0;
    if(purchaseDays>0){
        average=shoppingSum/purchaseDays;
    }
    double budgetSum=0;
    int i=0;
    int exhaustedDay=0;
    while(i<n){
        budgetSum+=spendings[i];
        if(budgetSum>=budget){
            exhaustedDay=i+1;
            break;
        }
        i++;
    }
    cout<<"Мінімальні витрати за день: "<<min<<" грн"<<endl;
    cout<<"Максимальні витрати за день: "<<max<<" грн"<<endl;
    cout<<"Сумарні витрати: "<<sum<<" грн"<<endl;
    cout<<"Перевитрата понад бюджет: "<<overspend<<" грн"<<endl;
    cout<<"днів з покупками: "<<purchaseDays<<endl;
    cout<<"Середні витрати за такий день: "<<average<<" грн"<<endl;
    if(exhaustedDay>0){
        cout<<"Бюджет вичерпано на дні: "<<exhaustedDay<<"; Накопичено: "<<budgetSum
        <<" грн"<<endl;
    }
    else{
        cout<<"Бюджет не вичерпано;"<<"Залишок бюджету: "<<budget-sum<<" грн"<<endl;
    }
}

//Дні з перевищенням денного ліміту(кнопка 3)
void showOverLimit(double spendings[],int n,double limit=1000){
    int count=0;
    cout<<fixed<<setprecision(2);
    cout<<"Ліміт: "<<limit<<" грн"<<endl;
    for(int i=0;i<n;i++){
        if(spendings[i]>limit){
            cout<<"  день "<<i+1<<": "<<spendings[i]<<" грн"<<endl;
            count++;
        }
    }
    cout<<"Разом днів з перевищенням: "<<count<<endl;
}

//сортування бульбашкою(для кнопки 4)
void bubbleSort(double spendings[],double copy[],int n){
    for(int i=0;i<n;i++){
        copy[i]=spendings[i];
    }
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(copy[j]<copy[j+1]){
                double save=copy[j];
                copy[j]=copy[j+1];
                copy[j+1]=save;
            }
        }
    }
}

//Три найдорожчі дні(кнопка 4)
void showTop3(double spendings[],int n){
    double copy[31];
    bubbleSort(spendings,copy,n);
    cout<<fixed<<setprecision(2);
    cout<<"Топ-3 витрат: ";
    int count=3;
    if(n<3){
    count=n;
    }
    for(int i=0;i<count;i++){
        cout<<copy[i]<<" ";
    }
    cout<<" грн"<<endl;
}


int main() {
    cout<<fixed<<setprecision(2);
    double budget;
    cout<<"Введіть бюджет: ";
    cin>>budget;
    while(cin.fail() || budget<0){
        cout<<"Помилка! Введіть невід'ємне число: ";
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>budget;
    }
    int n;
    cout<<"Кількість днів (1-31): ";
    cin>>n;
    while(cin.fail() || n<1 || n>31){
        cout<<"Помилка! Введіть число від 1 до 31: ";
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>n;
    }
    cout<<"Витрати по днях (грн): ";
    double spendings[31];
    for(int i=0;i<n;i++){
    cin>>spendings[i];
    while(cin.fail() || spendings[i]<0){
        cout<<"Помилка! Введіть невід'ємне число: ";
        cin.clear();
        cin.ignore(10000,'\n');
        cin>>spendings[i];
    }
    }
    int choice;
    do{
 menu:
        cout<<endl;
        cout<<"===== МЕНЮ ====="<<endl;
        cout<<"1. Показати витрати по днях"<<endl;
        cout<<"2. Статистика витрат"<<endl;
        cout<<"3. Дні з перевищенням денного ліміту"<<endl;
        cout<<"4. Три найдорожчі дні"<<endl;
        cout<<"0. Вийти"<<endl;
        cout<<"Ваш вибір: ";
        if(!(cin>>choice)){
            cout<<"Помилка! Введіть номер пункту меню."<<endl;
            cin.clear();
            cin.ignore(10000,'\n');
            goto menu;
        }
        switch(choice){
            case 1:
                showSpendings(spendings,n);
                break;
            case 2:
                showStats(spendings,n,budget);
                break;
            case 3:{
                double limit;
                cout<<"Введіть денний ліміт (0 = за замовчуванням 1000 грн): ";
                cin>>limit;  
                if(limit<0){
                cout<<"Помилка: ліміт не може бути від'ємним"<<endl;
                } 
                else if(limit==0){
                showOverLimit(spendings,n);
                }
                else{
                showOverLimit(spendings,n,limit);
                }
                break;
            }
            case 4:
                showTop3(spendings,n);
                break;
            case 0:
                cout<<"Програму завершено."<<endl;
                break;
            default:
                cout<<"Помилка! Введіть номер пункту меню."<<endl;
                goto menu;
        }
    }while(choice!=0);

    return 0;
}