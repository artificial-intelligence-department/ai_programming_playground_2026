//Снігурочка
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    string words;
    int count = 0;
    while (cin >> words) {
        int n = words.length();
        bool isPal = true;
        for (int i = 0; i < n; i ++) {
            char left  = tolower(words[i]);
            char right = tolower(words[n - i - 1]);
            if (left != right)
            {
                isPal = false;
                break;
            }
        }
        if (isPal) {
            count++;
        }
    }
    cout << count;
    return 0;
}