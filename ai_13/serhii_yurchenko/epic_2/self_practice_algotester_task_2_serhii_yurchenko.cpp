#include <iostream>
using namespace std;
int main() {
    long long l, r;
    cin >> l >> r;
    if (l == r) { cout << 0; return 0; }
    long long x = l ^ r;
    long long ans = 1;
    while (x > 0) { ans <<= 1; x >>= 1; }
    cout << ans - 1;
}