/*Автономність портативної зарядної станції, Тимофієнко, ШІ-14*/
// Використані бібліотеки для: введення/виведення даних, математичних формул, форматування даних, для роботи з текстом./
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
// Вказівка для використання cout, cin, string.
using namespace std;
// Функція для початку програми.
int main(){
    string station_model;
    // Перемінна для зберігання чисел з дробовою частиною.
    double nominal_capacity;
    double years;
    double degradation;
    double current_charge;
    double efficiency;
    double power_consumption;

    cout << "Enter station model: ";
    cin>>station_model;
    // Функція для перевірки довжини символів.
    if (station_model.length()>31){
        cout<<"Error: Station model name must not exceed 31 symbols."<<endl;
        // Аварійне завершення програми.
        return 1;
    }
    
    cout << "Enter nominal battery capacity (Wh):";
    cin >> nominal_capacity;
    if (nominal_capacity<=0) {
        cout <<"Error: Capacity must be greater than 0." <<endl;
        return 1;
    }
    cout << "Enter years of operation: ";
    cin >> years;
    // Логічний оператор "АБО".//
    if (years <0 || years>20){
        cout <<"Error: Years must be between 0 and 20." <<endl;
        return 1;
    }
    cout << "Enter annual degradation rate (%):";
    cin >> degradation;
    if (degradation < 0 || degradation > 100) {
        cout << "Error: Degradation rate must be between 0 and 100." << endl;
        return 1;
    }
    cout << "Enter current charge level (%): ";
    cin >> current_charge;
    if (current_charge <0|| current_charge>100){
        cout <<"Error: Charge must be between 0 and 100."<<endl;
        return 1;
    }

    cout << "Enter system efficiency (%): ";
    cin >> efficiency;
    if (efficiency<=0 || efficiency>100){
        cout<<"Error: Efficiency must be between 0 and 100."<<endl;
        return 1;
    }
    cout << "Enter power consumption (W): ";
    cin >> power_consumption;
    if (power_consumption<=0) {
        cout<<"Error: Power consumption must be greater than 0."<<endl;
        return 1;
    }
    double base = 1.0 - (degradation/100.0);
    // Розрахунок залишкової ємності акумулятора з урахуванням зносу за роки експлуатації (Вт·год).
    double aged_capacity = nominal_capacity * pow(base, years);
    // Визначення фактичної кількості енергії в акумуляторі на основі поточного заряду (Вт·год).
    double E_stored = aged_capacity * (current_charge/100.0);
    // Обчислення корисної енергії з урахуванням ККД системи (Вт·год).
    double E_useful = E_stored * (efficiency/100.0);
    // Визначення втраченої енергії під час роботи системи (Вт·год).
    double E_loss = E_stored - E_useful;
    // Розрахунок загального часу автономної роботи зарядної станції (год).
    double T = E_useful/power_consumption;
    // Виділення цілої кількості годин автономної роботи (год).
    int h = static_cast<int>(T);
    // Переведення дробової частини часу у хвилини (хв).
    int m = static_cast<int>((T-h)*60);

    cout<<"\n--- Calculation Results ---\n";
    // Форматування.
    cout <<left<<setw(30)<<"Model:"<<station_model<<endl;

    cout<<fixed;
    cout<<setw(30)<<"Nominal Capacity (Wh):"<<setprecision(1)<<nominal_capacity<<endl;
    cout<<setw(30)<<"Age (years):"<<setprecision(0)<<years<<endl;
    cout<<setw(30)<<"Aged Capacity (Wh):"<<setprecision(1)<<aged_capacity<<endl;
    cout<<setw(30)<<"Current Charge (%):"<<setprecision(0)<<current_charge<<endl;
    cout<<setw(30)<<"Efficiency (%):"<<setprecision(2)<<efficiency<<endl;
    cout<<setw(30)<<"Stored Energy (Wh):"<<setprecision(1)<<E_stored<<endl;
    cout<<setw(30)<<"Useful Energy (Wh):"<<setprecision(1)<<E_useful<<endl;
    cout<<setw(30)<<"Energy Losses (Wh):"<<setprecision(1)<<E_loss<<endl;

    cout<<setw(30)<<"Operation Time:"
    <<setprecision(2)<<T<<"hours = "
    // Додає нуль попереду, якщо хвилин менше 10.
    <<h<<"hours"<< (m<10? "0":"")<<m<<"min"<<endl;
    return 0;
}