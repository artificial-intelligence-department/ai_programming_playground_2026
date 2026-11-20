/*Algotester task 6 
Sofiia Chovhan 
Variant 1*/
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    unordered_map<string, int> words;

    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;

        for (char &c : s) {
            if (c >= 'A' && c <= 'Z') {
                c = c - 'A' + 'a';
            }
        }

        words[s]++;
    }

    bool used[26] = {};

    for (const auto &p : words) {
        if (p.second >= K) {
            for (char c : p.first) {
                used[c - 'a'] = true;
            }
        }
    }

    int M = 0;

    for (int i = 0; i < 26; i++) {
        if (used[i]) {
            M++;
        }
    }

    if (M == 0) {
        cout << "Empty!\n";
        return 0;
    }

    cout << M << '\n';

    bool first = true;

    for (int i = 25; i >= 0; i--) {
        if (used[i]) {
            if (!first) {
                cout << " ";
            }

            cout << char('a' + i);
            first = false;
        }
    }

    cout << '\n';

    return 0;
}