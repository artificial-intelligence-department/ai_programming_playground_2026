/*
    Задача: Коля, Вася і Теніс
    Автор: Стецюк Петро
    Група: ШІ-12
*/
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main()
{
    int ssize,k=0,v=0,dif,kres=0,vres=0;
    string s;
    cin>>ssize>>s;
    for(int i=0;i<=ssize;i++)
    {
        dif=abs(k-v);
        if(k>v&&dif>=2&&k>=11){kres++;k=0;v=0;}
         else if(v>k&&dif>=2&&v>=11){vres++;k=0;v=0;}
        if(s[i]=='K'&&i!=ssize)k++;
            else if(s[i]=='V'&&i!=ssize)v++;
    }
    cout<<kres<<":"<<vres<<endl;
    if(k!=0||v!=0){cout<<k<<":"<<v;}
    return 0;
}