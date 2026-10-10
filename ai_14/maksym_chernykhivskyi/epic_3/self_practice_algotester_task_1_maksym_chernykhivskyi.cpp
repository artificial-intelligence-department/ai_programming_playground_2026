/*Epic 3 - Bunny and Netbook
Чернихівський Максим
Ші - 14*/

#include <iostream>

using namespace std;

int main(){
    long long n;
    cin >> n;
    
    int bits = 0;
    
    while(n > 0){
        bits++;
        n /= 2; // Зсув праворуч на 1 біт
    }
    
    cout << bits;
    return 0;
}