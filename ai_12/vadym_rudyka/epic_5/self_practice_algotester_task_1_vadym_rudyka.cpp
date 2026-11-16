#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    char c;
    cin >> n >> c;

    string best = "";

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        int pos = s.size();

        for (int j = 0; j < s.size(); j++) {
            if (s[j] > c) {
                pos = j;
                break;
            }
        }

        s.insert(pos, 1, c);

        if (best == "" || s < best) {
            best = s;
        }
    }

    cout << best << '\n';

    return 0;
}