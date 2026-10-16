#include <iostream>

using namespace std ;

void showexpenses ( int d, double spending[31]) {
    for(int i = 0;i < d;i++){
        cout << "День "<< i + 1 <<" :"; 
        cout << spending [i] << endl;
    }
}

void minMax ( int d, double spending[31],double &minExp,double &maxExp) {
    minExp = spending[0];
    maxExp = spending[0];

for (int i = 1;i < d;i++){
    if(spending[i] < minExp){
        minExp = spending[i];  
    }
    if (spending[i] > maxExp){
        maxExp = spending[i];
    }
}
}

double sumExpenses (int d, double spending[31]) {
    if(d == 0){
        return 0;
    }
    return spending[d - 1] + sumExpenses(d - 1,spending);
}

void checkDailyLim (int d,double spending[31],double limit = 1000) {
    bool exce = false;
    int count = 0;
    for(int i = 0;i < d;i++){
        if(spending[i] > limit) {
            cout<< "День " << i+1 << " . "<< "Перевищено денний ліміт на:" <<spending[i] - limit <<endl;
            exce = true;
            count++;
        }
    }
    if(exce == false) {
        cout << "Денний ліміт не перевищено "<< endl;
    }
    cout<<"Разом днів із перевищенням: "<<count<<endl;
}

void top3(int d,double spending[31]) {
    double sort[31];
    for(int i = 0;i < d;i++){
        sort[i] = spending[i];
    }
    for(int i = 0;i < d - 1;i++){
        for(int j = 0;j < d - 1 - i;j++){
            if(sort[j] < sort[j + 1]) {
                double temp = sort[j];
                sort[j] = sort[j + 1];
                sort[j + 1] = temp;

            }
        }
    }
    for(int i = 0;i < 3 && i < d;i++){
        cout << sort[i] <<endl;
    }
    
}

int main(){

   
    double spending[31];
    double budget;
    int d;
    int choice;
    double minExp;
    double maxExp;

    cout << "Введіть бюджет та к-сть днів:" <<endl;

    cin >> budget;
      if(cin.fail() || budget <= 0) {
        cout << "Помилка! Бюджет має бути більшим за 0 та числом.";
        return 1;
    }

    cin >> d;
    if(cin.fail() || d > 31 || d < 1 || cin.peek() == '.'){
        cout << "Помилка! К-сть днів не повинна перевищувати 31 , не бути менше 1 та бути цілим числом.";
      return 1;
    }
    
    for(int i = 0;i < d;i++){
        cout << "Введіть витрати за день "<< i + 1 <<" :"<<endl; 
        cin >> spending [i] ;
        if(cin.fail() || spending [i] < 0 ){
            cout<<"Помилка введення витрат!"<<endl;
            return 1;
        }
    }

    do{
        cout <<"=== МЕНЮ ===\n" <<"1. Показати витрати \n" << "2. Статистика витрат \n" <<"3. Перевірка ліміту \n" << "4. Топ 3 витрати \n" << "0. Вихід \n";
        
        retry:

        cin >> choice;

        if (cin.fail()) {
        cout << "Помилка! Потрібно ввести число!" << endl;
        return 1;
        }
        
        switch (choice) {
            case 1: 
             showexpenses(d,spending);
             break;

            case 2: {
            minMax(d, spending, minExp, maxExp);
            double total = sumExpenses(d,spending);

            cout <<"Мінімальні витрати: " << minExp << endl;
            cout <<"Максимальні витрати:" << maxExp << endl;
            cout <<"Сума витрат: " << total << endl;

            if(total > budget) {
                cout << "Бюджет перевищено на: "<< total - budget << endl;
            }
            else{
                cout <<"Бюджет не перевищено!"<< endl;
            }

            int count = 0;
            for (int i = 0;i < d;i++) {
                if(spending[i] == 0){
                    continue;
                    
                }
                count++;
            }
            if(count > 0){
                    double average = total/count;
                    cout <<"Середні витрати: " << average <<endl;
                }
                else{
                    cout <<"Витрат не було"<<endl;
                }
            double currSum = 0;
            int day = 0;
            while(day < d) {
                currSum += spending[day];
                day += 1;
                if(currSum >= budget){
                    cout<<"Бюджет вичерпався на "<< day <<"день"<<endl;
                    break;
                }
            }
            if(currSum < budget){
                cout<<"Бюджет не вичерпано"<<endl;
            }
            break;
             }

            case 3: {
            double limit;
            cout << "Введіть денний ліміт:";
            cin>>limit;
            if (cin.fail()) {
            cout << "Помилка! Потрібно ввести число." << endl;
            return 1;
            }
            if(limit == 0) {
                checkDailyLim(d,spending);
            }
            else if(limit > 0){
                checkDailyLim(d,spending,limit);
            }
            else {
                cout<<"Помилка введення!"<< endl;
            }
            break;}

            case 4: {
                top3(d,spending);
                break;
            }
            case 0:
            break;

            default: 
            cout<<"Невідомий пункт! Спробуй ще раз."<<endl;
            goto retry;
        }
    }while (choice != 0);

  

    return 0;
}