/*
Self practice task 2
Снігурочка
Лисюк Андріана
ШІ-13
*/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool isPalindrome(const string& s){
    if (s.empty()) return false;

    int left = 0;
    int right = s.length() - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
int main(){
    string word;
    int palindromeCount = 0;
    while (cin >> word){
        string cleaned = "";
        for (char c : word){
            if (isalpha(static_cast<unsigned char>(c))){
                cleaned += tolower(static_cast<unsigned char>(c));
            }
        }
        if (isPalindrome(cleaned)){
            palindromeCount++;
        }
    }
    cout << palindromeCount;

return 0;
}