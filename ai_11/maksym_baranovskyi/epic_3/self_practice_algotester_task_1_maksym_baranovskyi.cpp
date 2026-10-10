//Літня школа

#include <iostream>

using namespace std;

int main(){

    int n, k;
    cin >> n >> k;
    
    int rem = n - k;

    int threes = rem / 2;
    int twos = rem % 2;
    int ones = k - threes - twos;

    if(n < k || n > 3 * k){
        cout << "Impossible";
        return 0;
    }

    for(int i = 0; i < threes; i++){
        cout << 3 << " ";
    }
    for(int i = 0; i < twos; i++){
        cout << 2 << " ";
    }
    for(int i = 0; i < ones; i++){
        cout << 1 << " ";
    } 
    

    return 0;
}
