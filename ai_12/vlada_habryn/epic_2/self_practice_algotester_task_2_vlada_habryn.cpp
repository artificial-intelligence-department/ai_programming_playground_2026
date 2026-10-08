#include <iostream>
using namespace std;
int main(){
    int a;
    int b;
    int c;
    cin>>a>>b>>c;
    if(b>= a+c)
    cout<<"All"<<endl;
    else if (b>=a)
    cout<<"All registered"<< endl;
    else 
    cout<<"Bad organizers"<<endl;
    return 0;
    
}