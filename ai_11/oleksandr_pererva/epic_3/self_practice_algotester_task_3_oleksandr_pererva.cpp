/*
Максимум
Перерва Олександр
ШІ-11
*/
#include <iostream>

using namespace std;

int findMax(int a[],int n){
    int max_a=a[0];
    for(int i=0;i<n;i++){
        if(a[i]>max_a) max_a=a[i];
    }
    return max_a;
}
int main(){
    int n;
    const int max_n=1000;
    int a[max_n];
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    cout<<findMax(a,n);
}