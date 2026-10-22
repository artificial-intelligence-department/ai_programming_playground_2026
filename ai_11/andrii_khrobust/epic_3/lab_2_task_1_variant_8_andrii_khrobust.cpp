/*
Задача: Лабораторна №2 варіант 8
Автор: Хробуст Андрій
Група ШІ-11 
*/
#include <iostream>

using namespace std;
int main(){
    double a=0.5;
    double e= 0.0001;
    double sum= a;
    int n=1;
        while(a>=e){
        a=a*(2*n+1)/(2*(2*n-1));
        sum+=a;
        n++;
    }
    cout<< sum;
    return 0;
}