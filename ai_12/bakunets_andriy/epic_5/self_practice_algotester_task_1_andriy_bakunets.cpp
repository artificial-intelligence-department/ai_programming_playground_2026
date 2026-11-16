#include <cstdio>

short dp[301][301][151];
char s[1005];

int mx(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int main() {
    int n;
    scanf("%d %s", &n, s);

    int c0 = 0;
    int c1 = 0;
    for (int k = 0; k < n; k++) {
        char ch = s[k];
        if (ch == '0') {
            c0++;
        } else {
            c1++;
        }
    }

    if (c0 % 2 == 1 && c1 % 2 == 1) {
        printf("-1\n");
        return 0;
    }

    bool odd = (n % 2 == 1);
    char mid = '1';
    if (c0 % 2 == 1) {
        mid = '0';
    }

    int maxX = c0 / 2;

    for (int i = n; i >= 0; i--) {
        for (int j = i; j <= n; j++) {
            for (int x = 0; x <= maxX; x++) {
                int best = -1;

                if (j == i) {
                    if (x == 0 && !odd) {
                        best = 0;
                    }
                }

                else if (j == i + 1) {
                    if (x == 0 && (!odd || s[i] == mid)) {
                        best = 0;
                    }
                }

                else {
                    best = mx(dp[i + 1][j][x],
                              dp[i][j - 1][x]);

                    if (s[i] == s[j - 1]) {
                        if (s[i] == '0') {
                            if (x > 0 && dp[i + 1][j - 1][x - 1] >= 0) {
                                best = mx(best, dp[i + 1][j - 1][x - 1]);
                            }
                        }

                        else {
                            if (dp[i + 1][j - 1][x] >= 0) {
                                best = mx(best, dp[i + 1][j - 1][x] + 1);
                            }
                        }
                    }
                }

                dp[i][j][x] = best;
            }
        }
    }

    int ans = n - c0 / 2 - c1 / 2;

    for (int r0 = 0; 2 * r0 <= c0; r0++) {
        for (int r1 = 0; 2 * r1 <= c1; r1++) {
            int m = r0 + r1;
            if (m >= ans) {
                continue;
            }

            int p = 0;
            int z = 0;
            int o = 0;
            while (z < r0 || o < r1) {
                if (s[p] == '0') {
                    z++;
                }

                else {
                    o++;
                }
                p++;
            }

            int px = (c0 - 2 * r0) / 2;
            int py = (c1 - 2 * r1) / 2;

            if (dp[p][n][px] >= py) {
                ans = m;
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}