/*
Self Practice Algotester Task 2
група ШІ-12
Козій Василь Іванович
*/
#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >>n;
    int* x = new int[n];
    int* y = new int[n];
    for(int i=0; i<n; i++)
    {
        cin >>x[i] >>y[i];
    }
    int max_x=0;
    int max_y=0;
    for(int i=0; i<n; i++)
    {
        if(x[i]>max_x)
        {
            max_x=x[i];
        }
        if(y[i]>max_y)
        {
            max_y=y[i];
        }
    }
    long long ans=0;
    for(int i=0; i<n; i++)
    {
        ans+=(max_x-x[i])+(max_y-y[i]);
    }
    cout <<ans;
    delete[] x;
    delete[] y;
}