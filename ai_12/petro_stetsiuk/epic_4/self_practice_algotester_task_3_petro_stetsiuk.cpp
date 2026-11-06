/*
Назва задачі: Баскетболіст
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <iostream>

using namespace std;

int main()
{
    long long n,m,k,res=0;
    cin>>n>>m>>k;
    if(n==m||m<n){cout<<0;return 0;}
    else if(k==1){cout<<-1;return 0;}
    while(n<m)
    {
        n=n*k;
        res++;
    }
    cout<<res;

}