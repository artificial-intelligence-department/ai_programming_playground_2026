#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<vector<int>> v1={};
    int n;
    cin >>n;
    int number;
    while(cin >>number)
    {
        v1.push_back({number, 0});
    }
    int len=v1.size();
    v1[len-1][1]=1;
    for(int i=len-2; i>=0; i--)
    {
        int m=0;
        for(int j=i+1; j<len; j++)
        {
            if(v1[j][1]>m && v1[j][0]>v1[i][0])
            {
                m=v1[j][1];
            }
        }
        v1[i][1]=m;
    }
    int m=0;
    for(int i=0; i<len; i++)
    {
        if(v1[i][1]>m)
        {
            m=v1[i][1];
        }
    }
    cout <<m;
}