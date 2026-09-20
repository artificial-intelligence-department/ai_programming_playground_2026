/*
Автономність портативної зарядної станції
Мішин ШІ-14
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

string name;//Назва станції
float C;// ємність
int years;//вік станції
int charge;// рівень заряду
float eff;//ефективність станції
float P;//Потужність станції
float C_eff;//залишкова ємність
float E_stored;//запас енергії при поточному заряді
float E_useful;//Корисна енергія, що дійде до приладу
float E_loss;//Втрати на перетворенні напруги
float T;//час роботи
int h;//години ціле число
int m;//хвилини, що залишились
bool check_ = false;// змінна для перевірки правильності вводу

void input(){//блок вводу значень
    cout << "Модель станції: ";
    cin >> name;
    cout << "Паспортна ємність (Вт·год): ";
    cin >> C;
    cout << "Вік станції (років): ";
    cin >> years;
    cout << "Рівень заряду (%): ";
    cin >> charge;
    cout << "ККД інвертора (%): ";
    cin >> eff;
    cout << "Потужність приладу (Вт): ";
    cin >> P;
}

void output(){// блок виводу значень
    cout << fixed<< endl << endl;
    cout << "Модель:                   " << name << endl;
    cout << "Паспортна ємність:        " << setprecision(1) << C << " Вт·год" << endl;
    cout << "Вік станції:              " << years << " р." << endl;
    cout << "Фактична ємність:         " << setprecision(1) << C_eff << " Вт·год" << endl;
    cout << "Рівень заряду:            " << charge << " %" << endl;
    cout << "ККД інвертора:            " << setprecision(2) << eff << " %" << endl;
    cout << "Запас енергії:            " << setprecision(1) << E_stored << " Вт·год" << endl;
    cout << "Корисна енергія:          " << setprecision(1) << E_useful << " Вт·год" << endl;
    cout << "Втрати на перетворенні:   " << setprecision(1) << E_loss << " Вт·год" << endl;
    cout << "Час роботи:               " << setprecision(2) << T << " год = " << h << " год ";
    cout << m << " хв" << endl;
}

void check(){//блок перевірки правильності вводу
    if (name.length() >= 31){
        cout<< endl <<"Помилка: назва станції мусить бути до 31 символу.";
        check_ = true;
    }

    if(C <= 0){
        cout<< endl <<"Помилка: паспортна ємність мусить бути більше 0.";
        check_ = true;
    }

    if( years < 0 || years > 20){
        cout<< endl <<"Помилка: вік станції мусить бути від 0 до 20.";
        check_ = true;
    }

    if (charge < 0 || charge > 100){
        cout<< endl <<"Помилка: заряд станції мусить бути від 0 до 100.";
        check_ = true;
    }

    if(eff <= 0 || eff >= 100){
        cout<< endl <<"Помилка: ефективність станції мусить бути більше 0, не більше 100.";
        check_ = true;
    }

    if(P <= 0){
        cout<< endl <<"Помилка: потужність станції мусить бути більше 0.";
        check_ = true;
    }
    
}

void calculation()//блок обчислень
{
    C_eff = C;
    float capacity_loss = 0.98;//скільки залишається ємності за 1 рік
    for (int i = 0; i < years; i++)//Вираховуєм залишкову ємність в залежності від віку станції станції
    {
        C_eff = C_eff * capacity_loss;
    }
    E_stored = C_eff * charge / 100;//Запас енергії при поточному заряді, Вт·год
    E_useful = E_stored * eff / 100;//Корисна енергія, що дійде до приладу, Вт·год
    E_loss = E_stored - E_useful;//Втрати на перетворенні напруги, Вт·год
    T = E_useful / P;//Час роботи, годин
    h = (int)T;//Повні години
    m = (int)((T - h) * 60);//Хвилини, що залишились
}

int main(){
    input();
    check();
    if(check_ == true){
        return 1;
    }
    calculation();
    output();
    return 0;
}
