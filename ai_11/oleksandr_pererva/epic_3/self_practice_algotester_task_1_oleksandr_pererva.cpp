/*
Підрахунок голосів
Перерва Олександр
ШІ-11
*/
#include <iostream>

using namespace std;

int main(){
    int n,m,count=0;
    const int maxA=100000;
    long long k,l;
    long long a[maxA];
    cin>>n>>m>>k;

    for(int i=0;i<m;i++){
        cin>>a[i];
    }
    l=k;
    for(int i=0;i<m;i++){
        if(l>=a[i]){
            l-=a[i];
        }
        else{
            count++;
            l=k;
            i--;
        }
        if(count>n){
         cout<<"-1";
         return 0;
     }
     if(i>=m-1) count++;
    }
    cout<<n-count;
}