#include <iostream>
#include <cmath>
using namespace std;

double calculateTotal(const double spending[], int n, int index=0){
    if (index>=n) return 0.0;
    return spending[index] + calculateTotal(spending, n, index+1);
}
void findMinMax(const double spending[], int n, double &minVal, double &maxVal){
    minVal = spending[0];
    maxVal = spending[0];
    for (int i=1; i<n; i++){
        if (spending[i]<minVal) minVal = spending[i];
        if (spending[i]>maxVal) maxVal = spending[i];
    }
}
void showDaily(const double spending[], int n){
    cout<<endl<<"---Витрати по днях---"<<endl;
    cout<<"День\t | Витрати, грн: "<<endl;
    for (int i=0; i<n; i++){
        cout<<i+1<<"\t | "<<spending[i]<<endl;
    }
}
void showStats(const double spending[], int n, double budget){
    cout<<endl<<"---Статистика витрат---"<<endl;
    double minV, maxV;
    findMinMax(spending, n, minV, maxV);

    double total = calculateTotal(spending, n);
    cout<<"Мінімум: "<<minV<<"грн | Максимум: "<<maxV<<" грн"<<endl;
    cout<<"Сумарні витрати: "<<total<<" грн"<<endl;
        if (total>budget){
            cout<< "Перевитрата: "<< abs(budget-total)<<" грн"<<endl;
        }else{
            cout<<"Залишок: "<<budget-total<<" грн"<<endl;
        }
        int days=0;
        double sum =0;
        for (int i=0; i<n; i++){
        if (spending[i] > 0) {
            sum += spending[i];
            days++;
        }
    }
        cout << "Днів з покупками: " << days << endl;
        cout<<"Середні витрати за день з покупками: "<<(days ? sum / days : 0)<<" грн"<<endl;
        
        double acc = 0;
         int exDay = -1;
        for (int j = 0; j < n; j++) {
        acc += spending[j];
        if (acc > budget) {
            exDay = j + 1;
            break;
            }
        }
    if (exDay != -1) {
        cout << "Бюджет вичерпано на дні " << exDay << ", накопичено " << acc << " грн." << endl;
    } else {
        cout << "Бюджету вистачило на всі дні. Залишок: " << budget - total << " грн." << endl;
    }
        }
        void showLimit(const double spending[], int n, double limit = 1000.0){
            cout<<endl<< "Введіть денний ліміт (0 за замовчуванням ): ";
            double input;
            cin>>input;
            while (cin.fail() || input < 0){
             cin.clear();
            cin.ignore(10000, '\n');
            cout<<"Помилка! Ліміт не може бути від'ємним: ";
            cin>>input;
            }
            if (input>0) limit = input;

            int count =0;
            cout<<"Ліміт: "<<limit<<" грн"<< endl;
            for (int i = 0; i<n; i++){
                if (spending[i]>limit){
                    cout<<"День "<<i+1<<": "<<spending[i]<<" грн"<< endl;
                    count++;
                }
            }
            cout<<"Всього днів з перевищенням: "<<count<<endl;
        }
        void showTop3(const double spending[], int n){
    double copy[31];
    for (int i = 0; i < n; i++) {
        copy[i] = spending[i];
    }

    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (copy[j] < copy[j+1]){
                double t = copy[j]; copy[j] = copy[j+1]; copy[j+1] = t;
            }
        }
    }

    cout << endl << "Топ-3 витрат: ";
    int limit = (n < 3) ? n : 3;
    for (int i = 0; i < limit; i++){
        cout << copy[i] << (i < limit - 1 ? ", " : " грн");
    }
    cout << endl;
}

int main(){
double budget;
int n;

    do {
        cout << "Бюджет: ";
        if (!(cin >> budget) || budget <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка! Бюджет має бути числом більше 0: " << endl;
        } else {
            break;
        }
    } while (true);
    do {
        cout << "Кількість днів (до 31): ";
        if (!(cin >> n) || n < 1 || n > 31) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Помилка! Кількість днів від 1 до 31: " << endl;
        } else {
            break;
        }
    } while (true);
    double spending[31];
    cout << "Витрати по днях:" << endl;
    for (int i=0; i<n; i++){
        do {
            if (!(cin >> spending[i]) || spending[i] < 0) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Помилка! День " << i+1 << ": ";
            } else {
                break;
            }
        } while (true);
    }

int choice;
do {
    menu:
    cout<<endl<< "1. Витрати"<<endl;
    cout<<"2. Статистика"<<endl;
    cout<<"3. Ліміт"<<endl;
    cout<<"4. Топ-3"<<endl;
    cout<<"0. Вихід"<<endl;
    cout<<"Вибір: ";

    if (!(cin>>choice)){
        cin.clear();
        cin.ignore(10000, '\n');
        goto menu;
    }
    switch (choice){
        case 1: showDaily(spending, n); break;
        case 2: showStats(spending, n, budget); break;
        case 3: showLimit(spending, n); break;
        case 4: showTop3(spending, n); break;
        case 0: cout<<"Вихід!"<<endl; break;
        default: goto menu;
    }
 } while (choice !=0);
    return 0;
}
