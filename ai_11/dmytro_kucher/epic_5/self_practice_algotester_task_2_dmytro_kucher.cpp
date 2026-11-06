/*
Епік 5. Self Practice: Algotester, задача "Снігурочка"
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool func (const string& word) {

    int size = word.size();

    if (size == 0) return false;

    for (int i = 0; i<size/2; i++) {
        if (tolower(word[i]) != tolower(word[size-i-1])) return false;
    }

    return true;
}

int main () {

    string text;
    int count = 0;

    while (getline(cin, text)) {

        string word = "";

        for (int i = 0; i<=text.size(); i++) {
            if (i < text.size() && isalpha(text[i])) word += text[i];
            else {
                if (func(word)) count++;
                word = "";
            }
        }
    }

    cout << count;

    return 0;
}