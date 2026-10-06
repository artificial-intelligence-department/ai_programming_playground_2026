
/*"Автономність портативної станції", Дохнюк Богдан , cші-14*/ 
#include <iostream> 
#include <cmath>
using namespace std ; 
 
void Exit () 
{ 
cout<<"Помилка вводу.Введіть коректне значення!"; 
exit(1); 
} 
 
//введення та перевірка даних 
int main() { 
const int MAX_LENGHT = 31; // Максимальна довжина назви
const int MAX_AGE = 20; //Максимальний вік станції
const int MAX_PERCENT = 100 ; //Максимальний заряд станції та ККД
const double PERCENT_BASE = 100.0; //Константа для переведення відсотків у частку
const double YEARLY_CAPACITY_LOSS = 2.0; //Втрата ємності за рік

string model, c = ""; 
double eff,P; 
unsigned short C,years,charge;  
  
//введення та перевірка даних 

cout<<"Модель станції : "; 
cin>>model;  
if(model.length()>MAX_LENGHT)Exit(); 
 
cout<<"Паспортна ємність, Вт·год : "; 
cin>>C; 
if(C<=0)Exit(); 
 
cout<<"Вік станції, років : "; 
cin>>years; 
if(years<0||years>MAX_AGE)Exit(); 
 
cout<<"Рівень заряду, % : "; 
cin>>charge; 
if(charge<0||charge>MAX_PERCENT)Exit(); 
 
cout<<"ККД інвертора, % : "; 
cin>>eff; 
if(eff<=0||eff>MAX_PERCENT)Exit(); 
 
cout<<"Потужність приладу, Вт : "; 
cin>>P; 
if(P<=0)Exit(); 
 
//розрахунки над даними
//Фактична ємність з урахуванням віку, Вт·год 
//Піднесення до степеня 
double C_eff=C * pow (1-YEARLY_CAPACITY_LOSS / PERCENT_BASE, years); 
//Запас енергії при поточному заряді, Вт·год 
double E_stored = C_eff * charge/ 100; 
//Корисна енергія, що дійде до приладу, Вт·год 
double E_useful = E_stored * eff / 100; 
//Втрати на перетворенні напруги, Вт·год 
double E_loss = E_stored - E_useful; 
//Час роботи, годин 
double T=E_useful / P; 
//Повні години 
int h = T; 
//Хвилини, що залишились 
int m=((T - h) * 60); 
 
//заокруглення даних
T=double(int(T*100))/100; 
C_eff=double(int(C_eff*10))/10; 
E_stored=double(int(E_stored*10))/10; 
E_useful=double(int(E_useful*10))/10; 
E_loss=double(int(E_loss*10))/10; 
 
cout<<"Модель станції : "<<model<<endl; 
cout<<"Паспортна ємність, : "<<C<<" Вт·год"<<endl; 
cout<<"Вік станції : "<<years<<" р."<<endl; 
cout<<"Фактична ємність : "<<C_eff<<" Вт·год"<<endl; 
cout<<"Рівень заряду, % : "<<charge<<" %"<<endl; 
cout<<"ККД інвертора, % : "<<eff<<" %"<<endl; 
cout<<"Запас енергії при поточному заряді : "<<E_stored<<" Вт·год"<<endl; 
cout<<"Корисна енергія, що дійде до приладу : "<<E_useful<<" Вт·год"<<endl; 
cout<<"Втрати на перетворенні : "<<E_loss<<" Вт·год"<<endl; 
 
if(m<10)c = "0"; 
 
cout<<"Час роботи,годин : "<<T<<" год "<<" = "<<h<<" год "<<c<<m<<" хв"<<endl; 
 
    return 0; 
}