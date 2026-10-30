#include <iostream>

using namespace std;

long long zero(int n){
    if(n < 5) return 0;
    return n/5 + zero(n/5);
}

int main(){
    long long n;
    cin >> n;
    cout << zero(n);
    return 0;
}