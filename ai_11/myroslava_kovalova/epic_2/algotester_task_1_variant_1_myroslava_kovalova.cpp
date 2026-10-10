/* Lab 1v1
Ковальова Мирослава
ШІ-11*/

#include <iostream>

using namespace std;

int main(){
    long long H, M, h1, h2, h3, m1, m2, m3;
    bool req1 = 1;
    bool req2 = 1;
    bool req3 = 1;
    
    cin>>H>>M>>h1>>m1>>h2>>m2>>h3>>m3;
    
    if(h1>0 && m1>0){
        req1=0;
    }
    if(h2>0 && m2>0){
        req2=0;
    }
    if(h3>0 && m3>0){
        req3=0;
    }
    H=H-h1-h2-h3;
    M=M-m1-m2-m3;
    if (H>0 && M>0 && req1 && req2 && req3){
        cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
    }

    return 0;
}