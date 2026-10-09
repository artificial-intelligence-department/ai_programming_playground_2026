#include <iostream>

using namespace std;
int main(){
    long long int a, b, avrg;
    cin>>a>>b;
    if (a==b || a == b+1 || b == a+1){
        cout<<"-1"<<endl;
    }else{
        avrg =(a+b)/2;
        cout<<avrg<<endl;
    }
    
    return 0;
}