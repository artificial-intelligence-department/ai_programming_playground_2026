#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    string first, second;
    cin >> n >> first >> second;

    int answer = 0, groups = 0;
    char previous = '?';

    for (int i = 0; i < n; ++i) {
        if (first[i] == 'B' && second[i] == 'B') {
            ++answer;
        } else if (first[i] != second[i]) {
            if (first[i] != previous) {
                ++groups;
                previous = first[i];
            }
        }
    }

    if (groups > 0) answer += groups / 2 + 1;
    cout << answer << '\n';
}