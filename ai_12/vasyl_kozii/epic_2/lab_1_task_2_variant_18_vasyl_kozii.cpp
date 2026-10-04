#include <iostream>
using namespace std;
int main()
{
    int n;
    cout <<"Перше число: ";
    cin >>n;
    int m;
    cout <<"Друге число: ";
    cin >>m;
    int s1=n++*m;
    n--;
    bool s2=n++<m;
    n--;
    bool s3=m-->m;
    cout <<"n++*m: " <<s1 <<endl;
    cout <<"n++<m: " <<s2 <<endl;
    cout <<"m-->m: " <<s3 <<endl;
}