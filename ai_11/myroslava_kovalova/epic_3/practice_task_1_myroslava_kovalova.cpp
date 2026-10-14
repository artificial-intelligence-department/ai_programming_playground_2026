#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
void ShowTable(int N, float spendings[]);
void StatiisticsMinMax(int N,float spendings[],float &min,float &max);  //максимальне та мінімальне значення записуються за посиланням у min, max
float SumSpending(float spendings[],int n);                             //повертаємо суму через рекурсію, додаємо з кінця
void BudgetLeft(float sum_spend, float budget);                         //виводимо переватрати або залишок
float AvaregeMonth(float spendings[], int N, int &days_with_spend, float sum_spend); //повертаємо середні витрати за місяць, враховуємо лише дні з витратами. Через посилання записуєм кількість днів з витратами
void LastBudgDay(float spendings[], int N, float budget);               //виводить на якому дні вийшли за бюджет або надлишок бюджету
void OverLimit(int N, float spendings[], float limit = 1000);           //виводить дні з перевищенням бюджету
void CopySpendings(float spendings[],float copy_spendings[], int N);    //копіюємо масив у новий
void ThreeMaxSpendings(float copy_spendings[], int N);                  //працюємо з скопійованим масивом



int main(){
    float budget = 0;
    int N = 0;
    float spendings[31] ={0};

    // перевірка введень на діапазон, можна вводити доки не буде задовільне значення
    while(true){
        cout<<"Бюджет на місяць (грн): ";
        cin>>budget;
        if (budget<=0){   
            cout<<"Бюджет має бути додатнім числом"<<endl;
        }else break;
    }
        

    while(true){
        cout<<"Кількість днів обліку: ";
        cin>>N;
        if (N<=0 || N>31){   
            cout<<"Кількість днів ціле число від 1 до 31"<<endl;
        }else break;
    }

    while(true){
        cout<<"Витрати по днях (грн): ";
        for (int i =0; i<N; i++){
            cin>>spendings[i];
        }
        bool IsSpendingsRight = 1;
        for(int i = 0; i<N; i++){
            if(spendings[i]<0){
                IsSpendingsRight=0;
            }
        }
        if(IsSpendingsRight){
            break;
        }else{
            cout<<"Витрати мають бути додатнім числом";
        }
    }
    
    char choice = ' ';
    menu:
    do{
        cout<<"Меню\n1 Показати витрати по днях\n2 Статистика витрат\n3 Дні з перевищенням денного ліміту\n4 Три найдорожчі дні\n0 Вихід\n";
        cin>>choice;
        if (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '0') goto menu;

        switch(choice){
            case '1': {
            ShowTable(N, spendings);
            break;
            }

            case '2': {
            float min, max;
            StatiisticsMinMax(N,spendings,min, max);
            cout<<"Мінімальні витрати за день: "<<min<< " грн"<<endl;
            cout<<"Максимальні витрати за день: "<<max<< " грн"<<endl;

            float sum_spend = SumSpending(spendings, N-1); 
            cout<<"Сумарні витрати: "<<sum_spend<< " грн"<<endl;
            
            BudgetLeft(sum_spend,budget);

            int days_with_spend = 0;
            float avarege = AvaregeMonth(spendings,N, days_with_spend, sum_spend);
            cout<<"Днів з покупками: "<<days_with_spend<<endl;
            cout<<"Середні витрати за такий день: "<<avarege<<endl;

            LastBudgDay(spendings, N, budget);
            break;
            }
            
            case '3': {
            float limit = 0;
            while(true){
            cout<<"Денний ліміт (грн, 0 = за замовчуванням):";            
            cin>>limit;
            if(limit<0){
                cout<<"Ліміт має бути невід'ємним числом";
            }else break;
            }
            if (limit ==0){ 
                OverLimit(N, spendings);
            }else OverLimit(N, spendings, limit);
            break;
            }

            case '4': {
            float copy_spendings[31]={0};
            CopySpendings(spendings,copy_spendings, N);
            ThreeMaxSpendings(copy_spendings,N);
            break;
            }
            
            case '0': {
            cout<<"Ви вийшли з програми";
            break;
            }

            default:{
                cout<<"Повторіть ще раз. Доступні опції 1,2,3,4 або 0."<<endl;
                break;
            }
        }

    }while (choice!='0');


    return 0;
}

void ShowTable(int N, float spendings[]){
    cout<<"День "<<" Витрати, грн"<<endl;
    for(int i =0;i<N;i++){
        cout<<i+1<<"      "<<spendings[i]<<endl;
    }

}

void StatiisticsMinMax(int N,float spendings[],float &min,float &max){
    min =spendings[0];
    max = spendings[0];
    for(int i =1;i<N;i++){
        if(spendings[i]<min) min = spendings[i];
        if(spendings[i]>max) max = spendings[i];
    }
}
float SumSpending(float spendings[],int n){  //n тут це N-1, сумуємо елементи від N-1 до 0
    if(n<0){
        return 0;
    }
    return spendings[n]+SumSpending(spendings, n-1);    
}
void BudgetLeft(float sum_spend, float budget){
    if(sum_spend>budget){
        cout<<"Перевитрата понад бюджет: "<<abs(budget-sum_spend)<< " грн"<<endl;
    }else{
        cout<<"Залишок бюджету: "<<budget-sum_spend<<endl;
    }

}
float AvaregeMonth(float spendings[], int N, int &days_with_spend, float sum_spend){
    days_with_spend = 0;
    for(int i =0; i<N; i++){
        if (spendings[i]==0) continue;
        days_with_spend ++;       
    }
    if (days_with_spend == 0) return 0;  //на 0 ділити не можна, тому робимо перевірку
    return SumSpending(spendings, N-1)/days_with_spend;
}
void LastBudgDay(float spendings[], int N, float budget){
    float sum=0;
    int i = 0;
    while(i<N){
        sum+=spendings[i];
        if(sum>budget) break;
        i++;
    }
    if (sum<=budget){
        cout<<"Залишок бюджету: "<<budget-sum<<endl;
    }else{
        cout<<"Бюджет вичерпано на дні "<<i+1<<", накопичено "<<sum<<endl; // вихід цим шляхом завжди відбувається до інкремента, тому день буде i+1
    }
}

void OverLimit(int N, float spendings[], float limit){
    int count = 0;
    for (int i = 0;i<N; i++){
        if(spendings[i]>limit){
            cout<<"день "<<i+1<<": "<<spendings[i]<<" грн  "<<endl;
            count++;
        }
    }
    cout<<"Разом днів з перевищенням:  "<< count<<endl;
}

void CopySpendings(float spendings[],float copy_spendings[], int N){
    for(int i =0; i<N; i++){
        copy_spendings[i]=spendings[i];
    }
}


void ThreeMaxSpendings(float copy_spendings[], int N){
    for(int i = 0;i<N;i++){
        for(int j =0;j<N-1;j++){
            if (copy_spendings[j]<copy_spendings[j+1]){
                float t = copy_spendings[j];
                copy_spendings[j]=copy_spendings[j+1];
                copy_spendings[j+1]=t;
            }
        }

    }
    cout<<"Топ-3 витрат:"<<endl;
    if (N<=2){
        for(int i =0; i<N; i++){
            cout<<copy_spendings[i]<<" ";
        }
    }else{
        for(int i = 0;i<3;i++){
            cout<<copy_spendings[i]<<" ";
        }
    }
    cout<<endl;
}