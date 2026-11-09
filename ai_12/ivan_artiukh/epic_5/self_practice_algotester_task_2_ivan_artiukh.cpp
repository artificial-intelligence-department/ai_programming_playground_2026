//снігурочка
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string word;
    int mark = 0;
    while (cin >> word) {
        int len = word.length();
        bool isPalindrome = true;
        for(int i = 0; i < len / 2; i++){
            if( tolower(word[i]) != tolower(word[len-i-1]) ){
                isPalindrome = false;
            }
        }
        if(isPalindrome){
            mark++;
        }
    }
    cout << mark << "\n";
    return 0;
}