/*
Перехід дороги
Перерва Олександр
ШІ-11
*/
#include <iostream>

using namespace std;

int main(){
    int n,perehid=0;
    long long ai1,ai2;
    cin>>n;
    cin>>ai1;
    for(int i=1;i<n;i++){
        cin>>ai2;
        if(ai1%2 != ai2%2){
            perehid++;
        }
        ai1=ai2;
    }
    cout<<perehid;

    return 0;
}