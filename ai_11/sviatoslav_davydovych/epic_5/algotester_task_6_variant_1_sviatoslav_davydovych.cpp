#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    
    const int LIMIT = 100005;
    const int CLET = 26;
    string words[LIMIT];

    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> words[i];
        for (int sym = 0; sym<words[i].length(); sym++) {
            words[i][sym]=tolower(words[i][sym]);
        }
    }

    sort(words, words + n);

    int charArr[CLET] = {0};

    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && words[j] == words[i]) {
            j++;
        }
        int count = j - i;
        if (count >= k) {
            for (char c : words[i]) {
                charArr[c - 'a'] = 1;
            }
        }
        i = j;
    }

    int unique_count = 0;
    for (int c = 0; c < CLET; c++) {
        if (charArr[c]) {
            unique_count++;
        }
    }

    if (unique_count == 0) {
        cout << "Empty!";
    } else {
        cout << unique_count << "\n";
        for (int c = 25; c >= 0; c--) {
            if (charArr[c]) {
                cout << (char)('a' + c) << " ";
            }
        }
    }

    return 0;
}