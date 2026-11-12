#include <stdio.h>

#define MAXL 1005
#define MAXLEN 205
#define MOD 1000000007

char s[MAXL];
char aux[MAXLEN];

// Масиви для ДП та префіксних сум
int count_match[MAXL][MAXL];
int dp[MAXL][MAXL];
int pref[MAXL][MAXL];
int col_sum[MAXL][MAXL];

// Підрахунок довжини рядка через вказівники
int str_len(const char *str) {
    const char *p = str;
    while (*p != '\0') p++;
    return (int)(p - str);
}

// Видалення символів переведення рядка '\n' та '\r'
void trim_nl(char *str) {
    char *p = str;
    while (*p != '\0') {
        if (*p == '\n' || *p == '\r') {
            *p = '\0';
            break;
        }
        p++;
    }
}

// Зчитування непорожнього рядка (пропускає порожні рядки-розділювачі між тестами)
int read_non_empty_line(char *buf, int size) {
    while (fgets(buf, size, stdin) != NULL) {
        trim_nl(buf);
        if (str_len(buf) > 0) {
            return 1;
        }
    }
    return 0;
}

void solve_test() {
    if (!read_non_empty_line(s, sizeof(s))) return;
    int L = str_len(s);

    char line[128];
    if (!read_non_empty_line(line, sizeof(line))) return;
    int n = 0;
    sscanf(line, "%d", &n);

    // Очищення матриць для поточного тесту
    for (int i = 0; i <= L; ++i) {
        for (int j = 0; j <= L; ++j) {
            count_match[i][j] = 0;
            dp[i][j] = 0;
            pref[i][j] = 0;
            col_sum[i][j] = 0;
        }
    }

    // 1. Пошук входжень допоміжних рядків у цільовий рядок s
    for (int i = 0; i < n; ++i) {
        read_non_empty_line(aux, sizeof(aux));
        int m = str_len(aux);
        if (m > L) continue;

        for (int l = 0; l <= L - m; ++l) {
            int match = 1;
            for (int k = 0; k < m; ++k) {
                if (*(s + l + k) != *(aux + k)) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                int r = l + m - 1;
                count_match[l][r]++;
            }
        }
    }

    // 2. Обчислення ДП за зростанням правого кінця r_prime
    for (int r_prime = 0; r_prime < L; ++r_prime) {
        // Довжина допоміжного рядка не перевищує 200, тому min_l >= r_prime - 199
        int min_l = r_prime - 199;
        if (min_l < 0) min_l = 0;

        for (int l_prime = min_l; l_prime <= r_prime; ++l_prime) {
            int c = count_match[l_prime][r_prime];
            if (c == 0) continue;

            if (l_prime == 0) {
                // Базовий випадок: відрізок починається з 0-го індексу
                dp[0][r_prime] = c % MOD;
            } else {
                // Отримуємо суму всіх можливих попередніх відрізків за O(1)
                int ways = col_sum[r_prime - 1][l_prime];
                dp[l_prime][r_prime] = (int)((1LL * c * ways) % MOD);
            }
        }

        // 3. Побудова префіксних сум рядка pref та оновлення стовпчиків col_sum
        long long cur = 0;
        for (int k = 1; k <= L; ++k) {
            cur += dp[k - 1][r_prime];
            if (cur >= MOD) cur %= MOD;
            pref[r_prime][k] = (int)cur;

            long long prev_col = (r_prime > 0) ? col_sum[r_prime - 1][k] : 0;
            long long add_val = (r_prime >= k) ? cur : 0;
            col_sum[r_prime][k] = (int)((prev_col + add_val) % MOD);
        }
    }

    // Відповідь — сума всіх dp[l][L - 1], що відповідає pref[L - 1][L]
    int ans = pref[L - 1][L];
    printf("%d\n", ans);
}

int main() {
    char line[128];
    if (!read_non_empty_line(line, sizeof(line))) return 0;
    int t = 0;
    sscanf(line, "%d", &t);

    while (t--) {
        solve_test();
    }

    return 0;
}