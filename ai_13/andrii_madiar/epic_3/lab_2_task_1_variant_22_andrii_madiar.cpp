/*
lab 2 task 1 variant 22, Мадяр Андрій, ШІ-13
*/
#include <iostream>
#include <cmath>
using namespace std;
double output(int n){//функція для знаходження n-го елемента
   double a;
   if(n <= 1){return 1;
   }else a = pow(n, log(n)) / pow(log(n), n);
   return a;
}
int main(){
    double sum = 0.0;
    for(int n = 2; n < 17; n++){//знаходження суми за допомогою циклу
     sum += output(n);
    }
    cout <<"Сума перших 15 дійсних елементів = " << sum <<endl;
    return 0;
}