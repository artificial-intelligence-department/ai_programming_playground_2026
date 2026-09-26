#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<vector<int>> v={};
    int n;
    cin >>n;
    int number;
    for(int i=0; i<n; i++)
    {
        cin >>number;
        v.push_back({number, 0});
    }
    int len=v.size();
    int m=0;
    v[len-1][1]=1;
    for(int i=len-2; i>=0; i--)
    {
        m=0;
        for(int j=i+1; j<len; j++)
        {
            
            if(v[j][0]>v[i][0] && v[j][1]>m)
            {
                m=v[j][1];
            }
        }
        v[i][1]=m+1;
    }
    m=0;
    for(int i=0; i<len; i++)
    {
        if(v[i][1]>m)
        {
            m=v[i][1];
        }
    }
    cout <<m;
    return 0;
}