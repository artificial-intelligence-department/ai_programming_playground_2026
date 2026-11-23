//снігурочка
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

//без урахування регістру
bool isPalindrome(const string& s) {
    int i = 0;
    int r = s.size() - 1;

    while (i < r) {
        if (tolower(s[i]) != tolower(s[r])) {
            return false;
        }
        i++;
        r--;
    }
    return true;
}

int main() {
    string word;
    int count = 0;

    while (cin >> word) {
        if (isPalindrome(word)) {
            count++;
        }
    }

    cout << count << "\n";
    return 0;
}