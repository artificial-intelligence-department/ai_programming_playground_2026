//#2594 - Знову шахи..

#include <bits/stdc++.h>

using namespace std;

#define all(X) (X).begin(), (X).end()
#define pb(X) push_back((X))

constexpr int MOD = 1e9+7;

void zBogom(){
    int n, m; cin >> n >> m;
    vector<string> matr(n);
    vector<vector<int>> dp(n, vector<int>(m, 0));
    dp[0][0] = 1;
    for (auto& el:matr) cin >> el;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i + 1 < n && j + 2 < m && matr[i+1][j+2] != '#') {
                dp[i+1][j+2] += dp[i][j];
                dp[i+1][j+2] %= MOD;
            }
            if (i + 2 < n && j + 1 < m && matr[i+2][j+1] != '#') {
                dp[i+2][j+1] += dp[i][j];
                dp[i+2][j+1] %= MOD;
            }
        }
    }
    cout << dp[n-1][m-1] % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t; t = 1;
    while(t--){
        zBogom();
        cout << "\n";
    }
    return 0;
}



