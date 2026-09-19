/*
Задача: Автономність портативної зарядної станції
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    string model;   //Назва моделі станції
    float C;        //Паспортна ємність
    int years;      //Вік станції
    int charge;     //Рівень заряду
    float eff;      //ККД інвентора
    float P;        //Потужність приладу
    

    //Блок введення даних та валідації

    cout<<"Station model: ";
    cin>>model;
    if(model.length() > 31)
    {
        cout<<"Error: station model name is too long.";
        return 1;
    }

    cout<<"Nominal capacity (W*h): ";
    cin>>C;
    if(C <= 0)
    {
        cout<<"Error: nominal capacity must be greater than 0.";
        return 1;
    }

    cout<<"Station age (years): ";
    cin>>years;
    if(years < 0 || years > 20)
    {
        cout<<"Error: age must be in the range from 0 to 20";
        return 1;
    }

    cout<<"Charge level (%): ";
    cin>>charge;
    if(charge < 0 || charge > 100)
    {
        cout << "Error: charge level must be in the range from 0 to 100.";
        return 1;
    }

    cout<<"Inverter efficiency (%): ";
    cin>>eff;
    if(eff <= 0 || eff > 100)
    {
        cout << "Error: inverter efficiency must be greater than 0, but not greater than 100.";
        return 1;
    }

    cout<<"Device power (W): ";
    cin>>P;
    if(P <= 0)
    {
        cout << "Error: device power must be greater than 0.";
        return 1;
    }
    
    //Блок обчислення

    float C_eff = C * pow(1.0 - 2.0/100.0, years); //Фактична ємність з урахуванням віку, Вт*год
    float E_stored = C_eff * charge/100.0;         //Запас енергії при поточному заряді, Вт*год
    float E_useful = E_stored * eff/100.0;         //Корисна енергія, що дійде до приладу, Вт*год
    float E_loss = E_stored - E_useful;            //Втрати на перетворенні напруги, Вт*год
    float T = E_useful / P;                        //Час роботи, годин
    int h = (int)T;                                //Повні години роботи
    int m = (int)((T - h) * 60);                   //Хвилини роботи

    //Блок виведення даних

    cout << endl;
    cout << fixed << setprecision(1); //Використовуємо fixed та setprecision() з iomanip для задання кількості знаків після коми у виводі
    cout << left << setw(30) << "Model: " << right << setw(15) << model << endl; //Використовуємо left, right, setw() з iomanip для вирівнювання виводу у два стовпці
    cout << left << setw(30) << "Nominal capacity: " << right << setw(15) << C << " W*h" << endl;
    cout << left << setw(30) << "Station age:" << right << setw(15) << years << " yr" << endl;
    cout << left << setw(30) << "Actual capacity:" << right << setw(15) << C_eff << " W*h" << endl;
    cout << left << setw(30) << "Charge level:" << right << setw(15)<< charge << " %" << endl; 
    cout << setprecision(2);
    cout << left << setw(30) << "Inverter efficiency:" << right << setw(15)<< eff << " %" << endl; 
    cout << setprecision(1);
    cout << left << setw(30) << "Energy stored:" << right << setw(15) << E_stored << " W*h" << endl;
    cout << left << setw(30) << "Useful energy:" << right << setw(15) << E_useful << " W*h" << endl; 
    cout << left << setw(30) << "Energy loss:" << right << setw(15) << E_loss << " W*h" << endl;
    cout << setprecision(2); 
    cout << left << setw(30) << "Working time:" << 
    right << setw(15) << T << " hr  =  " << h << " hr " << setfill('0') << setw(2) << m << " min" << endl; //Використовуємо setfill('0') з iomanip для виводу хвилин двома цифрами  
    
    return 0;
}