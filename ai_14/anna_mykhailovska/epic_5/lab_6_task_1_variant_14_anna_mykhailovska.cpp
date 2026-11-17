/*
    Lab 6
    Михайловська Анна
    ШІ-14
    Варіант 14
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    string s, word, result;

    bool letter = false;
    bool digit = false;
    bool correct = true;

    getline(cin, s);
    s += ' ';

    for (int i = 0; i < s.size(); i++) {
        char c = s[i];

        if (c == ' ') {
            if (letter && digit && correct) {
                if (result != "") {
                    result += ' ';
                }
                result += word;
            }

            word = "";
            
            letter = false;
            digit = false;
            correct = true;

        } else {
            word += c;
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                letter = true;
            } else if (c >= '0' && c <= '9') {
                digit = true;
            } else {
                correct = false;
            }
        }
    }
    s = result;
    cout << s;

    return 0;
}
