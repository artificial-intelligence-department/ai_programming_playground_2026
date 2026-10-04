#include <iostream>
using namespace std;

int main(){
    int n=0;
    int m=0;
    cout<<"Введіть n:";
    cin>>n;
    cout<<"Введіть m:";
    cin>>m;
    int a =n++*m;
    int b = n++<m;
    int c = m-->m;
    cout<<"n++*m "<<a<<endl;
    cout<<"n++<m "<<b<<endl;
    cout<<"m-- >m "<<c<<endl;
    return 0;
}