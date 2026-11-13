/*
Self practice task 3
Emoji
Лисюк Андріана
ШІ-13
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    if (!(cin >> n >> k)) return 0;
    string s;
    cin >> s;
    vector<string> valid_emojis(k);
    for (int i = 0; i < k; ++i) {
        cin >> valid_emojis[i];
    }
    sort(valid_emojis.begin(), valid_emojis.end());
    vector<int> dp(n + 1, 0);
    int last_colon = -1;
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1] + 1;
        if (s[i - 1] == ':') {
            if (last_colon != -1) {
                int name_len = (i - 1) - (last_colon + 1);
                if (name_len > 0) {
                    string name = s.substr(last_colon + 1, name_len);
                    if (binary_search(valid_emojis.begin(), valid_emojis.end(), name)) {
                        dp[i] = min(dp[i], dp[last_colon] + 1);
                    }
                }
            }
            last_colon = i - 1;
        }
    }
    cout << dp[n] << "\n";
    return 0;
}