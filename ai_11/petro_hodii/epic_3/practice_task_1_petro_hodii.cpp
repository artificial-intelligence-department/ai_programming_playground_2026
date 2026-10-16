#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

void getMinMax(const double p[], int len, double& min, double& max){
    for(int i = 0; i < len; i++){
        if(p[i] > max){max = p[i];}
        if(p[i] < min){min = p[i];}
    }
}

double sumSpending(const double p[], int len){
    if(len <= 0){return 0;}
    return p[len-1] + sumSpending(p, len-1);
}

int checkBuyDay(const double p[], int len){
    int result = 0;
    for(int i = 0; i < len; i++){
        if(p[i] == 0){continue;}
        result++;
    }
    return result;
}

void checkSpend(const double p[], int len, double budget, int& day, double& limBudget){
    int sum = 0;
    int i = 0;

    while(true){
        sum += p[i];
        if(sum > budget){day = i+1; limBudget = sum; break;}
        if(i == len-1){day = i+1; limBudget = -sum; break;}
        i++;
    }
}





void viewSpending(const double p[], int len){
    cout << "День     Витрати, грн" << endl;

    for(int i = 0; i < len; i++){
        cout << i+1 << "        " << fixed << setprecision(2) << p[i] << endl;
    }
}

void statistics(const double p[], int len, double budget){
    double min = 0;
    double max = 0;
    getMinMax(p, len, min, max);
    cout << "Мінімальні витрати за день: " << fixed << setprecision(2) << min << " грн" << endl;
    cout << "Максимальні витрати за день: " << fixed << setprecision(2) << max << " грн" << endl;

    double sum = sumSpending(p, len);
    cout << "Сумарні витрати: " << fixed << setprecision(2) << sum << " грн" << endl;

    if(sum > budget){
        cout << "Перевитрата понад бюджет: " << fixed << setprecision(2) << abs(budget - sum) << " грн" << endl;
    }
    else{
        cout << "Перевитрати понад бюджет немає" << endl;
    }

    int buyDay = checkBuyDay(p, len);
    cout << "Днів з покупками: " << buyDay << endl;
    cout << "Середні витрати за такий день: " << fixed << setprecision(2) << sum/double(buyDay) << " грн" << endl;
    
    int day = 0;
    double limBudget = 0.;
    checkSpend(p, len, budget, day, limBudget);
    if(limBudget > 0){
        cout << "Бюджет вичерпано на дні " << day << ", накопичено " << fixed << setprecision(2) << limBudget << " грн" << endl;
    }
    else{
        cout << "Бюджету вистачило. Залишок: " << fixed << setprecision(2) << budget + limBudget << " грн" << endl;
    }
}

void dayLimit(const double p[], int len){
    int numOfDays = 0;
    double limit;

    input:
    cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
    cin >> limit;

    if(cin.fail()){
        cout << "Помилка! Введіть коректне число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        goto input;
    }

    if(limit < 0){
        cout << "Помилка! Введіть додатне число." << endl;
        goto input;
    }

    limit = (limit == 0) ? 1000. : limit;

    cout << "Ліміт: " << limit << " грн" << endl;
    for(int i = 0; i < len; i++){
        if(p[i] > limit){
            cout << "день " << i+1 << ": " << fixed << setprecision(2) << p[i] << " грн" << endl;
            numOfDays++;
        }
    }
    cout << "Разом днів з перевищенням: " << numOfDays << endl;
}

void top3Days(const double p[], int len){
    double result[31];
    for(int i = 0; i < len; i++){
        result[i]=p[i];
    }

    int index = 0;
    for(int i = 0; i < len; i++){
        int max = 0;
        for(int j = len-1; j >= i; j--){
            if(result[j] > max){max = result[j]; index = j;}
        }
        int temp = result[i];
        result[i] = result[index];
        result[index] = temp;
    }

    cout << "Топ-3 витрат: " << fixed << setprecision(2) << result[0];
    if(len == 2){
        cout  << ", " << fixed << setprecision(2) << result[1];
    }
    else if(len >= 3){
        cout << ", " << fixed << setprecision(2) << result[1] << ", " << result[2];
    }
    cout  << " грн" << endl;
}


int main(){
    bool show = true;
    double budget = 0;
    double N = 0;
    double spending[31] = {};
    int action;

    budget_input:
    cout << "Бюджет на місяць (грн): ";
    cin >> budget;

    if(cin.fail()){
        cout << "Помилка! Введіть коректне число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        goto budget_input;
    }

    if(budget < 0){
        cout << "Помилка! Введіть додатне число." << endl;
        goto budget_input;
    }

    N_input:
    cout << "Кількість днів обліку: ";
    cin >> N;
    if((N - int(N)) != 0){
        cout << "Помилка! Введіть ціле число." << endl;
        goto N_input;
    }else{
        N = static_cast<int>(N);
    }
    if(cin.fail()){
        cout << "Помилка! Введіть коректне число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto N_input;
    }
    if(N <= 0){
        cout << "Помилка! Введіть додатне число." << endl;
        goto N_input;
    }
    if(N > 31){
        cout << "Помилка! Введіть число від 1 до 31." << endl;
        goto N_input;
    }

    spending_input:
    cout << "Витрати по днях (грн): ";
    for(int i = 0; i < N; i++){
        cin >> spending[i];

        if(cin.fail()){
        cout << "Помилка! Введіть коректне число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        goto spending_input;
        }

        if(spending[i] < 0){
        cout << "Помилка! Введіть додатне число." << endl;
        goto spending_input;
    }
    }

    do{
        menu:
        cout << endl << "----Menu----" << endl;
        cout << "1 - Показати витрати по днях" << endl;
        cout << "2 - Статистика витрат" << endl;
        cout << "3 - Дні з перевищенням денного ліміту" << endl;
        cout << "4 - Три найдорожчі дні" << endl;
        cout << "0 - Вийти" << endl;

        action_input:
        cout << "Оберіть дію: ";
        cin >> action;

        if(cin.fail()){
        cout << "Помилка! Введіть коректне число." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        goto action_input;
    }

        switch(action){
            case 1: viewSpending(spending, N); break;
            case 2: statistics(spending, N, budget); break;
            case 3: dayLimit(spending, N); break;
            case 4: top3Days(spending, N); break;
            case 0: show = false; break;
            default: goto menu;
        }
    } while(show);

    return 0;
}
