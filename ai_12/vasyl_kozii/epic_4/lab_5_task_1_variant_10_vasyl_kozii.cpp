/*
Lab 5 Task 1 Variant 10
група ШІ-12
Козій Василь Іванович
*/
#include <iostream>
using namespace std;
int negative_numbers(int** x, int row, int cols)
{
    int q=0;
    for(int j=0; j<cols; j++)
    {
        if(x[row][j]<0)
        {
            q=1;
            break;
        }
    }
    if(q==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void cout_matrix(int** x, int rows, int cols)
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            cout <<x[i][j] <<" ";
        }
        cout <<endl;
    }
}
int main()
{
    int rows, cols;
    cout <<"Висота: ";
    if(cin >>rows)
    {} else
    {
        cout <<"Будь ласка, тут ведіть ціле число" <<endl;
        return 1;
    }
    cout <<"Ширина: ";
    if(cin >>cols)
    {} else
    {
        cout <<"Будь ласка, тут ведіть ціле число" <<endl;
        return 1;
    }
    int** x = new int*[rows];
    for(int i=0; i<rows; i++)
    {
        x[i] = new int[cols]{};
    }
    int n;
    cout <<"Двовимірний масив: " <<endl;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(cin >>n){x[i][j]=n;}
            else
            {
                cout <<"Будь ласка, тут введіть матрицю чисел висотою " <<rows <<" і шириною " <<cols <<endl;
                return 1;
            }
        }
    }
    int q=0;
    int r=0;
    int** y = new int*[rows];
    for(int i=0; i<rows; i++)
    {
        y[i] = new int[cols]{};
    }
    for(int i=0; i<rows; i++)
    {
        if(negative_numbers(x, i, cols)==0)
        {
            y[r]=x[i];
            r++;
        }
        else
        {
            q++;
        }
    }
    for(int i=0; i<q; i++)
    {
        for(int j=0; j<cols; j++)
        {
            y[r][j]=0;
        }
        r++;
    }
    cout <<"Початковий масив: " <<endl;
    cout_matrix(x, rows, cols);
    cout <<"Масив після зміни: " <<endl;
    cout_matrix(y, rows, cols);
    for(int i=0; i<rows; i++)
    {
        delete[] x[i];
    }
    for(int i=0; i<rows; i++)
    {
        delete[] y[i];
    }
    delete[] x;
    delete[] y;
}