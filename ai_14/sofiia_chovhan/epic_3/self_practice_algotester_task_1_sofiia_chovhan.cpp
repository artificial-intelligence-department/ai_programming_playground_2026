/* Sofiia Chovhan AI 14
Longest Increasing Subsequence*/

#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int a[100], dp[100];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dp[i] = 1;
    }

    int longest = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
        }

        if (dp[i] > longest) {
            longest = dp[i];
        }
    }

    cout << longest << endl;

    return 0;
}