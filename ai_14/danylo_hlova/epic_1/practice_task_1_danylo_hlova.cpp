/*Epic 1 - Practice Task. Глова Данило, СШІ-14*/
#include <iostream>
#include<cmath>
#include<string>
#include<iomanip> //для фіксованої кількості знаків після коми

using namespace std;

int main()
{
    //оголошення змінних
    string model;
    double c;//ємність акумулятора
    int years;//вік акумулятора
    int charge;//заряд
    double eff;//ККД інвертора
    double p;//потужність приладу
    
    // ввід даних з перевіркою
    cout << "Модель станції: ";
    cin >> model;
    if (model.length() > 31) {
        cout << "Помилка: назва моделі має бути одним словом без пробілів (до 31 символа)." << endl;
        return 1;
    }

    cout<< "ємність станції(Вт*год): ";
    cin>> c;
    if(c<=0){
        cout << "Помилка: ємність повинна бути більша за 0" << endl;
        return 1;
    }

    cout<< "Вік станції(років): ";
    cin>> years;
    if(years<0 || years>20){
        cout << "Помилка: вік станції повинен бути від 0 до 20" << endl;
        return 1;
    }

    cout<< "Рівень заряду(%): ";
    cin>> charge;
    if(charge<0 || charge>100){
        cout << "Помилка: заряд станції може бути від 0% до 100%" << endl;
        return 1;
    }

    cout<< "ККД інвертора(%): ";
    cin>> eff;
    if(eff<0 || eff>100){
        cout << "Помилка: ККД інвертора може бути від 0% до 100%" << endl;
        return 1;
    }

    cout<< "потужність приладу(Вт): ";
    cin>> p;
    if(p<0){
        cout << "Помилка: потужність приладу повинна бути більша за 0" << endl;
        return 1;
    }

    //розрахунки
    const double LOSE=2.0;// відсоток втрати ємності за рік
    const double PERCENT=100.0; // Коефіцієнт для переведення відсотків у частку
    const int MINUTES = 60;// Кількість хвилин в одній годині

    //фактична ємність
    double c_eff= c*pow(1.0-LOSE/PERCENT,years);

    //запас енергії при поточному заряді
    double e_stored=c_eff*charge/PERCENT;

    //корисна енергія
    double e_useful=e_stored*eff/PERCENT;

    //втрати під час перетворення
    double e_loss=e_stored-e_useful;

    //час роботи
    double t=e_useful/p;
    int h=t;
    int m=(t-h)*MINUTES;

    //вивід
    cout<<"--------Характеристика станції--------"<<endl;
    cout<< "Модель: "<< model<<endl;

    cout << fixed; // Фіксує вивід дробових чисел

    cout<< "Паспортна ємність: "<<setprecision(1)<<c <<" Вт*год"<<endl;
    cout<< "Вік станції: "<< years<<" р."<<endl;
    cout<< "Фактична ємність: "<<setprecision(1)<< c_eff <<" Вт*год"<<endl;
    cout<< "Рівень заряду: "<< charge <<" %"<<endl;
    cout<< "ККД інвертора: "<<setprecision(2)<<eff<<" %"<<endl;
    cout<< "Запас енергії: "<<setprecision(1)<< e_stored<<" Вт*год"<<endl;
    cout<< "Корисна енергія: "<<setprecision(1)<< e_useful<<" Вт*год"<<endl;
    cout<< "Витрати на перетворенні: "<< setprecision(1)<<e_loss<<" Вт*год"<<endl;
    //setfill('0') << setw(2) дописує 0 в хвилинах
    cout<< "Час роботи: "<<setprecision(2)<< t<<" год = "<<h<<" год "<<setfill('0') << setw(2)<<m<<" хв"<<endl;

    return 0;
}