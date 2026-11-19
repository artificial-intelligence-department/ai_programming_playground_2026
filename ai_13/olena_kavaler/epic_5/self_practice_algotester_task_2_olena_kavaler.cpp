
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
#include <string>
using namespace std;

int pref[26][100001];

int main() {
    string t, s;
    cin >> t >> s;

    int n = t.length();
    int m = s.length();

    if (m > n) {
        cout << 0 << endl;
        return 0;
    }

    for (int c = 0; c < 26; c++) {
        for (int i = 0; i < n; i++) {
            if (t[i] - 'a' == c) {
                pref[c][i + 1] = pref[c][i] + 1;
            } else {
                pref[c][i + 1] = pref[c][i];
            }
        }
    }

    long long ans = 0;

    for (int j = 0; j < m; j++) {
        int c = s[j] - 'a';
        int cnt = pref[c][j + n - m + 1] - pref[c][j];
        ans += (long long)(j + 1) * cnt;
    }

    cout << ans << endl;
    return 0;
}