#include <iostream>
using namespace std;

int main() {
    long long n, m, k;
    cin >> n >> m >> k;

    long long groups = 1, cur = 0;
    for (int i = 0; i < m; i++) {
        long long a;
        cin >> a;
        if (cur + a > k) {   
            groups++;
            cur = 0;
        }
        cur += a;
    }

    if (groups > n) cout << -1;
    else cout << n - groups;
    return 0;
}