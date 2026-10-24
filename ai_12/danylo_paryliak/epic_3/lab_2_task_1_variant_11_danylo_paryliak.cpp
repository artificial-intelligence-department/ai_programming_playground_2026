#include <iostream>
#include <cmath>
using namespace std;

int main(){

int n = 1; //Номер члена ряду
double a = 1.0; //Поточний член ряду
double sum = 0.0; //Сума членів
double eps = 0.0001; //Точність 0.0001

while(a >= eps) {
    sum+= a;
    a = a * pow((double) n/(n + 1),n);
    n++;
}
cout<<"Сума ряду: "<< sum<<endl;


    return 0;
}