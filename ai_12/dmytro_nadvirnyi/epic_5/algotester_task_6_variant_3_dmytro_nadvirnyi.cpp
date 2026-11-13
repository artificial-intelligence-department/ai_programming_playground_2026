#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // 1. Зчитай поле (вектор рядків)
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    int q;
        cin >> q;
        while (q--) {
            int x, y;
            cin >> x >> y;
            // Переводимо у 0-індексацію
            int r = x - 1;
            int c = y - 1;


             // Випадок 1: клітинка вже заповнена
            if (grid[r][c] != '0') {
                cout << 1 << "\n";
                cout << grid[r][c] << "\n\n";
                continue;
            }

                // Випадок 2: клітинка пуста ('0')
            // Масив для позначення цифр від 1 до 9 (індекс = цифра)
            vector<bool> used(n + 1, false);

            for (int j = 0; j < n; ++j) {
                if (grid[r][j] != '0') {
                    int digit = grid[r][j] - '0';
                    if (digit >= 1 && digit <= n) used[digit] = true;
                }
            }
            for (int i = 0; i < n; ++i) {
                if (grid[i][c] != '0') {
                    int digit = grid[i][c] - '0';
                    if (digit >= 1 && digit <= n) used[digit] = true;
                }
            }

                // 3. Збираємо доступні цифри від 1 до N
            vector<int> available;
            for (int d = 1; d <= n; ++d) {
                if (!used[d]) {
                    available.push_back(d);
                }
            }


                // 4. Виводимо результат
            if (available.empty()) {
                cout << 0 << "\n\n";
            } else {
                cout << available.size() << "\n";
                for (size_t i = 0; i < available.size(); ++i) {
                    cout << available[i] << (i + 1 == available.size() ? "" : " ");
                }
                cout << "\n\n";
            }
        }


    return 0;
}