/*
Lab 3 Task 1 Variant 8
група ШІ-12
Козій Василь Іванович
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double const pi=3.14159265359;
double const a=0.1;
double const b=0.8;
int const k=10;
int const n=40;
double const epselon=0.0001;
double y(double x)
{
    return (x*sin(pi/4))/(1-2*x*cos(pi/4)+pow(x, 2));
}
int main()
{
    double x;
    double A;
    double sum1;
    double sum2;
    int j=2;
    for(int i=0; i<=k; i++)
    {
        x=a+((b-a)/k)*i;
        A=x*sin(pi/4);
        sum1=A;
        sum2=A;
        for(int j=2; j<=n; j++)
        {
            A=A*(x*sin(j*(pi/4)))/sin((j-1)*(pi/4));
            sum1+=A;
        }
        A=x*sin(pi/4);
        j=2;
        while(abs(A)>epselon || abs(A*(x*sin(j*(pi/4)))/sin((j-1)*(pi/4)))>epselon)
        {
            A=A*(x*sin(j*(pi/4)))/sin((j-1)*(pi/4));
            sum2+=A;
            j++;
        }
        cout <<left;
        cout <<"X=" <<setw(8) <<x <<"  ";
        cout <<"SN=" <<setw(15) <<sum1 <<"  ";
        cout <<"SE=" <<setw(15) <<sum2 <<"  ";
        cout <<"Y=" <<setw(8) <<y(x) <<"  ";
        cout <<endl;
    }
}