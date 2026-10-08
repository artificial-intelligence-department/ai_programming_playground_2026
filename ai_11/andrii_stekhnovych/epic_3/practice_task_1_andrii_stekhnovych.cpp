// Аналізатор місячного бюджету, ШІ-11, Стехнович Андрій
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
void PrintSpendings (float array[], int N) {
    cout << "День\tВитрати, грн"<<endl;
    for (int i = 1; i<(N+1); i++) {
        cout << i << fixed << setprecision(2) << "\t"<< array[i-1]<<endl;
    }
}
float SummarySpendings (float array[], int i) {
    if (i<0) {
        return 0;
    }
    float a=array[i];
    return a + SummarySpendings(array, i-1);
}
int SpendingsDays (float array[], int N) {
    int quantity=0;
    for (int i = 0; i<N; i++) {
        if (array[i]==0) {
            continue;
        }
        quantity++;
    }
    return quantity;
}
void MinMaxSpending (float array[], int N, float& minSpending, float& maxSpending) {
    minSpending = array[0];
    maxSpending = array[0];
    for (int i = 0; i<N; i++) {
        float sp=array[i];
        if (sp>maxSpending) {
            maxSpending=sp;
        }
        if (sp<minSpending) {
            minSpending=sp;
        }
    }
}
void OverLimit (float array[], int N, float lim=1000) {
    int count = 0;
    cout << "Ліміт: "<<fixed<<setprecision(2)<<lim<< " грн."<<endl;
    for (int i = 0; i<N; i++) {
        if (array[i]>lim) {
            cout << "\tдень "<<i+1<<":  "<<array[i]<<" грн"<<endl;
            count ++;
        }
    }
    cout << "Разом днів з перевищенням: "<< count <<endl;
}
void CopyArray(float array[], float copyarray[], int length) {
    for (int i = 0; i<length; i++) {
        copyarray[i]=array[i];
    }
}
void SortSpendings(float array[], int N) {
    for (int i = 0; i<N; i++) {
        for (int j = 0; j<N-1; j++) {
            
            if (array[j+1]>array[j]) {
                float a_1=array[j];
                array[j]=array[j+1];
                array[j+1]=a_1;
            }
        }
    }
}
void Top3Output(float array[], int N) {
    cout << "Топ-3 витрат: ";
    for (int i = 0; i<N; i++) {
        cout << fixed << setprecision(2) << array[i] << ", ";
        if (i==2) {
            break;
        }
    }
    cout << "грн " << endl;
}
int main() {
    float budget;
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;
    if (cin.fail() or budget<0) {
        cout << "Бюджет повинний бути числом більшим або рівним за 0." << endl;
        return 0;
    } 
    int N;
    cout << "Кількість днів обліку: ";
    cin >> N;
    if (cin.fail() or N<=0) {
                cout << "Кількість днів повинна бути числом більшим за 0." << endl;
                return 0;
    }
    if (N>31) {
        cout << "Облік ведеться не довше одного місяця." << endl;
        return 0;
    }
    float spending[31];
    cout << "Витрати по днях (грн): ";
    for (int i = 0; i<N; i++) {
        float v;
        cin >> v;
        if (cin.fail() or v<0) {
            cout << "Витрати - число більше/рівне 0.";
            return 0;
        }
        spending[i]=v;
    }
    int choice = 100;
    menu: 
        do {
        cout << "==== MENU ====\n 1 - Показати витрати по днях\n 2 - Статистика витрат\n 3 - Дні з перевищенням денного ліміту\n 4 - Три найдорожчі дні\n 0 - Вийти\nЗробіть свій вибір:\n";
        cin >> choice;
        if (cin.fail()) {
            cout << "\n[Помилка] Потрібно ввести число! Спробуйте ще раз.\n\n";
            cin.clear();              
            cin.ignore(10000, '\n');  
            goto menu;                
    }
        switch (choice) {
            case 1: {
                PrintSpendings(spending, N);
                break;
            }
                
            case 2: {
                int count_days = 0;
                double money_left = 0;
                double current_spendings = 0;
                float minSpend=0.0;
                float maxSpend=0.0;
                MinMaxSpending(spending, N, minSpend, maxSpend);
                cout << fixed << setprecision(2) << "Мінімальні витрати за день: \t" << minSpend << " грн." << endl;
                cout << fixed << setprecision(2) << "Максимальні витрати за день: \t" << maxSpend << " грн." << endl;

                float sum=SummarySpendings(spending, N-1);
                cout << fixed << setprecision(2) << "Сумарні витрати: \t\t" <<  sum << " грн." << endl;
                if (budget<sum) {
                    cout << fixed << setprecision(2) << "Перевитрата понад бюджет: \t" <<  fabs(budget-sum) << " грн." << endl;
                    while (count_days<N) {
                        current_spendings+=spending[count_days];
                        count_days++;
                        if (current_spendings>budget) {
                            break;
                        }

                    }
                } else {
                    money_left = budget-sum;
                }
                int sp_days = SpendingsDays(spending, N);
                cout<< "Днів з покупками: \t\t\t" <<  sp_days << endl;
                if (sp_days!=0) {
                    cout << fixed << setprecision(2) << "Середні витрати за такий день: \t" <<  sum/sp_days << " грн." << endl;
                } else {
                    cout << fixed << setprecision(2) << "Середні витрати за такий день: \t 0 грн." << endl;
                }
                
                    
                if (budget>=sum) {
                    cout << "Залишилось: " << money_left << " грн. " << endl;
                } else {
                    cout << "Бюджет вичерпано на дні " << count_days << ", накопичено " << current_spendings << " грн." <<endl;
                }
                break;
            }
                
            case 3: {
                float daily_limit = 0;
                cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
                cin >> daily_limit;
                if (cin.fail()) {
                    cout << "Ви ввели неправильний ліміт!"<<endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    goto menu;
                }
                if (daily_limit <=0) {
                    OverLimit(spending, N);
                } else {
                    OverLimit(spending, N, daily_limit);
                }  
                break;
            }
            case 4: {
                float sorted_spendings[31] = {0};
                CopyArray(spending, sorted_spendings, N);
                SortSpendings (sorted_spendings, N);
                Top3Output(sorted_spendings, N);
                break;
            }
            case 0:
            cout<<"Дякуємо за використання нашого аналізатора. До нових зустрічей! :)";
                break;
            default:
                cout << "\n[Помилка] Потрібно ввести число від 0 до 4! Спробуйте ще раз.\n\n";
                cin.clear();
                cin.ignore(10000, '\n');
                goto menu;
                break;
        }
    } while (choice!=0);

}