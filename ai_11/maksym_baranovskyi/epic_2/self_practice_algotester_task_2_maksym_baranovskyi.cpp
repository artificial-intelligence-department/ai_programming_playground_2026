//Спекотні дні пінгвінів

#include <iostream>

using namespace std;

int main(){

    int l, w, u, d;

    cin >> l >> w >> u >> d;

    if(u+d >= l && w >= l){
        cout << "Three times Sex on the Beach, please!";
    }
    else{
        cout << "Forget about the cocktails, man!";
    }
    
    return 0;
}