#include<iostream>
using namespace std;

int main(){
    int n,k;
    cin>>n;

    k=k+n/500;
    n=n-500*k;

    k=k+n/200;
    n=n-(200*(n/200));

    k=k+n/100;
    n=n-(100*(n/100));

    k=k+n/50;
    n=n-(50*(n/50));

    k=k+n/20;
    n=n-(20*(n/20));

    k=k+n/10;
    n=n-(10*(n/10));

    k=k+n/5;
    n=n-(5*(n/5));

    k=k+n/2;
    n=n-(2*(n/2));

    k=k+n;

    cout<<k<<endl;

}
