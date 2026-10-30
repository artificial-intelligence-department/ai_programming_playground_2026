#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    int k;
    cin >> k;
    vector<int> jumps(k);
    for (int i = 0; i < k; i++) {
        cin >> jumps[i];
    }

    int m;
    cin >> m;
    vector<bool> crater(n, false);
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        crater[x] = true;
    }

    vector<int> dp(n, -1);


    dp[0] = 0;

    for (int i = 1; i < n; i++) {
        if (crater[i]) continue;

        for (int d : jumps) {
            if (d <= i && dp[i - d] != -1) {
                int cand = dp[i - d] + 1;
                if (dp[i] == -1 || cand < dp[i]) {
                    dp[i] = cand;
                }
            }
        }
    }
    cout << dp[n - 1] << endl;

    return 0;
}
