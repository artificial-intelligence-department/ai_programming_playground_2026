/*
    Задача: Депутатські гроші
    Автор: Стецюк Петро
    Група: ШІ-12
*/
#include <iostream>

using namespace std;
int main()
{
    int n,k=0,i=1;
    cin>>n;
    while(i!=0)
    {
        if(n==0)i=0;
         else if(n>=500){k=n/500;n=n%500;}
          else if(n>=200){k=k+n/200;n=n%200;}
           else if(n>=100){k=k+n/100;n=n%100;}
            else if(n>=50){k=k+n/50;n=n%50;}
             else if(n>=20){k=k+n/20;n=n%20;}
              else if(n>=10){k=k+n/10;n=n%10;}
               else if(n>=5){k=k+n/5;n=n%5;}
                else if(n>=2){k=k+n/2;n=n%2;}
                 else if(n>=1){k=k+n/1;n=n%1;}
    }
    cout<<k<<endl;
    return 0;
}