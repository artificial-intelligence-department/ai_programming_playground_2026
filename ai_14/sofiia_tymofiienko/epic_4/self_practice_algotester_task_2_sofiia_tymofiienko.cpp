#include <iostream>
using namespace std;
int main(){
    bool seen[101]={false};
int n;
cin>>n;
int* a= new int[n];
int count=0;
for (int i=0; i<n; i++){
cin>>a[i];

if (!seen[a[i]]){
    count++;
    seen[a[i]]=true;
}
}
cout<<count<<endl;
delete[] a;
    return 0;
}
