/*Задача: Аналізатор місячного бюджету
Виконав: Барановський Максим ШІ - 11 */


#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void showSpendings(double spendings[], int amountOfDays){ //функція для показу щоденних витрат

    cout << left << setw(14) << "День" << "Витрати, грн" << endl;

    cout << fixed << setprecision(2);

    for(int i = 0; i < amountOfDays; i++ ){
        cout << right << setw(4) << i+1 << setw(17) << spendings[i] << endl;
    }
} 

//Пошук максимального та мінімального значень. Передаємо посилання як параметри для збереження значень в змінні, на які посилаємось

void findMinMaxSpendings(double spendings[], int amountOfDays, double& minValue, double& maxValue){

    minValue = spendings[0];
    maxValue = spendings[0];

    for(int i = 1; i < amountOfDays; i++){
        if(spendings[i] < minValue){
            minValue = spendings[i];
        }
        if(spendings[i] > maxValue){
            maxValue = spendings[i];
        }
    }
}

//Функція, що обчислює суму рекурсивним методом

double sumSpendings(double spendings[], int amountOfDays){

    if (amountOfDays == 1){
        return spendings[0];
    }
    return spendings[amountOfDays - 1] + sumSpendings(spendings, amountOfDays - 1);
}

//Вивід 2 пункту

void showStats(double spendings[], int amountOfDays, double budget){

    double currentMin = 0;
    double currentMax = 0;

    findMinMaxSpendings(spendings, amountOfDays, currentMin, currentMax);
    double totalSpendings = sumSpendings(spendings, amountOfDays);

    cout << fixed << setprecision(2);

    cout << left << setw(58) << "Мінімальні витрати за день: " << right << setw(10) << currentMin << " грн" << endl;
    cout << left << setw(59) <<  "Максимальні витрати за день: " << right << setw(10) << currentMax << " грн" << endl;
    cout << left << setw(49) << "Сумарні витрати: " << right << setw(10) << totalSpendings << " грн" << endl;

    if(totalSpendings > budget){
        cout << left << setw(57) << "Перевитрата понад бюджет: " << right << setw(10) << abs(budget - totalSpendings) << " грн" << endl;
    }

    int daysWithSpendings = 0;

    for(int i = 0; i < amountOfDays; i++){
        if(spendings[i] == 0) continue;
        daysWithSpendings++;
    }

    cout << left << setw(49) << "Днів з покупками: " << right << setw(10) << daysWithSpendings << endl;

    double averageSpendings = 0;

    if(daysWithSpendings > 0){
        averageSpendings = totalSpendings / daysWithSpendings;
    }

    cout << left << setw(58) << "Середні витрати за такі дні: " << right << setw(10) << averageSpendings << " грн" << endl;

    int currentDay = 0;
    double sum = 0.0;

    while (currentDay < amountOfDays){
        sum += spendings[currentDay];
        currentDay++;
    
        if (sum > budget) {
            cout << "Бюджет вичерпано на дні " << currentDay << ", накопичено " << sum << " грн." << endl;
            break;
    }
}

    if (sum <= budget) {
    cout << "Бюджету вистачило на всі дні. Залишок: " << (budget - sum) << " грн." << endl;
}
}

void showDaysWithExceededBudget(double spendings[], int amountOfDays, double dayLimit = 1000.0){

    cout << fixed << setprecision(2);

    cout << "Денний ліміт (грн, 0 = за замовчуванням): ";
    double tempLimitValue; //Створюємо змінну для тимчасового збереження значення

    while(!(cin >> tempLimitValue) || tempLimitValue < 0){
        cout << "Помилка: Ліміт повинен дорівнювати або бути більшим за 0! Введіть значення ще раз: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    if(tempLimitValue != 0){ //Якщо значення змінної не нуль, перепризначаємо значення dayLimit замість заданого в параметрах функції
        dayLimit = tempLimitValue; 
    }

    cout << "Ліміт: " << dayLimit << " грн" << endl;

    int countDaysWithExceededBudget = 0;

    for(int i = 0; i < amountOfDays; i++){
        if(spendings[i] > dayLimit){
            cout << " день" << i+1 << ": " << spendings[i] << " грн" << endl;
            countDaysWithExceededBudget ++;
        }
    }

    cout << "Разом днів з перевищеннямм: " << countDaysWithExceededBudget << endl;

}

