/*
Назва задачі: Вболівальниці
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n,k,z,a[12],qunt=0;
    cin>>n>>k>>z;
    for(int i=0;i<n;i++)
    cin>>a[i];
    sort(a,a+n);
    for(int i=0;i<n;i++)
    {
        if(a[i]*2>z){cout<<qunt;return 0;}
         else 
         {
            qunt++;
            z=z-a[i]*2;
         }
    }
    cout<<qunt;

}