// ДНК реп'яховірусу
#include <iostream>
#include <string>
using namespace std;

int main(){
    string s, t;
    cin >> t; // днк людини
    cin >> s; // днк вірусу

    int n = t.length();
    int m = s.length();

    if(n < m){
        cout << 0;
        return 0;
    }

    long long freq[26] = {};

    for(int i = 0; i <= n - m; i++){
        freq[t[i] - 'a']++;
    }

    long long count = 0;

    for(int j = 0; j < m; j++){
        count += freq[s[j] - 'a'] * (j + 1);

        if(j < m - 1){
            freq[t[j] - 'a']--;
            freq[t[j + n - m + 1] - 'a']++;
        }
    }
    cout << count;
    return 0;
}