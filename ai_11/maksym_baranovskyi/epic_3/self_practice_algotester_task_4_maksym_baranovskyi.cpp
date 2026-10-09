//Зайчик і нетбук

#include <iostream>

using namespace std;

int main(){
    long long n;
    cin >> n;
    
    long long bit = 0;
    long long num = 1;
    long long count = n + 1;
    while(num < count){
        bit ++;
        num *= 2;
        
    }
    cout << bit;
    
    return 0;
}
