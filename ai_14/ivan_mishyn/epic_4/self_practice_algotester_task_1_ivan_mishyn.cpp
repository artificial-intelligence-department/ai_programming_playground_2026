#include <iostream>
using namespace std;


int main(){
    int n;
    cin>>n;
    int* k=new int[n];
    int sum2=0;
    for(int i=0;i<n;i++){
        cin>>k[i];
        sum2+=k[i];
    }
    int sum1=0;
    bool isTak=false;
    for(int i=0;i<n;i++){
        sum1+=k[i];
        sum2-=k[i];
        if(sum1==sum2){
            isTak=true;
        }
        if(sum1>sum2){
            break;
        }
    }
    cout<<((isTak)?"TAK":"NI");
    delete[] k;
    k=nullptr;
    return 0;
}