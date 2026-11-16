#include <iostream>
#include <string>
#include <cctype>
using namespace::std;
// Снігурочка

int main () {
    string poem;
    int c = 0;
    while (cin >> poem) {
        bool palindrome = true;
        int l = poem.length();

        for (int i = 0; i < l/2; i++) {
            char left = tolower(poem[i]);
            char right = tolower(poem[l - i - 1]);
            if (left != right) {
                palindrome = false;
                break;
            }
        }
        if(palindrome) c++;
    }
    cout << c;
    return 0;
}