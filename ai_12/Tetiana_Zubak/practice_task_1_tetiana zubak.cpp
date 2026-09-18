#include <iostream>
#include <locale>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;



int main(){

    setlocale (LC_ALL, "uk_UA");

//ввід
   string model; // модель станції
    cout << "Введіть модель станції(< 31 символа, 1 слово): ";
    getline(cin,model);
    if (model.length() > 31){
        cout << "Помилка: довжина рядка перевищує 31 символ."<< endl;
        return 1;
    }
    if(model.find(" ") != string::npos){
        cout << "Помилка: більше одного слова."<< endl;
        return 1;
    }

    float C; // паспортна ємність станції
    cout << fixed << setprecision(1);
    cout << "Введіть паспортну ємність станції (у Вт*год): ";
    cin >> C;
    if (C<= 0.0f){
        cout << "Помилка: паспортна ємність має бути додатним числом."<< endl;
        return 1;
    }

    signed short year;
    cout << "Введіть вік станції (у роках):";
    cin >> year;
    if ( year < 0){
        cout << "Помилка: вік станції має бути додатним числом."<< endl;
        return 1;
    }
    if (year > 20){
        cout << "Помилка: вік станції не може бути більшим за 20 років."<< endl;
        return 1;
    }

    signed int charge;
    cout << "Введіть рівень заряду (у відсотках): ";
    cin >> charge;
    if (charge < 0){
        cout <<"Помилка: рівень заряду має бути додатним числом."<< endl;
        return 1;
    }
    if (charge > 100){
    cout << "Помилка: рівень заряду не може бути більшим за 100%."<< endl;
    return 1;
    }

    float eff;
    cout << fixed << setprecision(2);
    cout << "Введіть ККД (у відсотках): ";
    cin >> eff;
    if (eff <= 0.00f){
        cout << "Помилка: ККД не може бути від'ємним."<< endl;
        return 1;
    }
    if (eff > 100.00f){
        cout << "Помилка: ККД не може бути більшим за 100%."<< endl;
        return 1;
    }

    float P;
    cout <<"Введіть потужність (у Вт): ";
    cin >> P;
    if(P <= 0.0f){
        cout << "Помилка: потужність має бути додатною."<< endl;
        return 1;
    }

// змінні для виводу
    double C_eff = C * pow(1.0 - 0.02,year); // фактична ємність
    double E_stored = C_eff * charge / 100.0; // запас енергії
    double E_useful = E_stored * eff / 100.0; // корисна енергія
    double E_loss = E_stored - E_useful; //
    double T = E_useful / P; //
    int h = T;
    signed short m = (T - h) * 60;

// вивід
    cout << "Модель: " << model << endl << "Паспортна ємність: " << C << " Вт*год" << endl << fixed << setprecision(1)
    << "Вік станції: " << year << " р." << endl<< "Фактична ємність: " << C_eff << " Вт*год" << endl << "ККД інвертора: "
    << eff << "%" << endl << "Рівень заряду: " << charge << "%" << endl
    << fixed << setprecision(1) << "Запас енергії: " << E_stored << " Вт*год" << endl << fixed << setprecision(1)
    << "Корисна енергія: " << E_useful << " Вт*год" << endl << fixed << setprecision(1) << "Втрати на перетворенні: "
    << E_loss << " Вт*год" << endl << "Час роботи: " << T << " год" << " = " << h << " год " << m << " хв " << endl;

return 0;
}
