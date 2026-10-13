/*  Algotester self practice
    "Куди бігти?"
    Ярошик Наталія
    ШІ-14
*/
#include <iostream>
using namespace std;

int main(){
    long long d, u, v;
    cin >> d >> u >> v;
    if(d < 4*u){
        cout << "Down";
    }else if(d > 4*u){
        cout << "Up";
    }else{
        cout << "Never mind";
    }
    return 0;
}