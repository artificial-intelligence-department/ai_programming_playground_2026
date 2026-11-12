/*
Назва задачі: Вакцина від реп'яховіруса
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    string s, t;
    cin >> s >> t;

    int textLength = (int)s.length();
    cout << textLength << '\n';

    for (int i = 0; i < textLength; i++) {
        char neededLetter = t[i];
        int pos = (int)s.find(neededLetter);

        if (i > 0) {
            cout << ' ';
        }
        cout << pos + 1;

        s.erase(pos, 1);
        s += neededLetter;
    }

    cout << '\n';
    return 0;
}