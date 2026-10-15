#include <iostream>
using namespace std;

const int MOD = 1000000007;
const int L = 2520;

int dp[L], nw[L];

int main() {
    int n;
    cin >> n;

    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        a %= L;
        for (int r = 0; r < L; r++) {
            // або не беремо a (лишається dp[r]),
            // або беремо a (тоді раніше сума була r - a)
            nw[r] = (dp[r] + dp[(r - a + L) % L]) % MOD;
        }
        for (int r = 0; r < L; r++) dp[r] = nw[r];
    }

    // dp[0] враховує і порожню підмножину, тому віднімаємо 1
    cout << (dp[0] - 1 + MOD) % MOD;
    return 0;
}