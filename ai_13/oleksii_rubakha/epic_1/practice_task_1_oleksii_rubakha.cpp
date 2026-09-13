#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){

    //Оголошення змінних
    const double degradation = 0.02;
    
    string model;
    double C, eff, P, C_eff, E_stored, E_useful, E_loss, T;
    int    h, m, years, charge;

    //Введення моделі станції
    cout<<"Модель станції: ";
    cin>>model;
    //Перевірка на довжину рядку
    if (model.length() > 31){
        cout<<"Назва модель задовга";
        return 1;
    }

    //Введення паспортної ємності станції
    cout<<"Паспортна ємність: ";
    cin>>C;
    //Перевірка на правельність ємності
    if (C <= 0){
        cout<<"Неправильна ємність";
        return 1;
    }

    //Введення віку станції
    cout<<"вік станції: ";
    cin>>years;
    //Перевірка правельності введення віку
    if (years < 0 || years>20){
        cout<<"incorrect age model";
        return 1;
    }

    //Введення рівню зарядку
    cout<<"Рівень заряду: ";
    cin>>charge;
    //Перевірка правельності введення заряду станції
    if (charge < 0 || charge > 100){
        cout<<"incorrect charge level";
        return 1;
    }

    //Введення ККД інвентора
    cout<<"ККД інвентора: ";
    cin>>eff;
    //Перевірка правельності введення ККД інвентора
    if (eff <= 0 || eff > 100){
        cout<<"incorrect KKD";
        return 1;
    }

    //Введення потужності приладу
    cout<<"Потужність приладу: ";
    cin>>P;
    //Перевірка потужності
    if (P <= 0){
        cout<<"incorrect power";
        return 1;
    }

    //обрахунок фактичної ємності з урахуванням віку
    C_eff = C * pow((1 - degradation), years);
    //обрахунок запасу енергії при поточному заряді
    E_stored = C_eff * charge / 100;
    //обрахунок корисної енергії, що дійде до приладу
    E_useful = E_stored * eff / 100;
    //обрахунок втрат на перетворенні напруги
    E_loss = E_stored - E_useful;
    //обрахунок часу роботи
    T = E_useful / P;
    //обрахунок повних годин
    h = (int)T;
    //обрахунок хвилин, що залишились
    m = (int)((T-h)*60);

    //Виведння розрахунків
    cout << "\n";
    cout << left << setw(34) << "Модель:"                              << model                 << endl;
    cout << left << setw(40) << "Паспортна ємність:"<< setprecision(1) << C        << " Вт/год" << endl;
    cout << left << setw(39) << "Вік станції:"                         << years    << " p."     << endl;
    cout << left << setw(40) << "Фактична ємність:" << setprecision(1) << C_eff    << " Вт/год" << endl;
    cout << left << setw(40) << "Рівень заряду:"                       << charge   << " %"      << endl;
    cout << left << setw(40) << "ККД інвертора:"    << setprecision(2) << eff      << " %"      << endl;
    cout << left << setw(40) << "Запас енергії:"    << setprecision(1) << E_stored << " %"      << endl;
    cout << left << setw(40) << "корисна енергія:"  << setprecision(1) << E_useful << " %"      << endl;
    cout << left << setw(34) << "втрати:"           << setprecision(1) << E_loss   << " %"      << endl;

    return 0;
}