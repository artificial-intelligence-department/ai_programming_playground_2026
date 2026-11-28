/*
Algotester Task 5 Variant 2
Козій Василь Іванович
група: ШІ-12
*/
#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n, m;
    cin >>n >>m;
    string cave[n];
    for(int i=0; i<n; i++)
    {
        cin >>cave[i];
    }
    int q=0;
    do
    {
        q=0;
        for(int i=n-2; i>=0; i--)
        {
            for(int j=0; j<m; j++)
            {
                if(cave[i][j]=='S' && cave[i+1][j]=='O')
                {
                    cave[i][j]='O';
                    cave[i+1][j]='S';
                    q++;
                }
            }
        }   
    } while(q!=0);
    for(int i=0; i<n; i++)
    {
        cout <<cave[i] <<endl;
    }
}