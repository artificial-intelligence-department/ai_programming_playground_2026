/*
Назва задачі: Буквозабирання
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <string>

using namespace std;

bool matches(const string &initial, const string &target, int start) {
    for (int i = 0; i < (int)target.size(); i++) {
        if (initial[start + i] != target[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int tests;
    cin >> tests;

    for (int i = 0; i < tests; i++) {
        string initial;
        string target;
        cin >> initial >> target;

        if (initial.size() < target.size()) {
            cout << "Larry\n";
            continue;
        }

        int moves = (int)initial.size() - (int)target.size();
        int middle = moves / 2;

        bool sergeiWins;
        if (moves == 0) {
            sergeiWins = (initial == target);
        } else if (moves % 2 == 1) {
            
            sergeiWins = matches(initial, target, middle)
                && matches(initial, target, middle + 1);
        } else {
            
            sergeiWins = matches(initial, target, middle)
                || (matches(initial, target, middle - 1)
                    && matches(initial, target, middle + 1));
        }

        if (sergeiWins) {
            cout << "Sergei\n";
        } else {
            cout << "Larry\n";
        }
    }

    return 0;
}