#include <iostream>
using namespace std;
int main(){
int n;
cin>>n;
int *r=new int[n]; 
for (int i=0; i<n; i++){
cin>>r[i];
}
int m;
cin>>m;
int *arr=new int [m];
for (int j=0; j<m; j++){
    cin>>arr[j];
}
int count=0;
for (int i=0; i<n; i++){
    for (int j=0; j<m; j++){
        if (r[i]==arr[j]){
            count++;
            break;
        }
    }
}
int total=n+m-count;
cout<<count<<endl;
cout<<total<<endl;
delete[]r;
delete []arr;
    return 0;
}
