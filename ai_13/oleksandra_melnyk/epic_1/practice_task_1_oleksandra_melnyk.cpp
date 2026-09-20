/*Задача: Автономність портативної зарядної станції
Мельник Олександра
ШІ-13
 */
#include <iostream>
#include <iomanip> //бібліотека для округлення
#include <string> //бібліотека для введення назви станції
#include <cmath>
using namespace std;

int main() 
{
    string model;
    double capacity, capacityf,kkd,energyuseful, energy, power, lose, time;
    int  year, charge; 
    float k=0.02; //відсоток втрати ємності за рік 
    cout << "Модель станції: ";
    cin >> model;
    if (model.length()> 31) {
        cout<<"Помилка: Модель зарядної станції не повинна перевищувати 31 символів."<<endl;
        return 1;
    }
    cout << "Паспортна ємність (Вт·год): ";
    cin >> capacity;
    if (capacity<0) {
        cout<<"Помилка: Паспортна ємність не може бути від'ємною."<<endl;
        return 1;
    }
    cout << "Вік станції (років): ";
    cin >> year;
    if (year<0 || year>20) {
        cout<<"Помилка: Вік станції не може бути від'ємним або перевищувати 20 років."<<endl;
        return 1;
    }
    cout << "Рівень заряду (%): ";
    cin >> charge;
    if (charge<0 || charge>100) {
        cout<<"Помилка: Рівень заряду не може бути від'ємним або перевищувати 100%."<<endl;
        return 1;
    }
    cout << "ККД інвертора (%): ";
    cin>> kkd;
    if (kkd<0 || kkd>100) {
        cout<<"Помилка: ККД інвертора не може бути від'ємним або перевищувати 100%."<<endl;
        return 1;
    }
    cout << "Потужність приладу (Вт): ";
    cin >> power;
    if (power<=0) {
        cout<<"Помилка: Потужність приладу не може бути від'ємною."<<endl;
        return 1;
    }
    // перевірка введення на істинність 

    cout <<"Модель зарядної станції:           "<<model<<endl;;
    cout<<"Паспортна ємність (Вт*год):          "<<capacity<<fixed<<setprecision(1)<<" Вт*год"<<endl;
    cout<<"Вік станції (років):         "<<year<<endl;
    capacityf=capacity*pow(1.0-k,year); // Обчислюємо фактичну ємність з урахуванням зношення акумулятора (у Вт·год) 
    energy=capacityf*(charge/100.0); // Знаходимо запас енергії при поточному рівні заряду (у Вт·год)
    energyuseful=energy*(kkd/100.0); // Визначаємо корисну енергію, яка дійде до приладу через інвертор (у Вт·год)
    lose=energy-energyuseful; // Розраховуємо втрати енергії на перетворення напруги (у Вт·год)
    time=energyuseful/power; //обчислюємо час роботи приладу у годинах
    int h=int(time);
    int m=int((time-h)*60); // Виокремлюємо повні години та залишок у хвилинах для зручного виводу
    
    cout<<"Фактична ємність:            "<<capacityf<<fixed<<setprecision(1)<<" Вт*год"<<endl;
    cout<<"Рівень заряду:                 "<<charge<<"%"<<endl;
    cout<<"ККД інвертора:               "<<kkd<<fixed<<setprecision(2)<<"%"<<endl;
    cout<<"Запас енергії:               "<<energy<<fixed<<setprecision(1)<<" Вт*год"<<endl;
    cout<<"Корисна енергія:             "<<energyuseful<<fixed<<setprecision(1)<<" Вт*год"<<endl;
    cout<<"Втрати на перетворенні:      "<<lose<<fixed<<setprecision(1)<<" Вт*год"<<endl;
    cout<<"Час роботи приладу:          "<<h<<" год "<<m<<" хв"<<endl;
}