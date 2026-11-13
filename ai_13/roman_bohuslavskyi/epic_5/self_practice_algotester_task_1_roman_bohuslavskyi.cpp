/*
Задача:  Буквозабирання
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    int tests;
    cin >> tests;

    for (int i = 0; i < tests; i++) {
        string text, target;
        cin >> text >> target;

        int length = target.length();
        int moves = text.length() - target.length();
        int middle = moves / 2;
        bool sergeiWins = false;

        if (moves % 2 == 1) {
            sergeiWins = text.substr(middle, length) == target && text.substr(middle + 1, length) == target;
        }
        else if (text.substr(middle, length) == target) {
            sergeiWins = true;
        }
        else if (moves >= 2) {
            sergeiWins = text.substr(middle - 1, length) == target && text.substr(middle + 1, length) == target;
        }

        if (sergeiWins) {
            cout << "Sergei" << endl;
        }
        else {
            cout << "Larry" << endl;
        }
    }

    return 0;
}