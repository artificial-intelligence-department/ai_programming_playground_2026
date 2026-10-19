/*
Завдання: Найбільша зростаюча підпослідовність
*/
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int a[100];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int dp[100];
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    int ans = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (dp[i] > ans) {
            ans = dp[i];
        }
    }

    cout << ans << endl;

    return 0;
}