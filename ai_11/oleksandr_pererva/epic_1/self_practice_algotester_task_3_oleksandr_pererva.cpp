/*
Депутатські гроші
Перерва Олександр
ШІ-11
*/
#include <iostream>

using namespace std;

int main() {
    int n;
    cin>>n;

    int m = 0;

    m+=n/500; n%=500;
    m+=n/200; n%=200;
    m+=n/100; n%=100;
    m+=n/50;  n%=50;
    m+=n/20;  n%=20;
    m+=n/10;  n%=10;
    m+=n/5;   n%=5;
    m+=n/2;   n%=2;
    m+=n;       

    cout << m << endl;
    return 0;
}