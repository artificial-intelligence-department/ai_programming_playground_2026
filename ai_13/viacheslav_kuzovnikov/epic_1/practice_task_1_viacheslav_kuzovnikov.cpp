/*
Автономність портативної зарядної станції
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
#include <string> // для змінної string
#include <cmath> // для математичних розрахунків
#include <iomanip> // бібліотека для setprecision (кількість знаків після коми)

using namespace std;

int main (){
    setlocale (LC_ALL, "uk_UA"); // Використання української мови

    string model;
    cout << "Введіть модель станції:";
    cin >> model;

    if (model.size() > 31){
        cout << "Неправильний ввід даних: модель станції має бути менше 32 симаолів.";
        return 1;
    }


    int c_battery;
    cout << "Паспортна ємність (Вт·год): ";
    cin >> c_battery;

    if (c_battery <= 0 ){
        cout << "Неправильний ввід даних: ємність має бути більше 0.";
        return 1;
    }


    int num_years;
    cout << "Вік станції (років): ";
    cin >> num_years;
    if (num_years < 0 || num_years > 20) { // || - логічне або
        cout << "Неправильний ввід даних: вік станції мусить бути від 0 до 20.";
        return 1;
    }


    float battery;
    cout << "Рівень заряду (%): ";
    cin >> battery;
    if (battery < 0 || battery > 100){
        cout << "Неправильний ввід даних: рівень заряду має бути від 0 до 100.";
        return 1;
    }


    float kkd_invent;
    cout << "ККД інвентора (%): ";
    cin >> kkd_invent;
    if (kkd_invent <= 0 || kkd_invent > 100){
        cout << "Неправильний ввід даних: ККД має бути від 0 до 100.";
        return 1;
    }


    int p_invent;
    cout << "Потужність приладу (Вт): ";
    cin >> p_invent;
    if (p_invent < 0 ){
        cout << "Неправильний ввід даних: потужність має бути більше 0.";
        return 1;
    }


    float C_eff = c_battery * pow (1 - 0.02, num_years); // обчислюємо фактичну ємність з урахуванням віку, Вт·год, 0.02 - втрати ємності за рік.
    float E_stored = C_eff * battery / 100; // обчислюємо запас енергії при поточному заряді, Вт·год
    float E_useful = E_stored * kkd_invent / 100; // обчислюємо корисну енергію, що дійде до приладу, Вт·год
    float E_loss = E_stored - E_useful; // обчислюємо втрати на перетворенні напруги, Вт·год
    float time = E_useful / p_invent; // обчислюємо час роботи, годин
    int h = time; // обчислюємо повні години
    int m = (time - h)*60; // обчислюємо хвилини, що залишились


    cout << "" << endl;
    cout << "" << endl;

    cout << "Модель:" << "                   "<< model << endl;
    cout << "Паспортна ємність: "<< fixed << setprecision(1) << "       "<< c_battery << " Вт·год" << endl;
    cout << "Вік станції:" << "              "<< num_years << " р." << endl;
    cout << "Фактична ємність:" << fixed << setprecision(1) << "         "<< C_eff << " Вт·год" << endl;
    cout << "Рівень заряду:" << "            "<< battery << " %" << endl;
    cout << "ККД інвентора:" << fixed << setprecision(2) << "            "<< kkd_invent << " %" << endl;
    cout << "Запас енергії:" << fixed << setprecision(1) << "            "<< E_stored << " Вт·год" << endl;
    cout << "Корисна енергія:" << fixed << setprecision(1) << "          "<< E_useful << " Вт·год" << endl; 
    cout << "Втрати на перетворенні:" << fixed << setprecision(1) << "   "<< E_loss << " Вт·год" << endl;
    cout << "Час роботи:" << fixed << setprecision(2) << "               "<< time<< " год" << " = " << h << " год " << setfill('0') << setw(2) << m << " хв" << endl;  
    // setfill('0') - встановлює символ-заповнювач , а setw(2) - виводить 2 знаки



    return 0;
}









