/*
Self Practice Algotester Task 3
група ШІ-12
Козій Василь Іванович
*/
#include <iostream>
using namespace std;
int NSD(int x, int y)
{
    if(x==0 || y==0)
    {
        return max(x, y);
    }
    return NSD(max(x, y)%min(x, y), min(x, y));
}
int main()
{
    int n;
    cin >>n;
    int* x = new int[n];
    for(int i=0; i<n; i++)
    {
        cin >>x[i];
    }
    int N=x[0];
    for(int i=1; i<n; i++)
    {
        N=NSD(N, x[i]);
    }
    long long sum=0;
    for(int i=0; i<n; i++)
    {
        sum+=(x[i]/N);
    }
    cout <<sum;
}