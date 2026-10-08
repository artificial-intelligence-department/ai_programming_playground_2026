#include <iostream>
using namespace std;

int main(){
    long long a,b,sum;
    cin>>a>>b;
    if ((b-a)%12==0){
        sum = 13 * (a + b) / 2;
        cout<<sum;
    } else {
        cout<<"-1";
    }





    return 0;
}