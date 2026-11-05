/*
Назва задачі: Робот
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    int x,y,xR=0,yU=0,i;
    cin>>s;
    cin>>x>>y;
    for(i=0;i<s.size();i++)
    {
        if(s[i]=='R')xR++;
         else yU++;
    }
    if(xR>=x&&yU>=y)cout<<"YES";
     else cout<<"NO";
}