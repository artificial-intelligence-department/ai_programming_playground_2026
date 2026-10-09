/*
Автономність портативної зарядної станції
Перерва Олександр
ШІ-11
*/

// Підключення бібліотек
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    // оголошення змінних
    string name; // Модель станції
    double C; // Паспортна ємність
    int years; // Вік станції
    int charge; // Рівень заряду
    double eff; // ККД інвертора
    int P; // Потужність приладу
    // оголошення константи (Відсоток втрати ємності на рік)
    const double V=2; 
    // Ввід і перевірка даних
    cout<<"Модель станції: ";
    cin>>name; cout<<endl;
    if(name.length()>31){
        cout<<"Модель станції не може перевищувати 31 символ"<<endl;
        return 1;
    }
    cout<<"Паспортна ємність (Вт•год): ";
    cin>>C; cout<<endl;
    if(C<=0){
        cout<<"Паспортна ємність має бути більшою за 0"<<endl;
        return 1;
    }
    cout<<"Вік станції (років): ";
    cin>>years; cout<<endl;
    if(years<0 || years>20){
        cout<<"Вік має бути від 0 до 20"<<endl;
        return 1;
    }
    cout<<"Рівень заряду (%): ";
    cin>>charge; cout<<endl;
    if(charge<0 || charge>100){
        cout<<"Рівень заряду має бути від 0 до 100"<<endl;
        return 1;
    }
    cout<<"ККД інвертора (%): ";
    cin>>eff; cout<<endl;
    if(eff<=0 || eff>100){
        cout<<"ККД інвертора має бути більше 0 і не більше 100"<<endl;
        return 1;
    }
    cout<<"Потужність приладу (Вт): ";
    cin>>P; cout<<endl;
    if(P<=0){
        cout<<"Потужність приладу має бути більше 0"<<endl;
        return 1;
    }
    double C_eff; // Фактична ємність станції
    if(years==0){
        C_eff=C;
    } else{
        C_eff=C*pow((1-V/(100)),years); // Обчислення фактичної ємності з урахуванням віку
    }
    double E_stored=C_eff*charge/100; // Обчислення запасу енергії при поточному заряді
    double E_useful=E_stored*eff/100; // Обчислення корисної енергії, що дійде до приладу
    double E_loss=E_stored-E_useful; // Обчислення втрат на перетворенні напруги
    double T=E_useful/P; // Обчислення часу роботи приладу в годинах
    int h =floor(T); // Обчислення повних годин часу роботи
    int m =floor((T-h) * 60); // Обчислення хвилин, що залишились
    // Вивід результатів
    cout<<"Модель: "<<name<<endl;
    cout<<"Паспортна ємність: "<<fixed<<setprecision(1)<<C<<" Вт•год"<<endl;
    cout<<"Вік станції: "<<years<<" р."<<endl;
    cout<<"Фактична ємність: "<<fixed<<setprecision(1)<<C_eff<<" Вт•год"<<endl;
    cout<<"Рівень заряду: "<<charge<<" %"<<endl;
    cout<<"ККД інвертора: "<<fixed<<setprecision(2)<<eff<<" %"<<endl;
    cout<<"Запас енергії: "<<fixed<<setprecision(1)<<E_stored<<" Вт•год"<<endl;
    cout<<"Корисна енергія: "<<fixed<<setprecision(1)<<E_useful<<" Вт•год"<<endl;
    cout<<"Втрати на перетворенні: "<<fixed<<setprecision(1)<<E_loss<<" Вт•год"<<endl;
    if(m<10) cout<<"Час роботи: "<<fixed<<setprecision(2)<<T<<" год = "<<h<<" год 0"<<m<<" хв"<<endl;
    else cout<<"Час роботи: "<<fixed<<setprecision(2)<<T<<" год = "<<h<<" год "<<m<<" хв"<<endl;


    return 0;
}