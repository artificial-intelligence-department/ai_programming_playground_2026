/*
Задача: Автономність портативної зарядної станції
Автор:Гайдук Маргарита
Група: ШІ-12*/
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;
int main() {
    string model;
    cout<<"Модель станції: ";
    cin>>model;
    if (model.length() > 31) {
        cout<<"Помилка. Модель станції повинна бути не довшою за 31 символ.";
        return 1;
    }
    double C;
    cout<<"Паспортна ємність (Вт·год): ";
    cin>>C;
    if (C<=0) {
        cout<<"Помилка. Паспортна ємність повинна бути більше 0."<<endl;
        return 1;
    }
    int years;
    cout<<"Вік станції(років): ";
    cin>>years;
    if (years<0 || years>20) {
        cout<<"Помилка. Вік станції повинен бути від 0 до 20."<< endl;
        return 1;
    }
    int charge;
    cout<<"Рівень заряду(%): ";
    cin>>charge;
    if (charge<0 || charge>100) {
        cout<<"Помилка. Рівень заряду повинен бути від 0 до 100."<<endl;
        return 1;
    }
    double eff;
    cout<<"ККД інвертора(%): ";
    cin>>eff;
    if (eff<=0 || eff>100) {
        cout<<"Помилка. ККД інвертора повинен бути більше 0, не більше 100"<<endl;
        return 1;
    }
    double P;
    cout<<"Потужність приладу(Вт): ";
    cin>>P;
    if (P<=0) {
        cout<<"Помилка. Потужність приладу повинна бути більше 0."<<endl;
        return 1;
    }

    const double degradation = 2.0; // відсоток втрати ємності за рік
    double C_eff = C * pow(1 - degradation/100, years); // обчислюємо фактичну ємність(Вт·год) з урахуванням віку 
    double E_stored = C_eff* charge/100; // обчислюємо запас енергії(Вт·год) при поточному заряді
    double E_useful = E_stored * eff/100; // обчислюємо корисну енергію(Вт·год), що дійде до приладу
    double E_loss = E_stored - E_useful; // обчислюємо втрати(Вт·год) на перетворенні напруги
    double T = E_useful / P; // обчислюємо час роботи в годинах

    int h= (int)T; // виділяємо кількість повних годин роботи
    int m= int((T-h)*60); // обчислюємо кількість хвилин, що залишились 
    cout<<"Модель:                 " << model <<endl;
    cout<<"Паспортна ємність:      " << fixed<< setprecision(1)<< C << " Вт·год" << endl;
    cout<<"Вік станції:            " << years << " р." <<endl;
    cout<<"Фактична ємність:       " << fixed<< setprecision(1)<< C_eff << " Вт·год" << endl;
    cout<<"Рівень заряду:          " << charge << " %" <<endl;
    cout<<"ККД інвертора:          " << fixed<< setprecision(2)<< eff << " %" <<endl;
    cout<<"Запас енергії:          " << fixed<< setprecision(1)<< E_stored << " Вт·год" << endl;
    cout<<"Корисна енергія:        " << fixed<< setprecision(1) << E_useful << " Вт·год" << endl;
    cout<<"Втрати на перетворенні: " << fixed<< setprecision(1)<< E_loss << " Вт·год"<< endl;
    cout<<"Час роботи:             " << fixed<< setprecision(2) << T << " год" << " = " << h <<" год " <<setfill('0')<<setw(2)<< m << " хв" << endl;
    return 0;
}