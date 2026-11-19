/*
Назва: Снігурочка
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool palindrome(const string& word) {
    int left = 0;
    int right = word.length() - 1;

    while (left < right) {
        if (tolower((unsigned char)word[left]) != tolower((unsigned char)word[right])) {
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
        if (palindrome(word)) {
            count++;
        }
    }

    cout << count << endl;
    return 0;
}