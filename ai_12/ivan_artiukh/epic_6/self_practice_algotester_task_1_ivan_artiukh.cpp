#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    long long x, n, k;
    cin >> x >> n >> k;

    string ans;
    ans.reserve(n + k + 10);
    long long carry = 0;

    for (long long p = 0; p <= n + k - 2; p++) {
        long long L = max(0LL, p - n + 1);
        long long R = min(k - 1, p);
        long long cnt = R - L + 1;

        long long sum = cnt * x + carry;
        ans.push_back(char('0' + (sum % 10)));
        carry = sum / 10;
    }

    while (carry > 0) {
        ans.push_back(char('0' + (carry % 10)));
        carry /= 10;
    }

    reverse(ans.begin(), ans.end());
    cout << ans << '\n';
    return 0;
}