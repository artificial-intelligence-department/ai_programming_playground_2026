/*
Лабораторна робота №3
Варіант: 24
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() 
{
    const double a=-2.0,b=-0.1;   // межі діапазону
    const double eps=0.0001;         // задана точність
    const int k=10;                  // кількість кроків
    const int N=40;                  // задане n
    double h=(b-a)/k;            // крок зміни x
    

    // зміна параметра x
    for (int i=0;i<=k;i++) 
    {
        double x=a+i*h;
        double t=(1+x)*(1+x);

        // сума для заданого n
        double SN=0.0;
        double c=1.0; 
        for (int n=1;n<=N;n++) 
        {
            c=c * -t;                   // c_n = c_(n-1)*(-t)
            SN=SN + c / n;  
        }

        // сума для заданої точності
        double SE=0.0;
        double an=1.0;       
        int n=1;
        c=1.0;               
        while (fabs(an)>=eps)
        {
            c= c * -t;
            an= c / n;
            SE= SE + an;
            n++;
        }

        // Точне значення функції
        double Y=log(1.0/(2+2*x+x*x));

        cout<<"X="<<x<<"  SN="<<SN<<"  SE="<<SE<< "  Y="<<Y<<endl;
    }
    return 0;
}