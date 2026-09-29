/*
    Задача: Автономність портативної зарядної станції
    Автор: Стецюк Петро
    Група: ШІ-12
*/
#include <iostream>
#include <string>
#include<cmath>
#include<iomanip>

using namespace std;

int main() {
   // Введення змінних
   string Model; // Модель
   double Capacity, KKD, Power; // Паспортна ємність, ККД інвертора, потужність приладу
   int years, charge; // Вік станції, рівень заряду
   const double Loss=2; // Відсоток втрати ємності за рік
   // Введення данних та валідація 
   cout << "Модель станції: ";
   cin>>Model;
   if(Model.size()>31)
   {
    cout<< "Error: wrong data input";
    return 1;
   }
   cout<<"Паспортна ємність (Вт*год): ";
   cin>>Capacity;
   if(Capacity<=0)
   {
      cout<<"Error: wrong data input";
      return 1;
   }
   cout<<"Вік станції (років): ";
   cin>>years;
   if(years<=0||years>20)
   {
      cout<< "Error: wrong data input";
      return 1;
   }
   cout<<"Рівень заряду (%): ";
   cin>>charge;
   if(charge<=0||charge>100)
   {
      cout<< "Error: wrong data input";
      return 1;
   }
   cout<<"ККД інвертора (%): ";
   cin>>KKD;
   if(KKD<=0||KKD>100)
   {
      cout<< "Error: wrong data input";
      return 1;
   }
   cout<<"Потужність приладу (Вт): ";
   cin>>Power;
   if(Power<=0)
   {
      cout<< "Error: wrong data input";
      return 1;
   }

   // Обчислення фактичної ємності з урахуванням віку
   double Capacityfact = Capacity*pow((1-Loss/100),years);

   // Обчислення запасу енергії при поточному заряді
   double E_stored = Capacityfact*charge/100;

   // Обчислення корисної енергії ,що дійде до приладу
   double E_useful = E_stored*KKD/100;

   // Обчислення втрат енергії на перетворенні напруги
   double E_loss = E_stored-E_useful;

   // Обчислення часу роботи
   double Time = E_useful/Power;

   // Години роботи
   int hours = int(Time);
   
   // Хвилини роботи 
   int mins = int((Time-hours)*60);

   // Вивід данних
   cout<<fixed;
   cout<<"Модель:"<<setw(25)<<Model<<endl;
   cout<<"Паспортна ємність:"<<setw(15)<<setprecision(1)<<Capacity<<" Вт*год"<<endl; 
   cout<<"Вік станції:"<<setw(17)<<years<<" р."<<endl;
   cout<<"Фактична ємність:"<<setw(16)<<setprecision(1)<<Capacityfact<<" Вт*год"<<endl;
   cout<<"Рівень заряду:"<<setw(17)<<charge<<" %"<<endl;
   cout<<"ККД інвертора:"<<setw(19)<<setprecision(2)<<KKD<<" %"<<endl;
   cout<<"Запас енергії:"<<setw(19)<<setprecision(1)<<E_stored<<" Вт*год"<<endl;
   cout<<"Корисна енергія:"<<setw(17)<<setprecision(1)<<E_useful<<" Вт*год"<<endl;
   cout<<"Втрати на перетворенні:"<<setw(10)<<setprecision(1)<<E_loss<<" Вт*год"<<endl;
   cout<<"Час роботи:"<<setw(21)<<setprecision(2)<<Time<<" год = "<<hours<<" год ";
   if(mins<10) cout<<"0"<<mins<<" хв";
    else cout<<mins<<" хв";

   return 0;

}