/*
Algotester Task 2 Variant 2
група ШІ-12
Козій Василь Іванович
*/
#include <iostream>
using namespace std;
int main()
{
    int N, a, b, c;
    cin >>N;
    int* r = new int[N];
    for(int i=0; i<N; i++)
    {
        cin >>r[i];
    }
    cin >>a >>b >>c;
    int N_new=0;
    for(int i=0; i<N; i++)
    {
        if(r[i]!=a && r[i]!=b && r[i]!=c)
        {
            N_new++;
        }
    }
    int* r_new = new int[N_new];
    if(N_new==0 || N_new==1)
    {
        cout <<"0";
        return 0;
    }
    int j=0;
    for(int i=0; i<N; i++)
    {
        if(r[i]!=a && r[i]!=b && r[i]!=c)
        {
            r_new[j]=r[i];
            j++;
        }
    }
    cout <<(N_new-1) <<endl;
    for(int i=0; i<N_new-2; i++)
    {
        cout <<(r_new[i]+r_new[i+1]) <<" ";
    }
    cout <<(r_new[N_new-2]+r_new[N_new-1]);
    delete[] r;
    delete[] r_new;
}