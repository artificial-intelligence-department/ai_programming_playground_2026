#include <iostream>

using namespace std;

int main(){

int a, b, c;
cin>>a>>b>>c;

int arr[]={a, b, c};
if (arr[0]+arr[1]>arr[2]){
cout<<"YES"<<endl;
}else{
    cout<<"NO"<<endl;
}
    return 0;
}
