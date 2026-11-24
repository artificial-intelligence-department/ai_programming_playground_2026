#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s, t;
    if (!(std::cin >> s >> t)) return 0;

    int n = s.length();
    int m = t.length();

    // 1. Пошук найближчих 'A' та 'B' праворуч для кожного індексу
    std::vector<int> nextA(n + 1, n), nextB(n + 1, n);
    for (int i = n - 1; i >= 0; --i) {
        nextA[i] = (s[i] == 'A') ? i : nextA[i + 1];
        nextB[i] = (s[i] == 'B') ? i : nextB[i + 1];
    }

    // get_R(x) повертає індекс, після якого шматок почне містити і 'A', і 'B'
    auto get_R = [&](int x) {
        if (x >= n) return n;
        return std::max(nextA[x + 1], nextB[x + 1]);
        };

    // M[v] = мінімальний індекс x (від -1 до n-1), для якого get_R(x) >= v
    std::vector<int> M(n + 2, n);
    int ptr = -1;
    for (int v = 0; v <= n + 1; ++v) {
        while (ptr < n && get_R(ptr) < v) {
            ptr++;
        }
        M[v] = ptr;
    }

    // Швидкий доступ до наступного/попереднього входження будь-якого символу
    std::vector<std::vector<int>> nxt(26, std::vector<int>(n + 1, n));
    for (int i = n - 1; i >= 0; --i) {
        for (int c = 0; c < 26; ++c) nxt[c][i] = nxt[c][i + 1];
        nxt[s[i] - 'A'][i] = i;
    }

    std::vector<std::vector<int>> prv(26, std::vector<int>(n + 1, -1));
    for (int i = 0; i < n; ++i) {
        for (int c = 0; c < 26; ++c) prv[c][i] = (i > 0) ? prv[c][i - 1] : -1;
        prv[s[i] - 'A'][i] = i;
    }

    // 2. Зворотний прохід (Right-to-Left): знаходимо "вікно" можливостей [low[i], high[i]]
    std::vector<int> low(m), high(m);
    for (int i = m - 1; i >= 0; --i) {
        int req = (i == m - 1) ? n : low[i + 1];
        int min_x = std::max(0, M[req]);
        int max_x = (i == m - 1) ? n - 1 : high[i + 1] - 1;

        if (min_x > max_x) { std::cout << "NO\n"; return 0; }

        int c = t[i] - 'A';
        int first_occ = nxt[c][min_x];
        int last_occ = max_x >= 0 ? prv[c][max_x] : -1;

        // Якщо в потрібному діапазоні немає відповідної літери
        if (first_occ > max_x || last_occ < min_x) {
            std::cout << "NO\n";
            return 0;
        }

        low[i] = first_occ;
        high[i] = last_occ;
    }

    // Перевірка суфікса перед найпершим обраним елементом (індекс -1)
    if (low[0] > get_R(-1)) {
        std::cout << "NO\n";
        return 0;
    }

    // 3. Прямий прохід (Left-to-Right): безпечно забираємо перші коректні індекси
    std::vector<int> ans(m);
    for (int i = 0; i < m; ++i) {
        int c = t[i] - 'A';
        // Наступний індекс має бути щонайменше більшим за попередній і в межах low[i]
        int min_x_fwd = (i == 0) ? low[0] : std::max(low[i], ans[i - 1] + 1);
        ans[i] = nxt[c][min_x_fwd];
    }

    // 4. Успішне виведення
    std::cout << "YES\n";
    for (int i = 0; i < m; ++i) {
        std::cout << ans[i] + 1 << (i + 1 == m ? "" : " ");
    }
    std::cout << "\n";

    return 0;
}