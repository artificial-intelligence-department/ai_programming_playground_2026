/*
Задача:  ДНК реп'яховірусу
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    string text, virus;
    cin >> text >> virus;

    int n = text.length();
    int m = virus.length();

    if (n < m) {
        cout << 0 << endl;
        return 0;
    }

    int count[26] = {};
    int length = n - m + 1;

    for (int i = 0; i < length; i++) {
        count[text[i] - 'a']++;
    }

    long long result = 0;

    for (int i = 0; i < m; i++) {
        long long position = i + 1;
        int matches = count[virus[i] - 'a'];
        result += position * matches;

        if (i + 1 < m) {
            count[text[i] - 'a']--;
            count[text[i + length] - 'a']++;
        }
    }

    cout << result << endl;

    return 0;
}
