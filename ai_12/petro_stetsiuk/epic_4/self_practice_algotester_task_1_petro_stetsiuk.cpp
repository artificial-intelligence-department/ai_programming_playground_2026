/*
Назва задачі: Халява
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <iostream>
#include <algorithm>
using namespace std;
int a[105];
int main()
{
    int n,qunt=0;
    cin>>n;
    for(int i=0;i<n;i++)
    cin>>a[i];
    sort(a,a+n);
    for(int i=0;i<n;i++)
    {
        if(a[i]!=a[i+1])qunt++;
    }
    cout<<qunt;
    
}