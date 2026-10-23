/*
Lab 1 task 1
Перерва Олександр
ШІ-11
*/
#include <iostream>
#include <math.h>

using namespace std;

int main(){
    //float
    float a1=1000,b1=0.0001,c1,d1,e1,f1,g1,h1,i1,j1;
    c1=pow((a1-b1),3);
    d1=pow(a1,3);
    e1=3*a1*a1*b1;
    f1=pow(b1,3);
    g1=3*a1*b1*b1;
    h1=c1-(d1-e1);
    i1=f1-g1;
    j1=h1/i1;
    cout<<"Float: "<<j1<<endl;

    //double
    double a2=1000,b2=0.0001,c2,d2,e2,f2,g2,h2,i2,j2;
    c2=pow((a2-b2),3);
    d2=pow(a2,3);
    e2=3*a2*a2*b2;
    f2=pow(b2,3);
    g2=3*a2*b2*b2;
    h2=c2-(d2-e2);
    i2=f2-g2;
    j2=h2/i2;
    cout<<"Double: "<<j2<<endl;

    return 0;
}