/*
Назва задачі: Назва для покемона
Автор: Петро Стецюк
Група: ШІ-12
*/
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s1,s2;
    cin>>s1>>s2;
    bool flag=0;
    if(s1.size()<s2.size()){cout<<"NO";return 0;}
    for(int i=0;i<s1.size();i++)
    {
        if(s1[i]=='?'||s1[i]==s2[0])
        {
            for(int j=1;j<s2.size();j++)
            {
                if(i+j>=s1.size()){cout<<"NO";return 0;}
                 else if(s1[i+j]==s2[j]&&j==s2.size()-1){cout<<"YES";return 0;}
                    else if(s1[i+j]=='?'&&j==s2.size()-1){cout<<"YES";return 0;}
                        else if(s1[i+j]==s2[j]||s1[i+j]=='?');
                            else if(s1[i+j]!=s2[j]||s1[i+j]!='?')break;
            }
        }
    }
    cout<<"NO";
}