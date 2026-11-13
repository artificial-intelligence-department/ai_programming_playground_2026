#include <stdio.h>

#define MAXN 100005

char s[MAXN];
char t[MAXN];
int ans[MAXN];
int ans_len = 0;

int max_sub[MAXN];
int min_req[MAXN][2];
int last_failed[MAXN][2];

int n = 0;
int m = 0;

int str_len(const char *str) {
    const char *p = str;
    while (*p != '\0') p++;
    return (int)(p - str);
}

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

// Рекурсивна функція з відсіканням тупикових гілок
int dfs(int i, int j, int prev_taken) {
    if (i == n) {
        return (j == m);
    }

    int rem_needed = m - j;

    // Відсікання 1: чи не вимагає хвіст рядка більше вирізань, ніж у нас лишилося в t
    if (rem_needed < min_req[i][prev_taken] || rem_needed > (n - i)) {
        return 0;
    }

    // Відсікання 2: чи здатний хвіст рядка s взагалі вмістити решту t
    if (rem_needed > max_sub[i]) {
        return 0;
    }

    // Якщо цей стан для поточного j вже перевірявся і він тупиковий
    if (last_failed[i][prev_taken] == j) {
        return 0;
    }

    // Чи зобов'язані ми різати поточний символ?
    // Так, якщо був перехід між буквами, а попередній символ НЕ вирізали
    int must_take = (i > 0 && *(s + i - 1) != *(s + i) && prev_taken == 0);

    // Варіант 1: ВИРІЗАТИ символ s[i] у рядок t (якщо букви збігаються)
    if (j < m && *(s + i) == *(t + j)) {
        *(ans + ans_len) = i + 1; // 1-нумерація
        ans_len++;
        if (dfs(i + 1, j + 1, 1)) {
            return 1;
        }
        ans_len--; // Відкат, якщо гілка зайшла в глухий кут
    }

    // Варіант 2: ЗАЛИШИТИ символ s[i] (можна, якщо він не є обов'язковим для розрізу)
    if (!must_take) {
        if (dfs(i + 1, j, 0)) {
            return 1;
        }
    }

    last_failed[i][prev_taken] = j;
    return 0;
}

int main() {
    if (fgets(s, sizeof(s), stdin) == NULL) return 0;
    trim_nl(s);

    if (fgets(t, sizeof(t), stdin) == NULL) return 0;
    trim_nl(t);

    n = str_len(s);
    m = str_len(t);

    if (m > n) {
        printf("NO\n");
        return 0;
    }

    // 1. Швидка перевірка: чи є t підпослідовністю s взагалі
    int check_j = 0;
    for (int i = 0; i < n; ++i) {
        if (check_j < m && *(s + i) == *(t + check_j)) {
            check_j++;
        }
    }
    if (check_j < m) {
        printf("NO\n");
        return 0;
    }

    // 2. Рахуємо справа наліво max_sub
    int tj = m - 1;
    max_sub[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (tj >= 0 && *(s + i) == *(t + tj)) {
            tj--;
        }
        max_sub[i] = m - 1 - tj;
    }

    // 3. Рахуємо справа наліво min_req (мінімальні обов'язкові розрізи на стиках)
    min_req[n][0] = 0;
    min_req[n][1] = 0;
    for (int i = n - 1; i >= 0; --i) {
        for (int prev_taken = 0; prev_taken <= 1; ++prev_taken) {
            int must = (i > 0 && *(s + i - 1) != *(s + i) && prev_taken == 0);
            if (must) {
                min_req[i][prev_taken] = 1 + min_req[i + 1][1];
            } else {
                int opt0 = min_req[i + 1][0];
                int opt1 = 1 + min_req[i + 1][1];
                min_req[i][prev_taken] = (opt0 < opt1) ? opt0 : opt1;
            }
        }
    }

    if (m < min_req[0][1]) {
        printf("NO\n");
        return 0;
    }

    // Ініціалізація пам'яті невдалих станів
    for (int i = 0; i <= n; ++i) {
        last_failed[i][0] = -1;
        last_failed[i][1] = -1;
    }

    // 4. Запуск пошуку правильних індексів
    if (dfs(0, 0, 1)) {
        printf("YES\n");
        for (int k = 0; k < m; ++k) {
            printf("%d%c", *(ans + k), (k == m - 1) ? '\n' : ' ');
        }
    } else {
        printf("NO\n");
    }

    return 0;
}