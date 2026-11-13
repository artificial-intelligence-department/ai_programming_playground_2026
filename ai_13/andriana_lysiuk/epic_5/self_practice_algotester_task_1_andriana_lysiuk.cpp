/*
Self practice task 1
Буквозабирання
Лисюк Андріана
ШІ-13
*/

#include <iostream>
#include <string>

using namespace std;

bool matches(const string& start, const string& target, int left, int moves) {
    int targetLen = target.size();
    if (left < 0 || left > moves) return false;
    return start.compare(left, targetLen, target) == 0;
}
int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        string start, target;
        cin >> start >> target;
        int startLen = start.size();
        int targetLen = target.size();
        int moves = startLen - targetLen;

        bool sergeiWins;
        if (moves == 0) {
            sergeiWins = matches(start, target, 0, moves);
        } else if (moves % 2 == 1) {
            int center = (moves - 1) / 2;
            sergeiWins = matches(start, target, center, moves)
                      && matches(start, target, center + 1, moves);
        } else {
            int center = moves / 2;
            sergeiWins = matches(start, target, center, moves)
                      || (matches(start, target, center - 1, moves)
                          && matches(start, target, center + 1, moves));
        }
        cout << (sergeiWins ? "Sergei" : "Larry") << "\n";
    }
    return 0;
}