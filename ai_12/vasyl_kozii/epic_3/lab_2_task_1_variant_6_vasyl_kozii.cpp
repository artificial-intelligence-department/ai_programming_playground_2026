/*
Lab 2 Task 1 Variant 6
група ШІ-12
Козій Василь Іванович
*/
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    double a1_1=1;
    double a1_2=1;
    a1_1=a1_1/2;
    a1_2=a1_2/3;
    double a=a1_1+a1_2;
    double sum=a;
    double const epselon=0.0001;
    while(a>epselon)
    {
        a1_1=a1_1/2;
        a1_2=a1_2/3;
        a=a1_1+a1_2;
        sum+=a;
    }
    cout <<sum;
}