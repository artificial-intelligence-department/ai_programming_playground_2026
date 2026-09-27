/* 
Епік 1. Практичне завдання: Автономність портативної зарядної станції
Автор: Боднар Василь Іванович
Група: ШІ-12
*/


#include <iostream>
#include <cmath>
#include <iomanip> 
using namespace std;

int main() {
    
    
    //деградації зяряду станції щороку на 2%
    const double degradation_per_year = 2;
    //Назва моделі портативної зарядної станції
    string model_name;
    //паспортна ємність станції 
    double capacity = 0;
    //вік станції
    int years = 0;
    //рівень заряду
    int charge = 0;
    //ккд інвертора
    double efficiency = 0;
    //потужність приладу 
    double power = 0;

    cout << "Ведіть модель зарядної станції: ";
    cin >> model_name;
    if (model_name.length() > 31) {
        cout << "Помилка: назвою моделі повинно бути одне слово довжиною до 31 літери" << endl;
        return 1;
    }

    cout << "Введіть паспортну ємність зарядної станції(в Вт/год): ";
    cin >> capacity;
    if (capacity <= 0.0) {
        cout << "Помилка: ємність станції повинна бути більше 0" << endl;
        return 1;
    }

    cout << "Введіть вік зарядної станції: ";
    cin >> years;
    if (years < 0 || years > 20) {
        cout << "Помилка: вік станції повинен бути в межі від 0 до 20 років" << endl;
        return 1;
    }

    cout << "Введіть рівень заряду станції(у %): ";
    cin >> charge;
    if (charge < 0 || charge > 100) {
        cout << "Помилка: рівень заряду повинен бути в межі від 0 до 100" << endl;
        return 1;
    }

    cout << "Введіть ККД інвертора(у %): ";
    cin >> efficiency;
    if (efficiency < 0 || efficiency > 100) {
        cout << "Помилка: ККД інвертора повинен бути в межі від 0 до 100" << endl;
        return 1;
    }

    cout << "Введіть потужність приладу(у Вт): ";
    cin >> power;
    if (power <= 0) {
        cout << "Помилка: потужність приладу повинна бути більше 0" << endl;
        return 1;
    }

    // Фактична ємність з урахуванням віку, Вт·год
    double C_eff = capacity * pow(1 - degradation_per_year / 100.0, years);
    // Запас енергії при поточному заряді, Вт·год
    double E_stored = C_eff * charge / 100.0;
    // Корисна енергія, що дійде до приладу, Вт·год
    double E_useful = E_stored * efficiency / 100.0;
    // Втрати на перетворенні напруги, Вт·год
    double E_loss = E_stored - E_useful;
    // Час роботи приладу, год
    double T = E_useful / power;
    // Повні години роботи
    int h = int(T);
    // Хвилини, що залишились
    int m = int((T - h) * 60);
    cout << endl;

    cout << fixed;

    cout << "Модель зарядної станції:   " << model_name << endl;
    cout << "Паспортна ємність:   " << setprecision(1) << capacity << " Вт·год" << endl;
    cout << "Вік станції:   " << years << " років" << endl;
    cout << "Фактична ємність:   " << setprecision(1) << C_eff << " Вт·год" << endl;
    cout << "Рівень заряду:    " << charge << "%" << endl;
    cout << "ККД інвертора:   " << setprecision(2) << efficiency << "%" << endl;
    cout << "запас енергії:   " << setprecision(1) << E_stored << " Вт·год" << endl;
    cout << "Корисна енергія:   " << setprecision(1) << E_useful << " Вт·год" << endl;
    cout << "Втрати на перетворенні:   " << setprecision(1) << E_loss << " Вт·год" << endl;
    cout << "Час роботи:   " << setprecision(2) << T << " год  = " << h << " год ";
    if (m < 10) {
        cout << "0" << m << " хв";
    }
    else {
        cout << m << " хв";
    }

    return 0;
}