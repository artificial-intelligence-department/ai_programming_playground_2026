#include <iostream>
using namespace std;
int main()
{
    int a, b, c;
    cin >>a;
    cin >>b;
    cin >>c;
    if((a+b)<=47 || (a+c)<=47 || (b+c)<=47)
    {
        cout <<"YES";
    }
    else
    {
        cout <<"NO";
    }
}