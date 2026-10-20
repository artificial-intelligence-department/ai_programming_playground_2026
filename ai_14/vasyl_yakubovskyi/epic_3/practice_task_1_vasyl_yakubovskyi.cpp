/*
Task: Practice_task_Аналізатор місячного бюджету
Name: Vasyl Yakubovskyi
Group: ШІ-14(II)
*/



#include <iostream>
#include <iomanip> 
#include <cmath>


using namespace std;

void spendings_per_days(double spendings[], int N);
void spendings_Statistic(double spendings[], int N, long double budget, double &total, double max, double min);
void bubbleSort_Top3 (double spendings[], int N);
double Sum_spendings (double spendings[], int N);
void Day_limit(double spendings[], int N);
void min_max(double &min, double &max, double spendings[], int N);

int main(){

    setlocale(LC_ALL, "uk_UA"); 
    cout << fixed << setprecision(2); // щоб виводити два знаки після коми

    //Зчитуємо бюджет за місяць
    long double budget = 0;
    cout << "Введіть бюджет на місяць (грн): ";
    cin >> budget;

    if(budget <= 0){
        cout << "Помилка вводу!";
        return 1;
    }

    //Зчитуємо кількість днів 
    int N = 0;             
    cout << "Введіть кількість днів обліку: ";
    cin >> N;

    if(N <= 0 || N > 31){
        cout << "Помилка вводу!";
        return 1;
    }

    //Зчитуємо витрати за кожен N день
    double spendings[N] = {0};  
    
    cout << "Вкажіть витрати по днях (грн): ";

    for (int i = 0; i < N; i++){
        cin >> spendings[i];

        if(spendings[i] < 0){
            cout << "Помилка вводу!";
            return 1;
        }
        
    }
    int action = 0;
    double total = Sum_spendings(spendings, N);
    double min = spendings[0];
    double max = spendings[0];
    min_max(min, max, spendings, N);

    // виводимо користувачу меню і просимо обрати дію
    do
    {   
        MENU_START:

        cout << endl;
        cout << "======================МЕНЮ==========================" << endl;
        cout << "1 \t Показати витрати по днях" << endl;
        cout << "2 \t Показати статистику витрат" << endl;
        cout << "3 \t Показати дні з перевищенням денного ліміту" << endl;
        cout << "4 \t Показати три найдорожчі дні" << endl;
        cout << "0 \t ВИЙТИ" << endl;

        cout << "Оберіть ДІЮ: ";
        if (!(cin >> action)) {
            cout << "Помилка вводу!" << endl;
            cin.clear();               // Скидаємо прапорець помилки cin
            cin.ignore(10000, '\n');   // Очищаємо буфер
            goto MENU_START;           // Кидаємо користувача назад до меню
        }

        switch (action)
        {
        case 0: 
            break;
        case 1: 
            spendings_per_days(spendings, N);
            break;
        case 2: 
            spendings_Statistic(spendings, N, budget, total, max, min);
            break;
        case 3: 
            Day_limit(spendings, N);
            break;    

        case 4: 
            bubbleSort_Top3(spendings, N);
            break;

        default:
            cout << "Помилка вводу!" << endl;
            goto MENU_START; //Повертаємо користувача назад до меню 
        }

    } while (action != 0);
    



    return 0;
}

        // функція для обрахунку витрат по днях
void spendings_per_days(double spendings[], int N){  
    cout << "==================ВИТРАТИ ПО ДНЯХ===================" << endl;
        cout << "День \t Витрати, грн" << endl;
    for (int i = 0; i < N; i++){
        cout << (i + 1) << " \t\t" << spendings[i] << endl;

    }
}
        // рекурсивна функція для підрахування витрат
double Sum_spendings (double spendings[], int N){

    if(N <= 0){
        return 0;
    }

    return spendings[N - 1] + Sum_spendings(spendings, N - 1);
}

void min_max(double &min, double &max, double spendings[], int N){

    for (int i = 0; i < N; i++){
        if(spendings[i] > max){
            max = spendings[i];
        }
        if(spendings[i] < min){
            min = spendings[i];
        }
    }
   
}

        // Функція для виводу статистики витрат
