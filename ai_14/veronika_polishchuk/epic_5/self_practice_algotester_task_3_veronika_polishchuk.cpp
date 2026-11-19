//Найдорожчий подарунок

#include <iostream>
#include <string>
using namespace std;

int nxt[10005][3];

int main() {
    int n;
    string s;
    cin >> n >> s;

    // таблиця "де наступна буква c"
    for (int c = 0; c < 3; c++) nxt[n][c] = n;
    for (int i = n - 1; i >= 0; i--) {
        for (int c = 0; c < 3; c++) {
            if (s[i] - 'a' == c) nxt[i][c] = i;
            else nxt[i][c] = nxt[i + 1][c];
        }
    }

    long long ans = n;
    
    int total = 1;
    for (int L = 1; L <= 9; L++) {
        total *= 3;
        for (int m = 0; m < total; m++) {
            int r[9];
            int x = m;
            for (int j = 0; j < L; j++) {
                r[j] = x % 3;
                x /= 3;
            }

            // жадібно шукаємо, скільки разів r повторюється як підпослідовність
            int pos = 0, k = 0;
            bool ok = true;
            while (ok) {
                for (int j = 0; j < L; j++) {
                    int p = nxt[pos][r[j]];
                    if (p >= n) { ok = false; break; }
                    pos = p + 1;
                }
                if (ok) k++;
            }

            long long price = (long long)k * k * L;   // ціна = k*k*L
            if (price > ans) ans = price;
        }
    }

    cout << ans;
    return 0;
}