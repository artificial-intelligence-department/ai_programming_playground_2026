//Алфавітна послідовність
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    int n,answer=1,qunt=1;
    cin>>n>>s;
    for(int i=1;i<n;i++)
    {
        if(s[i]>s[i-1])
        {
            qunt++;
            if(qunt>answer)answer=qunt;
        }
        else qunt=1;
    }
    cout<<answer;

}