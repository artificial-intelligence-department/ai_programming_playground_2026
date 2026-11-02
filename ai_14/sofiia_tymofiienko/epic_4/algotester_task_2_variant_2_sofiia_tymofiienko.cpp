#include <iostream>
using namespace std;
int main(){
int n;
cin>>n;
int *r=new int[n];
for (int i=0; i<n; i++){
    cin >> r[i];
}
int a, b, c;
cin>>a;
cin>>b;
cin>>c;
int newsize=0; 
int *arr= new int [n];
for (int i=0; i<n; i++){
    if (r[i] !=a && r[i] !=b && r[i] !=c){
        arr[newsize]=r[i];
                newsize++;
    }
}
    int m=newsize-1;
    if (m>0){
        for (int j=0; j<m; j++){
            arr[j]=arr[j]+arr[j+1];
        }
        cout<<m<<endl;
        for (int j=0; j<m; j++){
            cout<<arr[j]<<" ";
        }
        cout<<endl;
    }else{
        cout<<0<<endl;
    }
delete []r;
delete []arr;
    return 0;
}
