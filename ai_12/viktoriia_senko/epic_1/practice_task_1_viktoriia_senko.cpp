/*"Автономність портативної зарядної станції" 
Автор:Сенько Вікторія
Група: ШІ-12 group3*/
#include <iostream> //введення та виведення даних
#include <string> //створення текстових рядків string
#include <cmath> //можливість виконувати математичні дії
#include <iomanip> //встановлення кількості знаків після коми (setprecision)
using namespace std;
int main() {
    setlocale(LC_ALL, "uk_UA");
    string name; 
    double c, eff, P, c_eff, E_stored, E_useful, E_loss, T;
    int years, charge, h, m;
    //задаємо константу - зношення акамулятора за рік у відсотках
    const double Battery_Degradation=2.0;
    cout<<"Введіть модель станції: ";
    cin>>name;
    cout<<"Введіть паспортну ємність (Вт·год): ";
    cin>> c;
    cout<<"Введіть вік станції (років): ";
    cin>>years;
    cout<<"Введіть рівень заряду (%): ";
    cin>>charge;
    cout<<"Введіть ККД інвертора (%): ";
    cin>>eff;
    cout<<"Введіть потужність приладу (Вт): ";
    cin>>P;
  
    //Перевіряємо, чи підходить дане значення під умову
    
    if(name.length() > 31)
    {
       cout<<"Помилка: назва моделі станції має бути не довша за 31 символ."<<endl;
    return 1;
     }
    
    if(c<=0) 
    {
        cout<<"Помилка: паспортна ємність повинна бути більше 0."<<endl;
        return 1;
    }
    
    if(years<0 || years>20)
    {
        cout<<"Помилка: вік станції мусить бути від 0 до 20."<<endl;
        return 1;
    }
     
    if(charge <0 || charge > 100){
        cout<<"Помилка: рівень заряду мусить бути від 0 до 100."<<endl;
        return 1;
    }
    
     if(eff <=0 || eff > 100){
        cout<<"Помилка: ККД інвертора має бути більше за 0 і не більше 100."<<endl;
        return 1;
    }
    if(P<=0){
        cout<<"Помилка: потужність має бути більше за 0."<<endl;
        return 1;
    }
      //___ОБЧИСЛЕННЯ ДАНИХ______
    //рахуємо фактичну ємність (Вт·год), використовуємо pow, щоб виконати дію піднесення до степеня
    c_eff=c*pow(1.0-(Battery_Degradation/100.0), years); 
    //обчислюємо запас енергії (Вт·год)
    E_stored=c_eff*charge/100.0;
    //обчислюємо корисну енергію, яка поступає до приладу (Вт·год)
    E_useful=E_stored*eff/100.0;
    //обчислюємо втрати на перетворенні напруги (Вт·год)
    E_loss=E_stored-E_useful;
    //обчислюємо час роботи (години)
    T=E_useful/P;
    //використвовуємо static_cast, щоб виділити цілу частину
    //виділяємо повні години (год)
    h= static_cast<int>(T); 
    //обчислюємо хвилини, що залишилися (хв)
    m=static_cast<int>((T-h)*60.0);
    

    cout<<endl;
    cout<<"Модель:                  "<<name<<endl;
    cout<<fixed<<setprecision(1);
    cout<<"Паспортна ємність:            "<<c<<" Вт·год"<<endl;
    cout<<"Вік станції (років):              "<<years<<" р."<<endl;
    cout<<"Фактична ємність:             "<<c_eff<<" Вт·год"<<endl;
    cout<<"Рівень заряду (%):              " <<charge<<" %"<<endl;
    cout<<fixed<<setprecision(2);
    cout<<"ККД інвертора (%):            "<<eff<<" %"<<endl;
    cout<<fixed<<setprecision(1);
    cout<<"Запас енергії:                "<<E_stored<<" Вт·год"<<endl;
    cout<<"Корисна енергія:              "<<E_useful<<" Вт·год"<<endl;
    cout<<"Витрати на перетворенні:      "<<E_loss<<" Вт·год"<<endl;
    cout<<fixed<<setprecision(2);
    cout<<"Час роботи:                    "<<T<<" год = "<< h << " год "<< setfill('0') << setw(2) << m << " хв" << endl;

    return 0;
}