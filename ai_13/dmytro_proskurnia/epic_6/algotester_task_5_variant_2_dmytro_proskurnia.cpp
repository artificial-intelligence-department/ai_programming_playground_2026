#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> cave(n);
    for (int i = 0; i < n; i++) {
        cin >> cave[i];
    }

    // кожен стовпець обробляємо знизу вгору:
    // pos - найнижча вільна клітинка, куди впаде наступна піщинка
    for (int j = 0; j < m; j++) {
        int pos = n - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (cave[i][j] == 'X') {
                pos = i - 1;
            } else if (cave[i][j] == 'S') {
                cave[i][j] = 'O';
                cave[pos][j] = 'S';
                pos--;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << cave[i] << "\n";
    }

    return 0;
}
