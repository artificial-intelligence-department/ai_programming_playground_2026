#include <iostream>
#include <string>

using namespace std;

int main(){
    string s, t;
    cin >> s >> t;

    int n = static_cast<int>(s.length());
    int last[26], shifts[26] = {};
    string used(n, '0');

    for (int i = 0; i < 26; ++i){
        last[i] = -1;
    }
    for (int i = 0; i < n; ++i){
        last[s[i] - 'a'] = i;
    }

    cout << n << '\n';

    for (int i = 0; i < n; ++i){
        int letter = t[i] - 'a';
        int pos = last[letter];

        cout << pos - shifts[letter] + 1;
        cout << (i + 1 == n ? '\n' : ' ');

        for (int j = 0; j < 26; ++j){
            if (last[j] > pos){
                ++shifts[j];
            }
        }

        used[pos] = '1';
        --pos;
        while (pos >= 0 && s[pos] != t[i]){
            if (used[pos] == '1'){
                --shifts[letter];
            }
            --pos;
        }
        last[letter] = pos;
    }

    return 0;
}