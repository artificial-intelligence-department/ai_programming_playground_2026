/*
* Задача: Найбільша зростаюча підпослідовність
* Поліщук Вероніка
* Група 14
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int a[105];
    int dp[105];

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int max_len = 1;

    for (int i = 0; i < n; ++i) {
        dp[i] = 1; // мінімальна довжина — 1 (сам елемент)
        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        max_len = max(max_len, dp[i]);
    }

    cout << max_len << "\n";

    return 0;
}