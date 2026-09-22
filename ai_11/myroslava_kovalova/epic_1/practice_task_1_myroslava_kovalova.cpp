/*Автономність портативної зарядної станції
Ковальова Мирослава
ШІ-11*/


#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    
    // оголошення змінних
    string model;   // назва моделі
    double C = 0.0; // паспортна ємність, Вт·год
    int years = 0;  // вік станції, р.
    int charge = 0; // рівень заряду, %
    double eff = 0.0;// ККд інвентора, %
    double P = 0.0;  // потужність приладу, Вт
    
    //оголошення констант
    const double percent_k = 2.0; // деградація за рік, %
    const int max_char = 31;  //максимальна кількість символів назви моделі

    //блок коду з почерговим вводом значень змінних користувачем та їх валідацією
    cout << "Модель станції: ";
    cin >> model;
    if (model.length()> max_char ){
        cout << "Помилка: назва максимум містить 31 символ";
        return 1;
    }

    cout << "Паспортна ємність (Вт·год): ";
    cin >> C;
    if (C <= 0){
        cout << "Помилка: ємність має бути більше 0";
        return 1;
    }
    
    cout << "Вік станції, років: ";
    cin >> years;
    if (years <0 || years>20){
        cout << "Помилка: вік має бути від 0 до 20";
        return 1;
    }

    cout << "Рівень заряду, %: ";
    cin >> charge;
    if (charge <0 || charge>100){
        cout << "Помилка: заряд має бути від 0 до 100";
        return 1;
    }

    cout << "ККД інвертора, %: ";
    cin >> eff;
    if (eff <=0 || eff>100){
        cout << "Помилка: ККД має бути більше 0, не більше 100";
        return 1;
    }

    cout << "Потужність приладу, Вт: ";
    cin >> P;
    if (P<=0){
        cout << "Помилка: потужність приладу має бути більше 0";
        return 1;
    }

    //обрахунок значень за формулами

    double C_eff = C*pow(1-percent_k/100, years); // фактична ємність з урахуванням віку, Вт·год
    double E_stored = C_eff*charge/100;           // запас енергії при поточному заряді, Вт·год
    double E_useful = E_stored*eff/100;           // корисна енергія, що дійде до приладу, Вт·год
    double E_loss = E_stored-E_useful;            // втрати на перетворенні напруги, Вт·год
    double T = E_useful/P;                        // час роботи, годин
    int h = (int)T;                               // повні години
    int m = (int)((T-h)*60);                      // хвилини, що залишуються

    //вивід значень дотримуючись умов про кількість знаків кожної змінної

    cout << left << setw(40) << "Модель: " << model<< endl; 
    cout << left << setw(40) <<"Паспортна ємність: " << fixed <<  setprecision(1) << C<< " Вт·год" << endl;
    cout << left << setw(40) <<"Вік станції: " << years<< " р." << endl;
    cout << left << setw(40) <<"Фактична ємність: " << fixed <<  setprecision(1) << C_eff << " Вт·год" << endl;
    cout << left << setw(40) <<"Рівень заряду: " << charge << " %" << endl;
    cout << left << setw(40) <<"ККД інвентора: " << fixed <<  setprecision(2) << eff << " %" << endl;
    cout << left << setw(40) <<"Запас енергії: " << fixed <<  setprecision(1) << E_stored << " Вт·год" << endl;
    cout << left << setw(40) <<"Корисна енергія: " << fixed <<  setprecision(1) << E_useful << " Вт·год" << endl;
    cout << left << setw(40) <<"Витрати на перетворення: " << fixed <<  setprecision(1) << E_loss << " Вт·год" << endl;
    cout << left << setw(40) <<"Час роботи: " << fixed <<  setprecision(2) << T << " год = " << h << " год "<< right<< setfill('0') << setw (2) << m << " хв " << endl;




    return 0;
}