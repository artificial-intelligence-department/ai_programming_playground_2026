#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int dp[305][305];

int main() {
    string s;
    cin >> s;

    
    string t = "";
    for (int i = 0; i < (int)s.size(); i++) {
        if (i == 0 || s[i] != s[i - 1]) {      // якщо символ перший або != попередньому
            t += s[i];                         // тобто стискаєм всі однакові підряд в одну цифру
        }
    }

    int n = t.size();    // довжина стиснутого рядка
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = 1;          // відрізок з 1 цифри за 1 хід
        for (int j = i + 1; j < n; j++) {
            dp[i][j] = dp[i + 1][j] + 1;        // викреслюєм t[i] за 1 хід   
                                                //dp[i][j] - мінімальна кількість ходів щоб повністю викреслити t[i...j]
            for (int k = i + 1; k <= j; k++) {
                if (t[k] == t[i]) {             // перебираєм всі позиції де к така ж як і
                    int mid = (k - 1 >= i + 1) ? dp[i + 1][k - 1] : 0;         // цінаа викреслення всьго між і та к
                    dp[i][j] = min(dp[i][j], mid + dp[k][j]);
                }
            }
        }
    }

    cout << dp[0][n - 1] << endl;
    return 0;
}