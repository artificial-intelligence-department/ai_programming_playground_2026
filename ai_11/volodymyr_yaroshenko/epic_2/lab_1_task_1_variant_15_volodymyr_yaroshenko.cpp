/*  
Лабораторна завдання 1 
Ярошенко Володимир 
11 група 
*/
#include <iostream>
#include <cmath>

using namespace std;

int main() {
float a = 1000; 
float b = 0.0001;
float c = pow((a+b) , 3);
float d = (pow(a, 3) + 3*pow(a,2) *b);
float e = (3* a * pow(b,2));
float f = pow(b,3);
float g = (3 * pow(a, 2) * b);
float res_f = (c - d) / (e + f + g);
/*
Cтворюєм величини за вказаним типом;
Обчислюєм значення виразу для float
*/
double a1 = 1000;
double b1 = 0.0001;
double c1 = pow( (a1+b1) , 3);
double d1= pow(a1, 3) + 3*pow(a1,2) *b1;
double e1 = 3* a1 * pow(b1,2);
double f1= pow(b1,3);
double g1 = 3 * pow(a1, 2) * b1;
double res_d = (c1 - d1) / (e1 + f1 + g1);
/*
Cтворюєм величини за вказаним типом;
Обчислюєм значення виразу для double 
*/
cout << "Float:"  << res_f << endl;
cout << "Double:" << res_d<< endl;
    return 0; 
}