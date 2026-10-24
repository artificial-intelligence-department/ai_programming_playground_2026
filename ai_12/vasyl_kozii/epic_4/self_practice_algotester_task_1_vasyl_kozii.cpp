/*
Self Practice Algotester Task 1
група ШІ-12
Козій Василь Іванович
*/
#include <iostream>
using namespace std;
int main()
{
    int rows, cols;
    cin >>rows;
    cin >>cols;
    int** x = new int*[rows];
    for(int i=0; i<rows; i++)
    {
        x[i] = new int[cols]{};
    }
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            cin >>x[i][j];
        }
    }
    int* a = new int[cols];
    int m=0;
    for(int j=0; j<cols; j++)
    {
        m=0;
        for(int i=0; i<rows; i++)
        {
            if(x[i][j]>m){m=x[i][j];}
        }
        a[j]=m;
    }
    m=1001;
    for(int j=0; j<cols; j++)
    {
        if(a[j]<m){m=a[j];}
    }
    cout <<m;
}