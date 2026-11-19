//Снігурочка
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    string s;
    int answer=0;
    bool polindrom;
    while(cin>>s)
    {
        int n=s.size();
        polindrom=true;
        for(int i=0;i<n/2;i++)
        {
            if(tolower(s[i])!=tolower(s[n-1-i])){polindrom=false;break;}
        }
        if(polindrom)answer++;
    }
    cout<<answer;

}