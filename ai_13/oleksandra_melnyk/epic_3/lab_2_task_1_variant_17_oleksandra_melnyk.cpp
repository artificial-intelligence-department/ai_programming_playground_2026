/*
Lab_2_task_1
Мельник Олександра ШІ-13 варіант 17
*/
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
/*
Знайти суму ряду з точністю ε=0.0001, загальний член якого
an=10^(-n)(n-1)!
*/
double factorial()
{
    double ε=0.0001;
    double a=0.1;
    int n=1;
    double sum=0.0;
    while(a>=ε)
    {
        sum+=a;
        a=a*(n/10.0);
        n++;
    }
    return sum;
}
int main()
{
    cout<<"Сума ряду дорівнює: "<<factorial();
}