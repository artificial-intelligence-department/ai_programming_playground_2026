#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main() {
    // Оптимізація введення-виведення
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int W, n;
    if (!(cin >>W >> n)) return 0;

    vector<int> a(n + 1);
    int total_sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        total_sum += a[i];
    }
    if (W > total_sum || W < 0) {
        cout << 0 << "\n";
        return 0;
    }

    // dp[i][w] — кількість способів набрати вагу w за допомогою перших i карт.
    // Обмежуємо значення числом 2, щоб уникнути переповнення типів даних.
    vector<vector<int>> dp(n + 1, vector<int>(W + 1,0));

    // Базовий випадок: є 1 спосіб набрати вагу 0 (не взявши жодної карти)
    dp[0][0] = 1;
    
    for (int i = 1; i <= n; ++i ) {
        int weight = a[i];
        for (int w = 0; w <= W; ++w) {
            //Варіант 1 не бкркмо карту.
            dp[i][w] = dp[i-1][w];

            //Варіант 2: беремо карту і.
            if (weight <= w) {
                dp[i][w] += dp[i-1][w - weight];
            }
            if (dp[i][w] > 2) dp[i][w] = 2;

        }
    }
    //Аналіз фінального результату
    if (dp[n][W] == 0) {
        cout << 0 << "\n";
    }   else if (dp[n][W] == 2) {
        cout << -1 << "\n";
    }   else {
        vector<int> missing_cards;
        int current_w = W;

        for (int i = n; i >= 1; --i) {
            if(dp[i-1][current_w] > 0) {
                missing_cards.push_back(i);
            }   else {
                current_w -= a[i];
            }
        }
        sort(missing_cards.begin(), missing_cards.end());

        for (int i = 0; i < missing_cards.size(); ++i) {
            cout << missing_cards[i] <<(i + 1 == missing_cards.size() ? "" : " ");
        }
    }

    return 0;
}
