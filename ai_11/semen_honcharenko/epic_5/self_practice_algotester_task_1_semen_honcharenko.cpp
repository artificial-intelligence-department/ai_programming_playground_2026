/*
    Алготестер. "Снігурочка"
    Гончаренко Семен
    ШІ-11
*/
#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(const string &s) {
    int i = 0, j = (int)s.size() - 1;
    while (i < j) {
        if (s[i] != s[j]) return false;
        i++;
        j--;
    }
    return true;
}

int main() {
    string word;
    int cnt = 0;

    while (cin >> word) {
        for (size_t k = 0; k < word.size(); k++) {
            if (word[k] >= 'A' && word[k] <= 'Z')
                word[k] = word[k] - 'A' + 'a';
        }
        if (isPalindrome(word)) cnt++;
    }

    cout << cnt << endl;
    return 0;
}