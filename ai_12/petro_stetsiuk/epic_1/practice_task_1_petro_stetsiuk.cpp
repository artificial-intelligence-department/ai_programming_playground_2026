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
   string Model;
   double Capacity, KKD, Power;
   int years, charge;
   const double Loss=2; // Відсоток втрати ємності за рік
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
      cout<< "Error: wrong data input";
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
   double Capacityfact = Capacity*pow((1-Loss/100),years);
   double E_stored = Capacityfact*charge/100;
   double E_useful = E_stored*KKD/100;
   double E_loss = E_stored-E_useful;
   double Time = E_useful/Power;
   int hours = int(Time);
   int mins = int((Time-hours)*60);

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