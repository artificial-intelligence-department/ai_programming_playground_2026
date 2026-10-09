#include <iostream>
using namespace std;

int main(){
    
    int x, y, z, res;
    cin>>x>>y>>z;
    if(x-y>z){
        cout<<"-1";
    }else if(x-y==z){
        res = x-y;
        cout<<res;
    }else if (x+y<=z){
        res = x+y;
        cout<<res;
    }else if(x+y>z || x-y<=z){
        res=z;
        cout<<res;
    }else{
        cout<<"-1";
    }
    
    return 0;
}