void spendings_Statistic(double spendings[], int N, long double budget, double &total, double max, double min){
    cout << "==================СТАТИСТИКА ВИТРАТ=================" << endl;

 //Обчислюємо найменше та найбільше значення   

    cout << "Мінімальні витрати за день:  \t\t" <<  min << endl;
    cout << "Максимальні витрати за день:  \t\t" << max << endl;


 //обчислюємо Сумарні витрати, перевитрати чи залишок бюджету.
    cout << "Сумарні витрати:  \t\t\t" << total << endl;
    double remainder = 0;
    remainder = fabs(budget - total);
    if(total > budget){
        cout << "Перевитрата понад бюджет:  \t\t" << remainder << endl;
    }else{
        cout << "Залишок бюджету:  \t\t\t" << remainder << endl;
    }


 
 //Обчислюємо Дні з покупками та середні витрати за такі дні.
     double purcdays_sum = 0;
     int purcdays = 0;
     double ave_spendings_sum = 0;

     for (int i = 0; i < N; i++){
        if(spendings[i] == 0){
            continue;
        }
        purcdays_sum += spendings[i];
        purcdays++;

    }

    ave_spendings_sum = purcdays_sum / purcdays;
    cout << "Днів з покупками:  \t\t\t" << purcdays << endl;
    cout << "Середні витрати за такі дні:  \t\t" << ave_spendings_sum << endl;
    purcdays = 0;
    purcdays_sum = 0;
    ave_spendings_sum = 0;


 //рахуємо день коли сума перевищила бюджет
        double moneyDaysSum = 0;
        int moneyDays = 0;

        while(moneyDays < N){
        moneyDaysSum += spendings[moneyDays];
        moneyDays++;
        if(moneyDaysSum > budget) break;
        }

        if(moneyDaysSum > budget){
            cout << "Бюджет вичерпано на дні " << moneyDays << ", накопичено   " << moneyDaysSum << endl;
        }else{
            cout << "Бюджет не перевищено, залишок бюджету:  " << (budget - moneyDaysSum) << endl;
        }
        moneyDaysSum = 0;
        moneyDays = 0;

}

        // функція для сортування елементів, знаходження трьох найбільших
void bubbleSort_Top3 (double spendings[], int N){
    double spendingsCopy[N] = {0};

    cout << "=================ТРИ НАЙДОРОЖЧІ ДНІ=================" << endl;
            
            for(int i = 0; i < N; i++){
                spendingsCopy[i] = spendings[i];
            }
    
    //Саме сортування бульбашкою від найбільшого до найменшого
    for (int i = 0; i < N - 1; i++){
        bool issort = false; //створюємо прапорець для оптимізації циклу(якщо всі елементи вже відсортовані немає сенсу крутити цикл дальше..)

        for(int j = 0; j < N - i - 1; j++){

            if(spendingsCopy[j + 1] > spendingsCopy[j]){
                double temp = spendingsCopy[j + 1];
                spendingsCopy[j + 1] = spendingsCopy [j];
                spendingsCopy[j] = temp;    
                issort = true;
            }
        }
        if(!issort) break;
    }

    cout << "Топ-3 витрат: " ;
    int spendingsTop = 0;

            if(N<3){
                spendingsTop = N;
            }else{
                spendingsTop = 3;
            }
            for(int i = 0; i < spendingsTop; i++){
                cout << spendingsCopy[i];
                if(i != spendingsTop - 1){
                    cout << ", ";
                }
            }
            cout << endl;

}


        // функція для знаходження днів з перевищенням денного ліміту
void Day_limit(double spendings[], int N){
    cout << "=========ДНІ З ПЕРЕВИЩЕННЯМ ДЕННОГО ЛІМІТУ=========" << endl;
        double dayLimit = 1000;
        int daysAboveLimit = 0;

        cout << "За замовчуванням: \t "<< dayLimit << endl;
        cout << "Введіть значення денного ліміту: " ;
        cin >> dayLimit;

    if(dayLimit <= 0) dayLimit = 1000;
    for(int i = 0; i < N; i++){
        if(spendings[i] > dayLimit){
            cout << "\t День " << (i+1) << ": " <<spendings[i] << endl;
            daysAboveLimit++;
        }   
    }
    cout << "Разом днів з перевищенням: " << daysAboveLimit << endl;
    dayLimit = 1000;
    daysAboveLimit = 0;

}
