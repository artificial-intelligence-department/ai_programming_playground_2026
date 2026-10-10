/*
    Автономність портативної зарядної станції
    Прізвище: Онишко
    Група: ШІ-14
*/


#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {




    string model_name;
    double capacity;
    int years;
    double charge;
    double efficiency;
    double power;

  
    cout << "Введіть назву станції: ";
    cin >> model_name;

    cout << "Введіть паспортну ємність (Вт*год): ";
    cin >> capacity;
    if (capacity <= 0) {
        cout << "Помилка ємність повинна бути більшою за 0." << endl;
        return 1;
    }

    cout << "Введіть вік станції (років): ";
    cin >> years;
    if (years < 0 || years > 20) {
        cout << "Помилка неправильний вік станції." << endl;
        return 1;
    }

    cout << "Введіть рівень заряду (%): ";
    cin >> charge;
    if (charge < 0 || charge > 100) {
        cout << "Помилка заряд має бути від 0 до 100." << endl;
        return 1;
    }

    cout << "Введіть ККД інвертора (%): ";
    cin >> efficiency;
    if (efficiency <= 0 || efficiency > 100) {
        cout << "Помилка ККД має бути від 1 до 100." << endl;
        return 1;
    }

    cout << "Введіть потужність приладу (Вт): ";
    cin >> power;
    if (power <= 0) {
        cout << "Помилка потужність має бути більшою за 0." << endl;
        return 1;
    }


    double real_capacity = capacity * pow(0.98, years);
    
    double stored_energy = real_capacity * charge / 100.0;
    double useful_energy = stored_energy * efficiency / 100.0;
    double energy_loss = stored_energy - useful_energy;
    
    double total_hours = useful_energy / power;
    
    int hours = total_hours;
    int minutes = (total_hours - hours) * 60;


    cout << "Модель станції " << model_name << endl;
    cout << "Паспортна ємність " << round(capacity * 10.0) / 10.0 << " Вт·год" << endl;
    cout << "Вік станції " << years << " р." << endl;
    cout << "Фактична ємність " << round(real_capacity * 10.0) / 10.0 << " Вт·год" << endl;
    cout << "Рівень заряду %  " << round(charge * 10.0) / 10.0 << " %" << endl;
    cout << "ККД інвертора %  " << round(efficiency * 10.0) / 10.0 << " %" << endl;
    cout << "Запас енергії " << round(stored_energy * 10.0) / 10.0 << " Вт·год" << endl;
    cout << "Корисна енергія  " << round(useful_energy * 10.0) / 10.0 << " Вт·год" << endl;
    cout << "Втрати на перетворенні " << round(energy_loss * 10.0) / 10.0 << " Вт·год" << endl;
    cout << "Час роботи годин  " << round(total_hours * 10.0) / 10.0 << " год  = " << hours << " год " << (minutes < 10 ? "0" : "") << minutes << " хв" << endl;
    
    return 0;
}