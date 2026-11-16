#include <iostream>
#include <string>

int pref[26][100001];

int main() {
    std::string t, s;
    std::cin >> t >> s;
    int n = t.size();
    int m = s.size();

    if (m > n) {
        std::cout << 0;
        return 0;
    }

    for (int c = 0; c < 26; c++) {
        for (int i = 0; i < n; i++) {
            pref[c][i + 1] = pref[c][i] + (t[i] - 'a' == c);
        }
    }

    long long result = 0;
    for (int i = 0; i < m; i++) {
        int c = s[i] - 'a';
        int count = pref[c][i + n - m + 1] - pref[c][i];
        result += (long long)(i + 1) * count;
    }

    std::cout << result;
    return 0;
}