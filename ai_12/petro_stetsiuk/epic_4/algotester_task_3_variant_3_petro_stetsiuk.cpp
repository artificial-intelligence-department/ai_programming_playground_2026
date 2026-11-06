/*
Lab 3v3
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <iostream>
#include <string>
using namespace std;
 
int main()
{
   string s,c="";
   cin>>s;
   int i,qunt=1;
   for(i=0;i<s.size();i++)
   {
    if(s[i]==s[i+1])qunt++;
     else if(s[i]!=s[i+1])
     {
        if(qunt==1) c=c+s[i];
        else c=c+s[i]+to_string(qunt);
        qunt=1;
    }
     
   }
   cout<<c;
}