// Нігіляція рядка


#include <iostream>
#include <string>
using namespace std;

int dp[305][305];

int main() {
    string s;
    cin >> s;   
    int n = s.length();

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {

            // Варіант 1: цифру s[i] стираємо окремим ходом, далі розв'язуємо задачу для відрізка від i+1 до j
            dp[i][j] = 1 + dp[i + 1][j];

            // Варіант 2: шукаємо таку саму цифру s[k] правіше
            for (int k = i + 1; k <= j; k++) {
                if (s[k] == s[i]) {
                    // Спочатку стираємо все між s[i] і s[k], тоді вони стають сусідами й стираються разом
                    int var = dp[i + 1][k - 1] + dp[k][j];

                    // Якщо цей варіант кращий, запам'ятовуємо його
                    if (var < dp[i][j]) dp[i][j] = var;
                }
            }
        }
    }
    cout << dp[0][n - 1];
    return 0;
}