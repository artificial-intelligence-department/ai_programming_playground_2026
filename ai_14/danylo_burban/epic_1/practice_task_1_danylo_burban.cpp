 /*Епік 1. Практичне завдання: Автономність портативної зарядної станції. Бурбан Данило, ШІ-14*/

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main (){
    //data from inputs
    string model_name;
    float C;
    short years;
    short charge;
    float eff;
    float P;
    
    //inputs
    cout<<"Модель станції"<<endl;
    cin>>model_name;
    if (model_name.length()>31 || model_name.empty()){
        cout<<"Неправильно введена модель станції";
        return 0;
    }

    cout << "Паспортна ємність (Вт·год): ";
    if (!(cin >> C) || C <= 0) {
        cout << "Помилка: паспортна ємність має бути більше 0" << endl;
        return 0;
    }

    cout << "Вік станції (в роках): ";
    if (!(cin >> years) || years < 0 || years > 20) {
        cout << "Помилка: вік станції має бути від 0 до 20" << endl;
        return 0;
    }

    cout << "Рівень заряду (%): ";
    if (!(cin >> charge) || charge < 0 || charge > 100) {
        cout << "Помилка: рівень заряду має бути від 0 до 100" << endl;
        return 0;
    }

    cout << "ККД інвертора (%): ";
    if (!(cin >> eff) || eff <= 0 || eff > 100) {
        cout << "Помилка: ККД інвертора має бути від 0 до 100" << endl;
        return 0;
    }

    cout << "Потужність приладу (Вт): ";
    if (!(cin >> P) || P <= 0) {
        cout << "Помилка: потужність приладу має бути більше 0" << endl;
        return 0;
    }



    //calculated data
    float C_eff;
    C_eff = C*pow((1-2.0/100),years); //очислюємо фактичну ємінсть в Вт*год де 0.02 це деградація з роками

    float E_stored;
    E_stored = C_eff * charge/100; //обчислюємо запас енергії в Вт*год

    float E_useful;
    E_useful = E_stored * eff/100; //Обчислюємо корисну енергію в Вт*год

    float E_loss;
    E_loss = E_stored - E_useful; //Обчислюємо втрати енергії на перетворення

    float T;
    T = E_useful / P; // обчислюємо час роботи

    int h;
    h = trunc(T); //цілі години

    int m;
    m = trunc((T-h)*60); // хвилини

    //output
    cout << left;
    cout << "Модель станції:\t\t" << model_name << endl;
    cout << "Паспортна ємність:\t" << fixed << setprecision(1) << C << " Вт*год" << endl;
    cout << "Вік станції:\t\t" << years << " років" << endl;
    cout << "Фактична ємність:\t" << fixed << setprecision(1) << C_eff << " Вт*год" << endl;
    cout << "Рівень заряду:\t\t" << charge << " %" << endl;
    cout << "ККД інвертора:\t\t" << fixed << setprecision(2) << eff << " %" << endl;
    cout << "Запас енергії:\t\t" << fixed << setprecision(1) << E_stored << " Вт*год" << endl;
    cout << "Корисна енергія:\t" << fixed << setprecision(1) << E_useful << " Вт*год" << endl;
    cout << "Втрати на перетворенні:\t" << fixed << setprecision(1) << E_loss << " Вт*год" << endl;
    cout << "Час роботи:\t\t" << fixed << setprecision(2) << T << " год  = " 
     << h << " год " << setfill('0') << setw(2) << m << " хв" << endl;

    return 0;
}