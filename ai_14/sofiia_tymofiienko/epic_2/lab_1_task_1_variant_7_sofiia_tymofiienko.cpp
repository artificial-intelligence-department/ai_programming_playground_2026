/*Tymofiienko Sofiia SHI-14*/

#include <iostream>
using namespace std;

int main(){
    
float a=1000.0f;
float b=0.0001f;
cout<< "a= "<<a<<endl;
cout<< "b= "<<b<<endl;

// Обчислюємо чисельник з використанням проміжних змінних:
float step_1= a-b;
float step_2= step_1 * step_1 * step_1;
float step_3= a*a*a;
float step_4= step_2-step_3;

// Обчислюємо знаменник з використанням проміжних змінних:
float step_5= b*b*b;
float step_6= 3*a*(b*b);
float step_7= 3*(a*a)*b;
float step_8= step_5-step_6;
float step_9= step_8-step_7;

// Обчислюємо загальний вираз:
float step_10=step_4/step_9;

cout<< "Вираз, виконаний через float набуває значення: "<<step_10<<endl;

// Обчислюємо той самий вираз через double:
double a_d=1000.0;
double b_d=0.0001;

double step_1d= a_d-b_d;
double step_2d= step_1d * step_1d * step_1d;
double step_3d= a_d*a_d*a_d;
double step_4d= step_2d-step_3d;

double step_5d= b_d*b_d*b_d;
double step_6d= 3*a_d*(b_d*b_d);
double step_7d= 3*(a_d*a_d)*b_d;
double step_8d= step_5d-step_6d;
double step_9d= step_8d-step_7d;

double step_10d=step_4d/step_9d;

cout<< "Вираз, виконаний через double набуває значення: "<<step_10d<<endl;
cout << "\n================= ПОРІВНЯННЯ ТА ПОЯСНЕННЯ =================" << endl;
    cout << "1. Результат для float:  " << step_10 << endl;
    cout << "2. Результат для double: " << step_10d << endl; 
    cout << "Пояснення: через різну розрядність типів даних (7 значущих цифр у" << endl;
    cout << "float та 15-17 у double), float накопичує похибку округлення" << endl;
    cout << "при роботі з числами різного масштабу (a=1000 і b=0.0001)," << endl;
    cout << "тоді як double дає більш точний і коректний результат." << endl;
    cout << "==========================================================" << endl;
    
return 0;
}


