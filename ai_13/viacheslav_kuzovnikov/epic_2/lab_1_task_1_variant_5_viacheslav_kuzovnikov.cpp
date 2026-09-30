/*
Лабораторна №1
Завдання №1
Варіант №5
Кузовніков В'ячеслав Євгенійович
ШІ-13
*/

#include <iostream>
#include <cmath>
using namespace std;
int main (){
    float a, b;
    cout << "Введіть а: ";
    cin >> a; 

    cout << "Введіть b: ";
    cin >> b;

    float c = (pow(a - b, 3)) - (pow(a, 3) - (3*b*pow(a, 2)));
    cout << c << endl;


    float d = (pow(b, 3)) - (3*pow(b, 2)*a);
    cout << d << endl;


    float e = c/d;

    cout << e << endl;
    

    double a1, b1;
    cout << "Введіть а: ";
    cin >> a1; 

    cout << "Введіть b: ";
    cin >> b1;


    double f = (pow(a1 - b1, 3)) - (pow(a1, 3) - (3*b1*pow(a1, 2)));
    cout << f << endl;


    double g = (pow(b1, 3)) - (3*pow(b1, 2)*a1);
    cout << g << endl;


    double h = f/g;

    cout << h << endl;


    return 0;
}