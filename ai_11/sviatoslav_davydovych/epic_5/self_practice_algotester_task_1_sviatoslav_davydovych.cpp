/* 
Умова: https://algotester.com/uk/ArchiveProblem/DisplayWithEditor/40192
Автор: Давидович Святослав
Група: ШІ-11
*/

#include <iostream>
#include <string>

int min(int a, int b){
    return (a<b) ? a : b;
}

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    int n = s.length();
    
    int **dp = new int*[n];

    for (int i = 0; i < n; i++){
        dp[i] = new int[n]{};
    }

    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            
            if (len == 1) {
                dp[i][j] = 1;
                continue;
            }

            dp[i][j] = dp[i + 1][j] + 1;

            if (s[i] == s[j]) {
                dp[i][j] = min(dp[i][j], dp[i + 1][j]);
            }

            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        }
    }

    cout << dp[0][n - 1];

    for (int i = 0; i<n; i++){
        delete dp[i];
    }
    delete[] dp;
    return 0;
}