#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int a[1000];
    int dp[1000];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dp[i] = 1;
    }

    int answer = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }

        if (dp[i] > answer)
            answer = dp[i];
    }

    cout << answer << endl;

    return 0;
}