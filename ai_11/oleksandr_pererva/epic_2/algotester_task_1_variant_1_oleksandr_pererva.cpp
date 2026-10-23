/*
Lab 1v1
Перерва Олександр
ШІ-11
*/
#include <iostream>

using namespace std;

int main(){
    long long H,M,hi,mi;
    bool win=true;
    cin>>H;
    cin>>M;
    for(int i=0;i<3;i++){
        cin>>hi;
        cin>>mi;
        if(hi>0 && mi>0){
            win=false;
        }
        H-=hi;
        M-=mi;
    }
    if(H<=0 || M<=0){
        win=false;
    }
    if(win) cout<<"YES"<<endl;
    else cout<<"NO"<<endl;


    return 0;
}