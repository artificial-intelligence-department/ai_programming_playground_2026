/*
Self Practice Algotester Task 3
група ШІ-12
Козій Василь Іванович
*/
#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int n;
    cin >>n;
    vector<int> v={};
    for(int i=1; i<=n; i++)
    {
        v.push_back(i);
    }
    int i=0;
    while(v.size()>1)
    {
        v[i]=0;
        i+=2;
        if(i>=v.size())
        {
            i=i%(v.size());
            erase(v, 0);
        }
        
    }
    cout <<v[0];
}