#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    char g[9][10];                      // поле максимум 9x9
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }

    int q;
    cin >> q;

    while (q--) {
        int x, y;
        cin >> x >> y;
        x--; y--;                       

        // клітинка заповнена
        if (g[x][y] != '0') {
            cout << 1 << "\n" << g[x][y] << "\n\n";
            continue;
        }

        bool used[10] = {false};

        // позначаємо цифри в рядку x і в стовпці y
        for (int i = 0; i < n; i++) {
            used[g[x][i] - '0'] = true;   
            used[g[i][y] - '0'] = true;   
        }

        // збираємо вільні цифри від 1 до n
        int res[9];
        int cnt = 0;
        for (int d = 1; d <= n; d++)
            if (!used[d]) {
                res[cnt++] = d;
            }
            
        cout << cnt << "\n";
        for (int i = 0; i < cnt; i++) {
            if (i) cout << " ";
            cout << res[i];
        }
        cout << "\n\n";
    }
    return 0;
}