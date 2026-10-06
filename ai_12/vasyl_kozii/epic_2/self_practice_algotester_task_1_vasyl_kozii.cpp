/*
Self Practice Algotester Task 1
група ШІ-12
Козій Василь Іванович
*/
#include <iostream>
#include <cmath>
using namespace std; 
int main()
{
    double a, b, c, R;
    cin>>a >>b >>c >>R;
    double p=0.5*(a+b+c);
    double R_in=pow((p-a)*(p-b)*(p-c)/p, 0.5);
    double R_out=a*b*c/(4*pow(p*(p-a)*(p-b)*(p-c), 0.5));
    if(R>=R_out)
    {
        cout <<"+";
    }
    else
    {
        cout <<"-";
    }

    if(R<=R_in)
    {
        cout <<"+";
    }
    else
    {
        cout <<"-";
    }
}