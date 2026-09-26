#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main()
{
    vector<int> v1={};
    vector<int> v2={};
    vector<int> v3={};
    int n;
    cin >>n;
    int number1, number2, number3;
    for(int i=0; i<n; i++)
    {
        cin >>number1;
        cin >>number2;
        cin >>number3;
        v1.push_back(number1);
        v2.push_back(number2);
        v3.push_back(number3);
    }
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    sort(v3.begin(), v3.end());
    int A=v1[(n/2)-1];
    int B=v2[(n/2)-1];
    int C=v3[(n/2)-1];
    int s1=0;
    int s2=0;
    int s3=0;
    for(int i=0; i<n; i++)
    {
        s1+=abs(v1[i]-A);
        s2+=abs(v2[i]-B);
        s3+=abs(v3[i]-C);
    }
    cout <<(s1+s2+s3);
}