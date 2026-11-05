/*
Lab 2v1
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <iostream>
#include <algorithm>
using namespace std;
 
int main() 
{
    int n,a[100001],i;
    cin>>n;
    for(i=0;i<n;i++)
    {
        cin>>a[i];
    }
    sort(a,a+n);
    if(n==1||n==2){cout<<0;return 0;}
    if(a[0]==a[1])cout<<a[n-2]-a[0];
        else if(a[n-1]==a[n-2])cout<<a[n-1]-a[1];
            else if(a[n-1]-a[1]>a[n-2]-a[0])cout<<a[n-2]-a[0];
                 else cout<<a[n-1]-a[1];
}