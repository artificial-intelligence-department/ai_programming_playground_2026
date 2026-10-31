
/* 
Епік 3. self practice: Algotester, задача "Найбільша зростаюча підпослідовність"
Авторка: Влада Ташогло
Група: ші-11
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int* a = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int* dp = new int[n];

    for (int i = 0; i < n; i++) {
        dp[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
            }
        }
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
        if (dp[i] > ans) {
            ans = dp[i];
        }
    }

    cout << ans << endl;

    delete[] a;
    delete[] dp;

    return 0;
}