//Функція копіювання масиву

void copyArray(double spendings[], int amountOfDays, double copy[]){

    for(int i = 0; i < amountOfDays; i++){
        copy[i] = spendings[i];
    }
}

//Bubble sort

void sortSpendings(double array[], int amountOfDays){

    for(int i = 0; i < amountOfDays - 1; i++){
        for(int j = 0; j < amountOfDays - 1 - i; j++){
            if(array[j+1] > array[j]){
                double temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

//Функція для виведення 4 пункту

void top3Spendings(double spendings[], int amountOfDays){

    double sortedArray[31] = {0};
    copyArray(spendings, amountOfDays, sortedArray);
    sortSpendings(sortedArray, amountOfDays);

    cout << fixed << setprecision(2);

    int count;
    if(amountOfDays < 3){
        count = amountOfDays;
    }
    else { 
        count = 3;
    }

    cout << "Топ-" << count << " витрат: ";
    for(int i = 0; i < count; i++){
        cout << sortedArray[i];
        if(i < count - 1){
            cout << ", ";
        }
    }
    cout << " грн" << endl;
}

int main(){

    const int DAYS = 31; //створюємо константу для максимального можливого значення днів

    cout << "Введіть бюджет на місяць, грн: " << endl;
    double budget;
    while(!(cin >> budget) || budget < 0){
        cout << "Помилка: Бюджет повинен бути невід'ємним числом! Введіть значення ще раз: " << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
    
    cout << "Введіть кількість днів обліку: " << endl;
    int amountOfDays;
    while(!(cin >> amountOfDays) || amountOfDays <= 0 || amountOfDays > DAYS){
        cout << "Помилка: Кількість днів повинна бути від 1 до " << DAYS << "! Введіть значення ще раз: " << endl;
        cin.clear();
        cin.ignore(10000, '\n');    
    }

    cout << "Введіть витрати по днях, грн: " << endl;
    double spendings[DAYS] = {0};
    for(int i = 0; i < amountOfDays; i++){
        while(!(cin >> spendings[i]) || spendings[i] < 0){
            cout << "Помилка: Витрати за день повинні дорівнювати або бути більшими за нуль! Введіть значення ще раз: " << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int userInput = -1;

    do{

        cout << left;

        menu:
            cout << setw(24) << "Пункт" << "Операція" << endl;
            cout << setw(19) << 1 << "Показати витрати по днях" << endl;
            cout << setw(19) << 2 << "Статистика витрат" << endl;
            cout << setw(19) << 3 << "Дні з перевищенням денного ліміту" << endl;
            cout << setw(19) << 4 << "Три найдорожчі дні" << endl;
            cout << setw(19) << 0 << "Вийти" << endl;
    
        if(!(cin >> userInput)){
            cin.clear();
            cin.ignore(10000, '\n');
            userInput = -1;
        }

        switch(userInput){
            case 0:
                cout << "Завершення програми..." << endl;
                break;
            case 1:
                showSpendings(spendings, amountOfDays);
                break;
            case 2:
                showStats(spendings, amountOfDays, budget);
                break;
            case 3:
                showDaysWithExceededBudget(spendings, amountOfDays, budget);
                break;
            case 4:{
                top3Spendings(spendings, amountOfDays);
                break;
            }
            default:
                cout << "Введіть коректне значення операції: " << endl; //якщо отримує неправильне значення виводимо помилку та повертаємо до меню
                goto menu;
                break;
        }
    }
    while (userInput != 0); //якщо userInput == 0, програма завершується

    return 0;
}