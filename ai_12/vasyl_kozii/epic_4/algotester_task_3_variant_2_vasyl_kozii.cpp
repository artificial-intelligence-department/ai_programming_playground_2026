/*
Algotester Task 3 Variant 2
група ШІ-12
Козій Василь Іванович
*/
#include <iostream>
using namespace std;
int main()
{
    int N, M;
    cin >>N;
    int*n = new int[N];
    for(int i=0; i<N; i++)
    {
        cin >>n[i];
    }
    cin >>M;
    int*m = new int[M];
    for(int i=0; i<M; i++)
    {
        cin >>m[i];
    }
    int s=0;
    int q=0;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            if(n[i]==m[j])
            {
                s++;
                q=1;
                break;
            }
        }
        if(q==1)
        {
            q=0;
            continue;
        }
    }
    cout <<s <<endl;
    cout <<(N+M-s);
    delete[] n;
    delete[] m;
}