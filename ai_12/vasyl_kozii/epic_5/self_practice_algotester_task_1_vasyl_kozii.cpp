/*
Self Practice Algotester Task 1
Козій Василь Іванович
група: ШІ-12
*/
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s;
    cin >>s;
    int n=s.size();
    string first="";
    string second="";
    for(int i=0; i<n; i++)
    {
        if(i%2==0)
        {
            first+="B";
            second+="Y";
        }
        else
        {
            first+="Y";
            second+="B";
        }
    }
    int F=0;
    int S=0;
    for(int i=0; i<n; i++)
    {
        if(s[i]!=first[i])
        {
            F++;
        }
        if(s[i]!=second[i])
        {
            S++;
        }
    }
    if(S>F)
    {
        cout <<F;
    }
    else
    {
        cout <<S;
    }
}