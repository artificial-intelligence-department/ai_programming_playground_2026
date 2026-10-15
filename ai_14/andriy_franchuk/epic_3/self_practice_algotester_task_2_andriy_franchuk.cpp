/*Epic 3 - Зайчик і нетбук
Франчук Андрій
Ші - 14*/

#include <iostream>

using namespace std;

int main(){
    long long n;
    cin >> n;
    
    int bits = 0;
    
    while(n > 0){
        bits++;
        n /= 2;
    }
    
    cout << bits;
    return 0;
}