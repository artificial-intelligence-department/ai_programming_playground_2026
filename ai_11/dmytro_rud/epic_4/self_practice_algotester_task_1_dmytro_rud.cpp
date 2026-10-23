#include <iostream>

using namespace std;

int main() {
    int n;
    int arr[100];
    int dp[100];

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        dp[i] = 1;
    }

    int answer = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j]) {
                if (dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                }
            }
        }

        if (dp[i] > answer) {
            answer = dp[i];
        }
    }

    cout << answer << "\n";

    return 0;
}

