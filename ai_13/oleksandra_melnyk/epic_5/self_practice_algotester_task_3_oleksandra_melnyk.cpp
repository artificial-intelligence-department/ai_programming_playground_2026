#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s;
    int k=0;
    cin>>s;
    for (int i=0; i<s.length(); i++)
    {
        if (s[i]==s[i+1])
        {
            k++;
        }
    }
    cout<<k;
}
