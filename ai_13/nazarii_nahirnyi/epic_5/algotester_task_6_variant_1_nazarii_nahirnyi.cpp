#include <iostream>
#include <cstring>

using namespace std;

char words[100005][12];

void qs(int l, int r) {
    int i = l, j = r;
    char p[12];
    strcpy(p, words[(l + r) / 2]);

    while (i <= j) {
        while (strcmp(words[i], p) < 0) i++;
        while (strcmp(words[j], p) > 0) j--;
        if (i <= j) {
            char t[12];
            strcpy(t, words[i]);
            strcpy(words[i], words[j]);
            strcpy(words[j], t);
            i++;
            j--;
        }
    }

    if (l < j) qs(l, j);
    if (i < r) qs(i, r);
}

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> words[i];
        for (int j = 0; words[i][j] != '\0'; j++) {
            if (words[i][j] < 'a') {
                words[i][j] += 32;
            }
        }
    }

    qs(0, n - 1);

    bool used[26] = {false};
    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && strcmp(words[i], words[j]) == 0) {
            j++;
        }
        if (j - i >= k) {
            for (int c = 0; words[i][c] != '\0'; c++) {
                used[words[i][c] - 'a'] = true;
            }
        }
        i = j;
    }

    int ans = 0;
    for (int c = 0; c < 26; c++) {
        if (used[c]) ans++;
    }

    if (ans == 0) {
        cout << "Empty!";
        return 0;
    }

    cout << ans << "\n";
    for (int c = 25; c >= 0; c--) {
        if (used[c]) {
            cout << char('a' + c) << " ";
        }
    }

    return 0;
}