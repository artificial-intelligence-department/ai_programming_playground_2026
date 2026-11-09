#include <iostream>
using namespace std;



int check(long long x2, long long x1, long long target_xn, long long a, long long b, long long c, int n) {
    long long prev2 = x1;
    long long prev1 = x2;

    for (int i = 3; i <= n; ++i) {
        long long curr = a * prev1 + b * prev2 + c;
        prev2 = prev1;
        prev1 = curr;
    }

    if (prev1 < target_xn) return -1;
    if (prev1 > target_xn) return 1;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long a, b, c;
    int n;
    long long x1, xn;

    if (!(cin >> a >> b >> c >> n >> x1 >> xn)) return 0;

    if (n == 2) {
        cout << xn << "\n";
        return 0;
    }

    long long low = -1000000ll, high = 1000000ll;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        int res = check(mid, x1, xn, a, b, c, n);

        if (res == 0) {
            cout << mid << "\n";
            return 0;
        } else if (res < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return 0;
}