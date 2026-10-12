/*"Аналізатор місячного бюджету"
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream>
#include <iomanip>
using namespace std;
//вивід витрат за кожен день
void Menu1(double spending[], int N){
    cout<<"День\t"<<"Витрати, грн"<<endl;
    for(int i=0; i<N; i++){
    cout<<i+1<<"\t"<<spending[i]<<endl;
}
}
//пошук мінімального та максимального значення за допомогою порівняння
void MinMaxSpending(const double spending[], int N, double &minValue, double &maxValue){
    minValue=spending[0];
    maxValue=spending[0];
    for(int i=1; i<N;i++){
        if(spending[i]<minValue){
            minValue=spending[i];
        }
        if(spending[i]>maxValue){
            maxValue=spending[i];
        }
    }
}
//сума усіх витрат, обчислена за допомогою рекурсії
double SumSpending(double spending[], int N){
    if(N == 0) return 0;
    return spending[N-1]+ SumSpending(spending, N-1);
}
//перевитрати
double OverSpending(double budget, double sum){
    if(sum>budget){
        return sum-budget;
    }
    return 0.00;
}
//дні з покупками
int PurchaseDays(double spending[], int N){
    int k=0;
    for(int i=0; i<N; i++){
        if(spending[i]>0)
        k++;
    }
    return k;
}
//середні витрати за день з покупками
double Average(double spending[], int N, int purchase){
    double suma=0;
    if(purchase==0) return 0;
    for(int i=0; i<N; i++){
        if(spending[i]==0) continue;
        else suma=suma+spending[i];
    }
    return suma/purchase;
}
//вихід за бюджет
void overBudget(double spending[], int N, double budget, double &sumabud, int &days){
    sumabud=0;
    days=0;
    int i=0;
    while(i<N){
        if(sumabud<budget){       
        sumabud=sumabud+spending[i];
        days++;
        i++;
        }
        //перериваємо цикл, коли знайшли день перевищення бюджету
        else break;
    }
}
//вихід за денний ліміт
void Menu3(double spending[], int N, double limit) {
    int k=0;
    for(int i=0; i<N; i++){
        if(spending[i]>limit){
            k++;
            cout<<"День "<<i+1<<": "<<spending[i]<<" грн"<<endl;
        }
    }
    cout<<"Разом днів з перевищенням: "<<k<<endl;
}
//сортування за спаданням, три найбільші суми
void SortValue(double spending[], int N) {
    double a[N];
    for(int i=0; i<N; i++) a[i]=spending[i];
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                double temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    if(N>=3) cout<<a[N-1]<<" "<<a[N-2]<<" "<<a[N-3]<<" грн"<<endl;
    else if(N==2) cout<<a[N-1]<<" "<<a[N-2]<<" грн"<<endl;
    else cout<<a[N-1]<<" грн"<<endl;
}
int main() {
    double budget;
    int N, menu;
    double spending[31];
    cout<<fixed<<setprecision(2);
    start1:
    cout<<"Бюджет на місяць (грн): ";
    if(!(cin>>budget)|| budget<0){
        cout<<"Помилка: введіть дійсне значення."<<endl;
        //скидання неправильного вводу та очищення буферу
        cin.clear();
        cin.ignore(10000,'\n');
        goto start1;
    }
    start2:
    cout<<"Кількість днів обліку: ";
    if(!(cin>>N)|| N<=0 || N>31){
        cout<<"Помилка: введіть дійсне значення.";
        cin.clear();
        cin.ignore(10000, '\n');
        goto start2;
    }
    start3:
    cout<<"Витрати по днях (грн): ";
    for(int i=0; i<N; i++){
        if(!(cin>>spending[i])||spending[i]<0){
            cout<<"Помилка: введіть дійсне значення."<<endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto start3;
    }
    }
    do {
    start:
    cout<<endl;
    cout<<"Меню"<<endl;
    cout<<"1 Покази витрат по днях"<<endl;
    cout<<"2 Статистика витрат"<<endl;
    cout<<"3 Дні з перевищенням денного ліміту"<<endl;
    cout<<"4 Три найдорожчі дні"<<endl;
    cout<<"0 Вийти"<<endl;
    if (!(cin>>menu)|| menu<0 || menu>4) {
        cout<<"Помилка: недійсне значення"<<endl;
            cin.clear();
            cin.ignore(10000, '\n');        
        goto start;
    }
    switch(menu){
        case 1: Menu1(spending, N);
        break;
        
        case 2:{
            double min, max;
            MinMaxSpending(spending, N, min, max);
            cout<<"Мінімальні витрати за день: \t"<<min<<" грн"<<endl;
            cout<<"Максимальні витрати за день: \t"<<max<<" грн"<<endl;
            double sum= SumSpending(spending, N);
            cout<<"Сумарні витрати: \t\t"<<sum<<"грн"<<endl;
            double over=OverSpending(budget, sum);
            cout<<"Перевитрата понад бюджет: \t"<<over<<" грн"<<endl;
            int purchase=PurchaseDays(spending, N);
            cout<<"Днів з покупками: \t\t"<<purchase<<endl;
            double aversum=Average(spending, N, purchase);
            cout<<"Середні витрати за такий день: "<<'\t'<<aversum<<" грн"<<endl;
            int days;
            double sumabud;
            overBudget(spending, N, budget, sumabud, days);
            cout<<"Бюджет вичерпано на дні "<<days<<", накопичено "<<sumabud<<" грн."<<endl;
            break;
        }
        case 3:{
            double limit;
            cout<<"Денний ліміт (грн 0 = за замовчуванням): ";
            cin>>limit;
            if (limit == 0)  limit = 1000;
            cout<<"Ліміт: "<<limit<<endl;
            Menu3(spending, N, limit);
            break;
        }
        case 4:
        cout<<"Топ-3 витрати: ";
        SortValue(spending, N);
        break;
    }
} while(menu!=0);
return 0;
}