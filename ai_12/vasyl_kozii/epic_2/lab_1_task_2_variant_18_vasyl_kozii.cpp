#include <iostream>
using namespace std;
int main()
{
    int n;
    cin >>n;
    int m;
    cin >>m;
    int s1=n++*m;
    bool s2=n++<m;
    bool s3=m-->m;
    cout <<s1 <<endl;
    cout <<s2 <<endl;
    cout <<s3 <<endl;
}