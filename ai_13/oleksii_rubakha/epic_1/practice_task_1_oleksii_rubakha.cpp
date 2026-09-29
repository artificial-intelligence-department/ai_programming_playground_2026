
/*
 Автономність портативної зарядної станції 
 Автор: Рубаха Олексій 
 Група: ШІ-13
*/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){

    // Втрата ємності акумулятора за один рік - 2 %
    const double degradation = 0.02;

    //Оголошення змінних
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
    cout<<"Паспортна ємність (Вт·год): ";
    cin>>C;
    //Перевірка на правельність ємності
    if (C <= 0){
        cout<<"Неправильна ємність";
        return 1;
    }

    //Введення віку станції
    cout<<"Вік станції (років): ";
    cin>>years;
    //Перевірка правельності введення віку
    if (years < 0 || years>20){
        cout<<"incorrect age model";
        return 1;
    }

    //Введення рівню зарядку
    cout<<"Рівень заряду (%): ";
    cin>>charge;
    //Перевірка правельності введення заряду станції
    if (charge < 0 || charge > 100){
        cout<<"incorrect charge level";
        return 1;
    }

    //Введення ККД інвентора
    cout<<"ККД інвертора (%): ";
    cin>>eff;
    //Перевірка правельності введення ККД інвентора
    if (eff <= 0 || eff > 100){
        cout<<"incorrect KKD";
        return 1;
    }

    //Введення потужності приладу
    cout<<"Потужність приладу (Вт): ";
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
    cout << fixed << left << setw(40) << "Модель:"                                             << model                 << endl;
    cout << fixed << left << setw(40) << "Паспортна ємність:"      << fixed << setprecision(1) << C        << " Вт·год" << endl;
    cout << fixed << left << setw(40) << "Вік станції:"                                        << years    << " р."     << endl;
    cout << fixed << left << setw(40) << "Фактична ємність:"       << fixed << setprecision(1) << C_eff    << " Вт·год" << endl;
    cout << fixed << left << setw(40) << "Рівень заряду:"                                      << charge   << " %"      << endl;
    cout << fixed << left << setw(40) << "ККД інвертора:"          << fixed << setprecision(2) << eff      << " %"      << endl;
    cout << fixed << left << setw(40) << "Запас енергії:"          << fixed << setprecision(1) << E_stored << " Вт·год" << endl;
    cout << fixed << left << setw(40) << "Корисна енергія:"        << fixed << setprecision(1) << E_useful << " Вт·год" << endl;
    cout << fixed << left << setw(40) << "Втрати на перетворенні:" << fixed << setprecision(1) << E_loss   << " Вт·год" << endl;
    cout << fixed << left << setw(40) << "Час роботи:"             << fixed << setprecision(2) << T        << " год = " << h << " год "
        << setfill('0') << setw(2) << m << setfill(' ') << " хв" << endl;

        return 0;
}