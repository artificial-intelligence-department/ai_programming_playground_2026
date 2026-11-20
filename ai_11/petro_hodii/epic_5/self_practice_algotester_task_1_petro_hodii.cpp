
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool isPalindrome(const string& s) {
    int left = 0;
    int right = static_cast<int>(s.size()) - 1;

    while (left < right) {
        char c1 = static_cast<char>(tolower(static_cast<unsigned char>(s[left])));
        char c2 = static_cast<char>(tolower(static_cast<unsigned char>(s[right])));
        if (c1 != c2) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string word;
    int count = 0;

    while (cin >> word) {
        if (isPalindrome(word)) {
            count++;
        }
    }

    cout << count << '\n';
    return 0;
}