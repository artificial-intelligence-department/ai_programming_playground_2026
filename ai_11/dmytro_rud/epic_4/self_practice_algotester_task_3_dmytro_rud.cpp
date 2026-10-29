#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Довжина ділянки
    int n;
    cin >> n;

    // Дозволені довжини стрибків
    int k;
    cin >> k;
    vector<int> jumps(k);
    for (int i = 0; i < k; i++) {
        cin >> jumps[i];
    }

    // Кратери: crater[x] == true, якщо в точці x яма
    int m;
    cin >> m;
    vector<bool> crater(n, false);
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        crater[x] = true;
    }

    // dp[i] = мінімальна кількість стрибків до точки i, -1 якщо недосяжна
    vector<int> dp(n, -1);

    // 1. Базовий випадок (старт)
    dp[0] = 0;

    // 2. Головний цикл: i від 1 до n-1
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
    // 3. Виводимо відповідь
    cout << dp[n - 1] << endl;

    return 0;
}
