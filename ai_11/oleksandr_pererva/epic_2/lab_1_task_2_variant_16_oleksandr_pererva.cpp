/*
Lab 1 task 2
Перерва Олександр
ШІ-11
*/
#include <iostream>

using namespace std;

int main(){
    int n,m;
    cout<<"Введіть n та m: "<<endl;
    cin>>n;
    cin>>m;
    // 1)
    int n1=n,m1=m;
    int res1=++n1*++m1;
    cout<<"1) "<<res1<<endl;
    // 2)
    int n2=n,m2=m;
    bool res2=m2++<n2;
    if(res2) cout<<"2) true"<<endl;
    else cout<<"2) false"<<endl;
    // 3)
    int n3=n,m3=m;
    bool res3=n3++>m3;
    if(res3) cout<<"3) true"<<endl;
    else cout<<"3) false"<<endl;

    return 0;
}