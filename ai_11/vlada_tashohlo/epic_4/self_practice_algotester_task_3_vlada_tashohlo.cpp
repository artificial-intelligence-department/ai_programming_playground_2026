
/* 
Епік 4. self practice: Algotester, задача "Назва ресторану"
Авторка: Влада Ташогло
Група: ші-11
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int k;
    string s;

    cin >> k >> s;

    int n = s.size();
    int best = 0;

    // Початок першого підрядка
    for (int p = 0; p <= n; p++) {

        // Початок другого підрядка
        for (int q = p; q <= n; q++) {

            int maxA = min(n - p, q - p);
            int maxC = n - q;

            int columns = maxC + 1;
            int* dp = new int[(maxA + 1) * columns]();

            // Обчислення LCS для всіх довжин
            for (int i = 1; i <= maxA; i++) {
                for (int j = 1; j <= maxC; j++) {

                    if (s[p + i - 1] == s[q + j - 1]) {
                        dp[i * columns + j] = dp[(i - 1) * columns + j - 1] + 1;
                    }
                    else {
                        dp[i * columns + j] = max(
                            dp[(i - 1) * columns + j],
                            dp[i * columns + j - 1]
                        );
                    }

                    int scs = i + j - dp[i * columns + j];

                    if (scs <= k) {
                        best = max(best, i + j);
                    }
                }
            }

            // Випадки, коли один підрядок порожній
            for (int i = 1; i <= maxA; i++) {
                if (i <= k) {
                    best = max(best, i);
                }
            }

            for (int j = 1; j <= maxC; j++) {
                if (j <= k) {
                    best = max(best, j);
                }
            }

            delete[] dp;
        }
    }

    cout << 2 * k - best << '\n';

    return 0;
}
