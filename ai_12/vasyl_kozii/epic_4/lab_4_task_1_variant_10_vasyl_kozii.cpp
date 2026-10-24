#include <iostream>
using namespace std;
int main()
{
    int x1[]={10, 18, 5, 15, 13, 1, 4, 6, 8, 9};
    for(int i=0; i<10; i++)
    {
        cout <<x1[i] <<" ";
    }
    cout <<endl;
    int x2[5];
    for(int i=5; i<10; i++)
    {
        x2[i-5]=x1[i];
    }
    int x3[8];
    for(int i=0; i<5; i++)
    {
        x3[i]=x2[i];
    }
    cout <<"Будь ласка, введіть 3 елементи, які додати в масив: ";
    int x;
    for(int i=0; i<3; i++)
    {
        if(cin >>x)
        {
            x3[i+5]=x;
        }
        else
        {
            cout <<"Будь ласка, введіть число" <<endl;
        }
    }
    for(int i=0; i<8; i++)
    {
        cout <<x3[i] <<" ";
    }
}