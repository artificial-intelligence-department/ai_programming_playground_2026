#include <stdio.h>

/**
 * Обчислення довжини рядка через різницю вказівників (аналог strlen).
 */
int str_length(const char *str) {
    const char *ptr = str;
    while (*ptr != '\0') {
        ptr++;
    }
    return (int)(ptr - str);
}

/**
 * Очищення рядка від символів переведення каретки/рядка ('\n', '\r')
 * за допомогою вказівника.
 */
void trim_newline(char *str) {
    char *ptr = str;
    while (*ptr != '\0') {
        if (*ptr == '\n' || *ptr == '\r') {
            *ptr = '\0';
            break;
        }
        ptr++;
    }
}

/**
 * Порівняння двох фрагментів пам'яті через розіменування вказівників.
 * Повертає 1 (true), якщо збігаються, або 0 (false).
 */
int match_prefixes(const char *p1, const char *p2, int len) {
    for (int i = 0; i < len; ++i) {
        if (*(p1 + i) != *(p2 + i)) {
            return 0; // Знайдено відмінність
        }
    }
    return 1; // Усі len символів однакові
}

/**
 * Визначення нового стану збігу після додавання символу c.
 * Використовує адресну арифметику та вказівники.
 */
int get_next_state(int state, char c, const char *s, int m) {
    // Літера 'C' миттєво обнуляє збіг, оскільки s містить тільки 'A' і 'B'
    if (c == 'C') {
        return 0;
    }

    // Буфер для поточного суфікса
    char cur[32];
    for (int i = 0; i < state; ++i) {
        *(cur + i) = *(s + i);
    }
    *(cur + state) = c;

    int cur_len = state + 1;
    int max_len = (cur_len < m) ? cur_len : m;

    // Шукаємо найдовший суфікс cur, що збігається з префіксом s
    for (int len = max_len; len >= 1; --len) {
        const char *suffix_ptr = cur + (cur_len - len);
        const char *prefix_ptr = s;

        if (match_prefixes(suffix_ptr, prefix_ptr, len)) {
            return len;
        }
    }

    return 0;
}

int main() {
    int n = 0;
    char buffer[64];
    char s[64];

    // 1. Зчитування n через fgets + sscanf
    // Це запобігає класичній помилці, коли scanf залишає '\n' в буфері stdin
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    sscanf(buffer, "%d", &n);

    // 2. Зчитування рядка s через fgets
    if (fgets(s, sizeof(s), stdin) == NULL) {
        return 0;
    }
    trim_newline(s); // Прибираємо перехід на новий рядок

    int m = str_length(s);

    // Граничний випадок: якщо заборонений рядок довший за n
    if (m > n) {
        long long total = 1;
        for (int i = 0; i < n; ++i) {
            total *= 3;
        }
        printf("%lld\n", total);
        return 0;
    }

    // Статичний масив на стеку для підрахунку станів
    long long dp[20] = {0};
    *(dp + 0) = 1; // Початковий стан (збіг 0 символів)

    const char alphabet[3] = {'A', 'B', 'C'};

    // Покрокове нарощування довжини SMS
    for (int step = 0; step < n; ++step) {
        long long next_dp[20] = {0};

        for (int state = 0; state < m; ++state) {
            long long current_ways = *(dp + state);
            if (current_ways == 0) continue;

            for (int i = 0; i < 3; ++i) {
                char c = *(alphabet + i);
                int nxt = get_next_state(state, c, s, m);

                // Якщо новий стан не заборонений (nxt < m)
                if (nxt < m) {
                    *(next_dp + nxt) += current_ways;
                }
            }
        }

        // Оновлення основного масиву через вказівники
        for (int i = 0; i < m; ++i) {
            *(dp + i) = *(next_dp + i);
        }
    }

    // Підсумовуємо всі можливі варіанти
    long long total_valid = 0;
    for (int state = 0; state < m; ++state) {
        total_valid += *(dp + state);
    }

    // 3. Форматований вивід результату через printf
    printf("%lld\n", total_valid);

    return 0;
}