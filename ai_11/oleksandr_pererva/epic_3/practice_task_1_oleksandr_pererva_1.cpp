/*
Аналізатор місячного бюджету
Перерва Олександр
ШІ-11
*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cctype>

using namespace std;

void punkt1(double spending[], int N){
    cout<<"День"<<setw(30)<<"Витрати, грн"<<endl;
    for(int i=0;i<N;i++){
        cout<<setw(4)<<i+1<<setw(19)<<setprecision(2)<<spending[i]<<endl;
    }
}

double totalSpending(double spending[], int N){
    if(N==0) return 0;
    return spending[N-1] + totalSpending(spending, N-1); //рекурсивна функція обчислення суми витрат
}

void punkt2(double spending[], int N,double &min_spending,double &max_spending, double &budget){
    for(int i=0;i<N;i++){
        if(i==0 || spending[i]<min_spending) min_spending=spending[i];
        if(i==0 || spending[i]>max_spending) max_spending=spending[i];
    }
    double total=totalSpending(spending, N);
    double remainBudget=budget-total;
    int count=0;
    // Обчислення кількості днів з витратами
    for(int i=0;i<N;i++){
        if(spending[i]==0) continue;
        count++;
    }
    if(count==0){
        cout<<"Немає днів з витратами"<<endl;
        return;
    }
    double averageSpending=total/count;
    double budgetUsed=0;
    count=0;
    while(count<N){
        budgetUsed+=spending[count];
        count++;
        if(budgetUsed>=budget) break;
    }
    cout<<"Мінамільні витрати за день: "<<setw(19)<<setprecision(2)<<min_spending<<" грн"<<endl;
    cout<<"Максимальні витрати за день: "<<setw(18)<<setprecision(2)<<max_spending<<" грн"<<endl;
    cout<<"Сумарні витрати: "<<setw(30)<<setprecision(2)<<total<<" грн"<<endl;
    if(remainBudget<0) cout<<"Перевитрата понад бюджет: "<<setw(21)<<setprecision(2)<<fabs(remainBudget)<<" грн"<<endl;
    else cout<<"Залишок бюджету: "<<setw(30)<<setprecision(2)<<remainBudget<<" грн"<<endl;
    cout<<"Середні витрати за дні з покупками: "<<setw(11)<<setprecision(2)<<averageSpending<<" грн"<<endl;
    if(budgetUsed>=budget) cout<<"Бюджет вичерпано на дні "<<count<<", накопичено: "<<setw(8)<<setprecision(2)<<budgetUsed<<" грн."<<endl;
    else cout<<"Бюджету вистачило на всі дні, залишок: "<<setw(8)<<setprecision(2)<<budget-budgetUsed<<endl;

}

void punkt3(double spending[], int N, double limit=1000){
    int countLimit=0;
    cout<<"Ліміт: "<<setprecision(2)<<limit<<" грн"<<endl;
    for(int i=0;i<N;i++){
        if(spending[i]>limit){ // Дні з перевищенням ліміту
            cout<<"\t день "<<i+1<<": "<<setprecision(2)<<spending[i]<<" грн"<<endl;
            countLimit++;
        }
    }
    cout<<"Разом днів з перевищенням: "<<countLimit<<endl;
}

void punkt4(double spending[],int N, const int MAX){
    double spendingCopy[MAX], t; 
    for(int i=0;i<N;i++) spendingCopy[i]=spending[i];
    // сортування копії масиву
    for(int i=0;i<N-1;i++){
        for(int j=0;j<N-1-i;j++){
            if(spendingCopy[j]<spendingCopy[j+1]){
                t=spendingCopy[j];
                spendingCopy[j]=spendingCopy[j+1];
                spendingCopy[j+1]=t;
            }
        }
    }
    cout<<"Топ-3 витрат: ";
    for(int i=0;i<N;i++){
        cout<<setprecision(2)<<spendingCopy[i];
        if(!(i>1 || i>N-2)) cout<<", ";
        if((i>=2 || i>=N)) break;
    }
    cout<<" грн"<<endl;
}

int main(){
    const int MAX=31; // максимальна кількість днів
    int N; // кількість днів
    double budget,spending[MAX], min_spending, max_spending, limit; // бюджет, витрати по днях, мінімальні і максимальні витрати, діміт витрат
    int menuInput;
    bool exit=false;
    cout<<fixed<<setprecision(2);
    // Ввід даних про бюджет
    input:
            cout<<"==================================================="<<endl;
            cout<<"Бюджет на місяць (грн): "; 
            if(!(cin>>budget) || budget<=0){
                cin.clear();
                cin.ignore(10000, '\n');
                cout<<"Бюджет має бути числом більшим за 0"<<endl;
                goto input;
            }
            cout<<"Кількість днів обліку: "; 
            if(!(cin>>N) || N<=0 || N>31){
                cin.clear();
                cin.ignore(10000, '\n');
                cout<<"Кількість днів обліку має бути цілим числом від 1 до 31"<<endl;
                goto input;
            }
            cout<<"Витрати по днях (грн): ";
            for(int i=0;i<N;i++){
                if(!(cin>>spending[i]) || spending[i]<0){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout<<"Витрати мають бути числом не меншими за 0"<<endl;
                    goto input;
                }
            }
    // Меню
    do{
        menu:
            cout<<"==================================================="<<endl;
            cout<<"Введіть число: \n1 - Показати витрати по днях\n2 - Статистика витрат\n3 - Дні з перевищенням денного ліміту\n4 - Три найдорожчі дні\n0 - Вихід з програми\nВаш вибір: "; 
            // валідація вводу
            if(!(cin>>menuInput) || menuInput<0 || menuInput>4){
                cin.clear();
                cin.ignore(10000, '\n');
                cout<<"Помилка: введіть ціле число від 0 до 4"<<endl;
                goto menu; 
            }
            cout<<endl;
            if(menuInput==0) exit=true;
            if(menuInput==1) punkt1(spending,N);
            if(menuInput==2) punkt2(spending, N, min_spending, max_spending, budget);
            if(menuInput==3){
                cout<<"Денний ліміт (грн, 0 = за замовчуванням): ";
                if(!(cin>>limit) || limit<0){
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout<<"Помилка: ліміт має бути невід'ємним числом\n==================================================="<<endl;
                    goto menu;
                }
                if(limit==0) punkt3(spending, N);
                else punkt3(spending, N, limit);
            }
            if(menuInput==4) punkt4(spending, N, MAX);                 
    } while(!exit); 
}       