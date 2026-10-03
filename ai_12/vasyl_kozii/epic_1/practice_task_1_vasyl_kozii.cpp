/*Епік 1. Практичне завдання: Автономність портативної зарядної станції
ШІ-12
Козій Василь Іванович*/
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip> //Для виведення з заданою кількістю цифр після коми та в колонку
using namespace std;
int main()
{
    double const annual_degradation_coefficient=2; //Кеефіцієнт дегредації старнції за рік
    string Station_Model;
    //Вводимо всі змінні і робимо перевірки
    cout <<"Модель станції: ";
    getline(cin, Station_Model); //Якщо в назві будуть пропуски програма всеодно її запише
    if(Station_Model.length()>31){
        cout <<"Введіть назву не довшу за 31 символ" <<endl;
        return 1;
    }
    double C;
    cout <<"Паспортна ємність (Вт·год): ";
    cin >>C;
    if(C<=0){
        cout <<"Введіть додатне число" <<endl;
        return 1;
    }
    int years;
    cout <<"Вік станції (років): ";
    if(cin >>years){
    }
    else{
        cout <<"Введіть ціле число від 0 до 20" <<endl;
        return 1;
    }
    if(years<0 || years>20){
        cout <<"Введіть ціле число від 0 до 20" <<endl;
        return 1;
    }
    double charge;
    cout <<"Рівень заряду (%): ";
    if(cin >>charge){
    }
    else{
        cout <<"Введіть ціле число від 0 до 100" <<endl;
        return 1;
    }
    if(charge<0 || charge>100){
        cout <<"Введіть ціле число від 0 до 100" <<endl;
        return 1;
    }
    double eff;
    cout <<"ККД інвертора (%): ";
    if(cin >>eff){
    }
    else{
        cout <<"Введіть число від 0 до 100" <<endl;
        return 1;
    }
    if(eff<0 || eff>100){
        cout <<"Введіть число від 0 до 100" <<endl;
        return 1;
    }
    double p;
    cout <<"Потужність приладу (Вт): ";
    if(cin >>p){
    }
    else{
        cout <<"Введіть число більше 0" <<endl;
        return 1;
    }
    if(p<=0){
        cout <<"Введіть число більше 0" <<endl;
        return 1;
    }
    //Розрахунки
    double C_eff=C*pow(1-(annual_degradation_coefficient/100), years); //Фактична ємність(Вт·год)
    double E_stored=C_eff*(charge/100); //Запас енергії(Вт·год)
    double E_useful=E_stored*(eff/100); //Корисна енергія(Вт·год)
    double E_loss=E_stored-E_useful; //Втрати енергії на перетворенні(Вт·год)
    double T=E_useful/p; //Час роботи(год+хв)
    double h=(int)T; //Ціла частина від T
    double m=(int)((T-h)*60); //Кількість хвилин(ціла частина від неї)
    //Виводимо дані з заданою кількістю цифр після коми та рівно в колонку
    cout <<"Модель:                    "
    <<right <<setw(10) <<Station_Model <<endl;
    cout <<"Паспортна ємність:         "
    <<right <<setw(10) <<fixed <<setprecision(1) <<C
    <<left <<" Вт·год" <<endl;
    cout <<"Вік станції:               "
    <<right <<setw(10) <<fixed <<setprecision(0) <<years
    <<left <<" р." <<endl;
    cout <<"Фактична ємність:          "
    <<right <<setw(10) <<fixed <<setprecision(1) <<C_eff
    <<left <<" Вт·год" <<endl;
    cout <<"Рівень заряду:             "
    <<right <<setw(10) <<fixed <<setprecision(0) <<charge
    <<left <<" %" <<endl;
    cout <<"ККД інвертора:             "
    <<right <<setw(10) <<fixed <<setprecision(2) <<eff
    <<left <<" %" <<endl;
    cout <<"Запас енергії:             "
    <<right <<setw(10) <<fixed <<setprecision(1) <<E_stored
    <<left <<" Вт·год" <<endl;
    cout <<"Корисна енергія:           "
    <<right <<setw(10) <<fixed <<setprecision(1) <<E_useful
    <<left <<" Вт·год" <<endl;
    cout <<"Втрати на перетворенні:    "
    <<right <<setw(10) <<fixed <<setprecision(1) <<E_loss
    <<left <<" Вт·год" <<endl;
    cout <<"Час роботи:                "
    <<right <<setw(10) <<fixed <<setprecision(2) <<T
    <<left <<" год = ";
    if(m<10){
        cout <<fixed <<setprecision(0) <<h <<" год" <<" 0" <<m <<" хв" <<endl; //Якщо кількість хвилин менша за 10, то перед числом хвилин ставимо 0
    }
    else{
        cout <<fixed <<setprecision(0) <<h <<" год" <<" " <<m <<" хв" <<endl; //Якщо кількість хвилин 10, або більша, то перед нею не ставимо 0
    }
    return 0;
}