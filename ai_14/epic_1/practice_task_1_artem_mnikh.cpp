#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;
int main(){

    // Оголошення змінних
    const double loss = 2; // відсоток втрати ємності
    double C, eff, P, C_eff, charge, E_stored, E_useful, E_loss, T, h;
    int years, m;
    string model;


    // Отримання значень та їх валідація

    cout << "Модель станції: ";
    if (!(cin >> model) || model.length() > 31) {
        cout << "Помилка. Некоректні дані моделі" << endl;
        return 1;
    }
    cout << "Паспортна ємність (Вт·год): ";
    if (!(cin >> C) || C < 0){
        cout << "Помилка. Некоректна паспортна ємність" << endl;
        return 1;
    }
    cout << "Вік станції (років): ";
    if (!(cin >> years) || years < 0 || years > 20) {
        cout << "Помилка. Некоректний вік станції" << endl;
        return 1;
    }
    cout << "Рівень заряду (%): ";
    if (!(cin >> charge) || charge < 0 || charge > 100) {  
        cout << "Помилка. Некоректний рівень заряду" << endl;
        return 1;
    }   
    cout << "ККД інвертора (%): ";
    if (!(cin >> eff) || eff <= 0 || eff > 100) {
        cout << "Помилка. Некоректний ККД інвертора" << endl;
        return 1;
    }
    cout << "Потужність приладу (Вт): ";
    if (!(cin >> P) || P <= 0) {
        cout << "Помилка. Некоректна потужність приладу" << endl;
        return 1;
    }
    // Обичислюємо фактичну ємність з урахуванням віку, Вт·год
    C_eff = C * pow((1 - loss / 100), years);
    // Обчислюємо запас енергії при поточному заряді, Вт·год
    E_stored = C_eff * charge / 100;
    // Обчислюємо корисну енергію, що дійде до приладу, Вт·год
    E_useful = E_stored * eff / 100;
    // Обчислюємо втрати на перетворенні напруги, Вт·год
    E_loss = E_stored - E_useful;
    // Обчислюємо час роботи, годин
    T = E_useful / P;
    h = trunc(T);
    m = (T - h)*60;

    // Виводимо результати
    cout << fixed;
    cout << "Модель: " << model << endl;
    
    // Виводимо значення з 1 знаком після коми
    cout << setprecision(1);
    cout << "Паспортна ємність: " << C << " Вт·год" << endl;
    cout << "Вік станції: " << years << " р." << endl;
    cout << "Фактична ємність: " << C_eff << " Вт·год" << endl;

    // Виводимо значення без коми
    cout << setprecision(0);
    cout << "Рівень заряду: " << charge << " %" << endl;
    
    // Виводимо 2 знаки після коми
    cout << setprecision(2);
    cout << "ККД інвертора: " << eff << " %" << endl;
    
    //Знову виводимо  1 знак після коми
    cout << setprecision(1);
    cout << "Запас енергії: " << E_stored << " Вт·год" << endl;
    cout << "Корисна енергія: " << E_useful << " Вт·год" << endl;
    cout << "Втрати на перетворенні: " << E_loss << " Вт·год" << endl;
    
    // Ще раз 2 знаки після коми для годин та форматуємо хвилини з нулем (05)
    cout << setprecision(2);
    cout << "Час роботи: " << T << " год = " << h << " год ";
    if (m < 10){
        cout << "0" << m << " хв" << endl;
    } else {
        cout << m << " хв" << endl;
    }
    return 0;
}