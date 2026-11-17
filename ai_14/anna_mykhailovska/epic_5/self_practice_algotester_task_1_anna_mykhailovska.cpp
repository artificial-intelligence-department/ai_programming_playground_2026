/*
    Задача: Cнігурочка
    Михайловська Анна
    ШІ-14
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string word;
    int answer = 0;

    while (cin >> word) {
        bool palindrome = true;
        int n = word.size();

        for (int i = 0; i < n / 2; i++) {
            if (tolower(word[i]) != tolower(word[n - 1 - i])) {
                palindrome = false;
                break;
            }
        }

        if (palindrome) {
            answer++;
        }
    }

    cout << answer << endl;
    return 0;
}