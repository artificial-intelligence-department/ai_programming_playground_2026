#include <iostream>
using namespace std;

long long gcd(long long x, long long y) {
    while (y != 0) {
        long long t = x % y;  
        x = y;
        y = t;
    }
    return x;
}

int main() {
    long long n, m, k;
    cin >> n >> m >> k;       

    long long a = gcd(k, n);  
    long long b = k / a;      

    if (m % b == 0) {         
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}