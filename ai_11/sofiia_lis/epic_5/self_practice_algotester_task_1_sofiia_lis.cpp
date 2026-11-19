/* 
Епік 5. self_practice_algotester_task_1 "ДНК реп'яховірусу"
Авторка: Софія Ліс
Група: ші-11
*/

#include <string>
#include <iostream>

using namespace std;

int main() {
    string t, s;
    cin >> t >> s;
    size_t n = t.length(), m = s.length();

    if (m > n) { 
        cout << 0; 
        return 0; 
    }

    size_t w = n - m;          
    long long cnt[26] = {};  
    for (size_t i = 0; i <= w; i++) {
        cnt[t[i] - 'a']++;
    }

    long long sum = 0;
    for (size_t j = 0; j < m; j++) {
        sum += (long long)(j + 1) * cnt[s[j] - 'a'];
        if (j + 1 < m) {
            cnt[t[j] - 'a']--;
            cnt[t[j + w + 1] - 'a']++;
        }
    }
    cout << sum;
    return 0;
}
