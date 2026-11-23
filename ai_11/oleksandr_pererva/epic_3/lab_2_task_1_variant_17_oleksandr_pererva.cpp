/*
Lab 2 task 1
Перерва Олександр
ШІ-11
*/
#include <iostream>
#include <cmath>

using namespace std;

int main(){
    const double e=0.0001;
    double a,sum=0, n=1;
    a=pow(10,-n);
    while(a>=e){
        sum+=a;
        a=a*n/10;
        n++;
    }
    cout<<"Cума ряду: "<<sum<<endl;


}