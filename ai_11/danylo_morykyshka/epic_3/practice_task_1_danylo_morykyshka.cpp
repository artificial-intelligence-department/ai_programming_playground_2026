/*
 * Задача: Аналізатор місячного бюджету
 * Автор: Морикишка Данило
 * Група: ШІ-11
*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void ShowStatisticsOfOne(double daysFlow[], int length);
void ShowMenu();
void ShowStatisticsOfFlow();
void ShowStatisticsOfFlow(double daysFlow[], int length,double& maxValue, double& minValue);
double SumOfFlow(double arr[], int length, double& sum);
void ShowStatisticsOfTwo(double arr[], int length, double budget);
void ShowDayLimit(double arr[], int length, double limit);
void ThreeMostExpensive(double arr[], int length);

int main()
{
    const double MIN_BUDGET = 2000;
    const double MAX_BUDGET = 12000;
    const int MIN_COUNT_OF_DAYS = 1;
    const int MAX_COUNT_OF_DAYS = 31;

    tryagainBudget:
        cout << "Бюджет на місяць (грн): ";
        double budget;
        if(!(cin >> budget) || budget < MIN_BUDGET || budget > MAX_BUDGET){
            cout << "Неправильне значення бюджету!.Спробуйте ще раз." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto tryagainBudget;
        }
    tryagainDays:    
        cout << "Кількість днів обліку: ";
        int countOfDays;
        if(!(cin >> countOfDays) || countOfDays < MIN_COUNT_OF_DAYS || countOfDays > MAX_COUNT_OF_DAYS){
            cout << "Неправильне значення кількості днів!.Спробуйте ще раз." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            goto tryagainDays;
        }
    cout << "Витрати по днях: ";
    double daysFlow[MAX_COUNT_OF_DAYS];
    for(int i = 0; i < countOfDays;i++)
    {
        if(!(cin >> daysFlow[i]) || daysFlow[i] < 0 || daysFlow[i] > budget){
            cout << "Ви ввели неправильне значення для задання витрат, спробуйте ще раз!";
            cin.clear();
            cin.ignore(10000, '\n');
            i--;
        }
    }

    ShowMenu();

    int userChoice;
    bool isWorking = true;
    do
    {
    tryagainChoice:
       cout << "\nВведіть опцію: ";
       if(!(cin >> userChoice)){
        cout << "Помилка!Некоректне значення вводу.Спробуйте ще раз.";
        cin.clear();
        cin.ignore(10000, '\n');
        goto tryagainChoice;
       }
        switch(userChoice){
            case 1:
            ShowStatisticsOfOne(daysFlow, countOfDays);
            break;
             case 2:
            ShowStatisticsOfTwo(daysFlow, countOfDays, budget);
            break;
             case 3:
            cout << "Денний ліміт (грн, 0 = за замовчуванням): " << 0 << endl;
            tryagainLimit:
            cout << "Введіть ліміт: ";
             double limit;
             if(!(cin >> limit) || limit < 0){
                cout << "Помилка!Некоректне значення вводу.Спробуйте ще раз.";
                cin.clear();
                cin.ignore(10000, '\n');
                goto tryagainLimit;
             }
             ShowDayLimit(daysFlow, countOfDays, limit);

            break;
             case 4:
            ThreeMostExpensive(daysFlow, countOfDays);
            break;
             case 0:
            cout << "Вихід з програми.";
            isWorking = false;
            break;
            default:
            cout << "Такої опції немає.Виберіть від 0 до 4.\n";
            break;
        }
    } 
    while (isWorking);
 }

void ShowMenu()
{
    cout << endl;
     cout << setw(25) << "Меню\n";
    cout << left;
   
    cout << setw(10) << 1 << "Вказати витрати по днях.\n";
    cout << setw(10) << 2 << "Статистика витрат.\n";
    cout << setw(10) << 3 << "Дні з перевищенням денного ліміту.\n";
    cout << setw(10) << 4 << "Три найдорожчі дні.\n";
    cout << setw(10) << 0 << "Вийти.\n";
    
}

 void ShowStatisticsOfOne(double daysFlow[], int length)
 {
    cout << left;
    cout << "\nДень    Витрати, грн\n";
    cout << right << fixed << setprecision(2);
    for(int i = 0; i < length;i++){
         cout << setw(4) << i + 1 << setw(16) << daysFlow[i] << '\n';
    }
 }

 void MinMaxFinding(double daysFlow[], int length,double& maxValue, double& minValue)
 {
    maxValue = daysFlow[0];
    minValue = daysFlow[0];

    for(int i = 0; i < length; i++){
        if(daysFlow[i] < minValue){
            minValue = daysFlow[i];
        }
        if(daysFlow[i] > maxValue) {
            maxValue = daysFlow[i];
        }
    }
 }

 double SumOfFlow(double arr[], int length, double& sum)
 {
    
    if(length > 0 ){
        sum += arr[length - 1];
        return SumOfFlow(arr, length - 1, sum);
    }
    else{
        return sum;
    }
 }


 void ShowStatisticsOfTwo(double arr[], int length, double budget)
 {
    cout << "\nСтатистика витрат:" << endl;
    double max = 0;
    double min = 0;
    double sum = 0;
    sum = SumOfFlow(arr, length, sum);
    MinMaxFinding(arr, length, max, min);
    cout << right << fixed << setprecision(2);
    cout << "Мінімальні витрати за день:" << setw(10) << min<< endl;
    cout << "Максимальні витрати за день:" << setw(9) << max<< endl;
    cout << "Сумарні витрати: "<< setw(21) << sum << endl;
    cout << "Перевитрата понад бюджет: ";

    double surp = 0;
    if (budget >= sum)
    {
        surp = 0;
    }
    
    else
    {
        surp = budget - sum;
        if(surp < 0){
            cout << abs(surp) << endl;
        }
    }
   
    int count = 0;
    for(int i = 0; i < length;i++){
        if(arr[i] > 0){
            count++;
        }
    }

    cout << "Днів з покупками: " << count << endl;
    double sumOfNonNull = 0;
    for(int i = 0; i < length;i++){
        if(arr[i] > 0 ){
            sumOfNonNull += arr[i];
        }
        else{
            continue;
        }
    }
    double res = 0;
    res = sumOfNonNull / count;
    
    cout << "Середні витрати за такий день: "<< res << endl;

    double sum2 = 0;
    count = 0;
    while(count < length){
        sum2 += arr[count];
        count++;
           if(sum2 > budget){ 
            break;
        }
    }
    
    if(budget >= sum2){
        cout << "Бюджету вистачило на всі дні.Залишок: " << budget - sum2 << "грн.";
    }
        
    else{
        cout << "Бюджет вичерпано на " << count << "-й день, накопичено " << sum2 << " грн.\n";
    }
    
}

void ShowDayLimit(double arr[], int length, double limit)
{
    if(limit == 0){
        limit = 1000;
    }

    int count = 0;
    cout << "Ліміт: "<< fixed << setprecision(2) << limit << endl;
    for(int i = 0;i < length;i++){
        if(arr[i] > limit){
            cout << "день " << i + 1 << " : " << arr[i] << " грн." << endl;
            count++;
        }
    }
    cout << "Разом днів з перевищенням: " << count;

}

void ThreeMostExpensive(double arr[], int length)
{
    const int MAX_VALUE_OF_TEMP_ARRAY = 31;

    double tempArr[MAX_VALUE_OF_TEMP_ARRAY];
    for(int i = 0;i < length;i++){
        tempArr[i] = arr[i];
    }

    for(int i = 0;i < length;i++){
        for(int j = 0;j < length - 1;j++){
            if(tempArr[j] < tempArr[j + 1]){
                double savedValue = tempArr[j];
                tempArr[j] = tempArr[j + 1];
                tempArr[j + 1] = savedValue;
            }
        }
    }

    cout << "Топ-3 витрат: ";
    for(int i = 0;i < length;i++){
        if(i < 3 &&  i != 0){
           cout << ", " << tempArr[i] ;
        }
        else if(i == 0){
            cout << tempArr[i] ;
        }
    }
    cout << "грн" << endl;
}

