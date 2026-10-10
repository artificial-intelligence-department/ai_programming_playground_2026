/*
<Белаш Матвій ШІ-12
Завдання з алготестеру "Депутатські гроші"
*/
#include <iostream>

int main(){

    int c = 0;
    std::cin >> c;
    int k = 0;
    int p;

   
    if(c >= 500){
        p = c / 500;
        c -= 500 * p;
        k += p;
    }
    if(c >= 200){
        p = c / 200;
        c -= 200 * p;
        k += p;
    }
    if(c >= 100){
        p = c / 100;
        c -= 100 * p;
        k += p;
    }
    if(c >= 50){
        p = c / 50;
        c -= 50 * p;
        k += p;
    }
    if(c >= 20){
        p = c / 20;
        c -= 20 * p;
        k += p;
    }
    if(c >= 10){
        p = c / 10;
        c -= 10 * p;
        k += p;
    }
    if(c >= 5){
        p = c / 5;
        c -= 5 * p;
        k += p;
    }
    if(c >= 2){
        p = c / 2;
        c -= 2 * p;
        k += p;
    }
    if(c == 1){
        k ++;
    }
    
    std::cout << k;
    return 0;
    
}