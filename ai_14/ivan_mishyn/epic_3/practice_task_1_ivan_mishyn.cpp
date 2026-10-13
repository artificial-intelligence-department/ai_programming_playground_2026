#include <iostream>
#include <iomanip>
using namespace std;

void input(double &budget, int &N, double spending[]){
read_budget:
    cout<<"Бюджет на місяць (грн): ";
    cin>>budget;
    if(cin.fail()||budget<0){
        cout<<"Помилка вводу. Значення мусить бути більше 0\n";
        cin.clear();
        cin.ignore(1000,'\n');
        goto read_budget;
    }
read_N:
    cout<<"Кількість днів обліку: ";
    cin>>N;
    if(cin.fail()||N<1||N>31){
        cout<<"Помилка вводу. Значення мусить бути від 1 до 31\n";
        cin.clear();
        cin.ignore(1000,'\n');
        goto read_N;
    }
    cout<<"Витрати по днях (грн): ";
    for(int i=0; i<N; i++){
    read_spending:
        cin>>spending[i];
        if(cin.fail()||spending[i]<0){
            cout<<"Помилка вводу. Значення мусить бути більше 0\n";
            cin.clear();
            cin.ignore(1000,'\n');
            goto read_spending;
        }
    }

}

//Показати витрати по днях
void spendings_by_day(int N, double spending[]){
   cout<< "День     Витрати, грн\n";
   for(int i=0; i<N;i++){
    cout<<i+1<<"        "<<spending[i]<<"\n";
   }
}


// сума масива
double sum(const double arr[], int n) {
    if (n <= 0) return 0.0;
    double result = arr[n - 1] + sum(arr, n - 1);
    return result;
}

void findMinMax(const double arr[], int n, double &minVal, double &maxVal) {
    minVal = arr[0];
    maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }
}

// статистика витрат
void stats(double budget, int N, const double spending[]) {
    double minVal;// мінімум за день
    double maxVal;// максимум за день
    findMinMax(spending, N, minVal, maxVal);

    double totalSpending = sum(spending, N);//сумарні витрати

    double balance = budget - totalSpending;    // залишок або перевитрата

    //дні з покупками
    int purchaseDays = 0;
    for (int i = 0; i < N; i++) {
        if (spending[i] == 0.0) {
            continue;
        }
        purchaseDays++;
    }
    //середні витрати
    double avgSpending = (purchaseDays > 0) ? (totalSpending / purchaseDays) : 0.0;

    //пошук дня вичерпання бюджету
    int dayExceed = 0;
    double summ = 0;
    bool isExceed = false;
    while (summ <= budget) {
        summ += spending[dayExceed];
        dayExceed++;
        if (summ > budget) {
            isExceed = true;
            break;
        }
        if (dayExceed >= N) {
            break;
        }
    }

    // Вивід
    cout << "\nМінімальні витрати за день:     " << minVal << " грн\n";
    cout << "Максимальні витрати за день:     " << maxVal << " грн\n";
    cout << "Сумарні витрати:                 " << totalSpending << " грн\n";

    if (totalSpending > budget) {
        cout << "Перевитрата понад бюджет:        " << -balance << " грн\n";
    } else {
        cout << "Залишок бюджету:                 " << balance << " грн\n";
    }

    cout << "Днів з покупками:                " << purchaseDays << "\n";
    cout << "Середні витрати за такий день:   " << avgSpending << " грн\n";
    if (isExceed == true) {
        cout << "Бюджет вичерпано на дні " << dayExceed << ", накопичено " << summ << " грн.\n";
    } else {
        cout << "Бюджету вистачило на всі дні, залишок: " << budget - summ << " грн.\n";
    }
}



//Дні з перевищенням денного ліміту
void overFlow( int N, double spending[],double limit = 1000){
    cout<<"\nЛіміт: "<<limit<<" грн\n";
    int nOverFlow=0;
    for(int i=0; i<N;i++){
        if(spending[i]>limit){
            cout<<"  день "<<i+1<<": "<<spending[i]<<" грн\n";
            nOverFlow++;
        }
    }
    cout<<"\nРазом днів з перевищенням: "<<nOverFlow<<"\n";
}

// Вивід 3 найдорожчих днів
void sort3(int N, double spending[]){
    double sspending[31];
    for (int i=0; i<N; i++){
        sspending[i]=spending[i];
    }
    for(int j =0; j<N-1;j++){
        for(int i=0;i<N-1-j;i++){
            if(sspending[i]<sspending[i+1]){
                double temp =sspending[i];
                sspending[i]=sspending[i+1];
                sspending[i+1]=temp;
            }
        }
    }
    int nOut=(N>=3)? 3:N;
    cout<<"\nТоп-3 витрат:";
    for (int i=0;i<nOut;i++){
        cout<<" "<<sspending[i];
    }
    cout<<" грн\n";
    
}


int main(){
    cout << fixed << setprecision(2);
    double budget;
    int N;
    double spending[31];
    input(budget, N, spending);
    int menu=0;
    double userLimit;
 do{    
 menu:
    cout<<"\nВиберіть операцію\n"<<
    "1 - Показати витрати по днях\n"<<
    "2 - Статистика витрат\n"<<
    "3 - Дні з перевищенням денного ліміту\n"<<
    "4 - Три найдорожчі дні\n"<<
    "0 - Вийти\n";
    cin>>menu;
    switch(menu){
        case 1:
        spendings_by_day(N, spending);
        break;
        case 2:
        stats(budget, N, spending);
        break;
        case 4:
        sort3(N,spending);
        break;
        case 0:
        break;
        case 3:
    read_limit:
        cout<<"\nДенний ліміт (грн, 0 = за замовчуванням): ";
        cin>> userLimit;
        if(cin.fail()|| userLimit < 0){
        cout<<"Помилка вводу. Значення мусить бути додатнім\n";
        cin.clear();
        cin.ignore(1000,'\n');
        goto read_limit;
        }
        if(userLimit==0){
            overFlow(N, spending);
        }
        else{
            overFlow(N, spending, userLimit);
        }

        break;
        default:
        cout<<"Помилка вводу. Значення мусить відповідати одному з запропонованих\n";
        cin.clear();
        cin.ignore(1000,'\n');
        goto menu;
    }
   } while (menu != 0);
    return 0;
}