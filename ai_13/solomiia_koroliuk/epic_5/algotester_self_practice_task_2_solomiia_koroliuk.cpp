/* Task 0835 - Snow Maiden */

#include <iostream>
#include <string>
using namespace std;

// перетворюємо всі літери слова на малі
string toLower(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = s[i] + 32;
        }
    }
    return s;
}

// перевіряє, чи слово є паліндромом
bool isPalindrome(string s) {
    s = toLower(s);
    int left = 0;
    int right = s.size() - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
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

    cout << count << endl;
    return 0;
}
