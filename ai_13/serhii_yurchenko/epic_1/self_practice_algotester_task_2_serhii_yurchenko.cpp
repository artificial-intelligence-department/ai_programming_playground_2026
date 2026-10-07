#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        if (a > 0) ans += a - 1;
    }
    cout << ans << "\n";
    return 0;
}