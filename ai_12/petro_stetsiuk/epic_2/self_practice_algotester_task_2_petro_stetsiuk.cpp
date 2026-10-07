/*
    Задача: Вогняне дихання
    Автор: Стецюк Петро
    Група: ШІ-12
*/
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

int main()
{
    int x,y,n,k,i=0,x1,y1;
    double a[101];
    cin>>x>>y>>n>>k;
    for(i=0;i<n;i++)
    {
        cin>>x1>>y1;
        a[i]=sqrt(pow(x-x1,2)+pow(y-y1,2));
    }
    sort(a,a+n);
    cout<<fixed<<setprecision(8)<<a[k-1];
}