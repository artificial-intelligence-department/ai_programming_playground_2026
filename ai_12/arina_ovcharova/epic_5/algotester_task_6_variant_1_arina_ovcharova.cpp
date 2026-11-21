// Algotester Lab 6, варіант 1
// букви зі слів, які зустрічаються >= K разів
#include <iostream>
#include <string>
#include <map>
using namespace std;

// великі і малі букви однакові, тому все переводжу в малі
string toLowerWord(string s) {
    for (size_t i = 0; i < s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] - 'A' + 'a';
        }
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // слово -> скільки разів зустрілось
    map<string, int> cnt;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        cnt[toLowerWord(s)]++;
    }

    // used[c] = true, якщо буква c вже є у відповіді
    bool used[26] = {false};
    for (map<string, int>::iterator it = cnt.begin(); it != cnt.end(); it++) {
        if (it->second >= k) {
            string w = it->first;
            for (size_t i = 0; i < w.length(); i++) {
                used[w[i] - 'a'] = true;
            }
        }
    }

    int m = 0;
    for (int c = 0; c < 26; c++) {
        if (used[c]) {
            m++;
        }
    }

    if (m == 0) {
        cout << "Empty!" << endl;
        return 0;
    }

    cout << m << endl;
    // від останньої букви до першої, тому з 'z' до 'a'
    for (int c = 25; c >= 0; c--) {
        if (used[c]) {
            cout << (char)('a' + c) << " ";
        }
    }
    cout << endl;

    return 0;
}
