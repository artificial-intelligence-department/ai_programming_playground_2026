/*
Self Practice Algotester Task 2
Козій Василь Іванович
група: ШІ-12
*/
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cctype>
using namespace std;
int dp[305][305];
inline int min_val(int a, int b) {
    return (a < b) ? a : b;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    if (!(cin >> s)) return 0;
    int n = s.length();
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = 1 + dp[i+1][j];
            for (int k = i + 1; k <= j; ++k) {
                if (s[i] == s[k]) {
                    dp[i][j] = min_val(dp[i][j], dp[i+1][k-1] + dp[k][j]);
                }
            }
        }
    }
    cout << dp[0][n-1] << "\n";
}