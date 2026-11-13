#include <iostream>
#include <string>

using namespace std;


bool ComposeAndPredictWhoGoesFirst(const string& s, const string& t, int pos) {
    if (pos < 0 || pos + (int)t.size() > (int)s.size()) {
        return false;
    }
    for (int i = 0; i < (int)t.size(); ++i) {
        if (s[pos + i] != t[i]) {
            return false;
        }
    }
    return true;
}

void write_winner() {
    string s, t;
    cin >> s >> t;

    int k = (int)s.size() - (int)t.size();
    bool sergei_wins = false;

    if (k == 0) {
        sergei_wins = (s == t);
    } else if (k > 0) {
        int r = k / 2;
        if (k % 2 == 1) {

            sergei_wins = ComposeAndPredictWhoGoesFirst(s, t, r) && ComposeAndPredictWhoGoesFirst(s, t, r + 1);
        } else {

            sergei_wins = ComposeAndPredictWhoGoesFirst(s, t, r) || (ComposeAndPredictWhoGoesFirst(s, t, r - 1) && ComposeAndPredictWhoGoesFirst(s, t, r + 1));
        }
    }

    cout << (sergei_wins ? "Sergei\n" : "Larry\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    if (cin >> tests) {
        while (tests--) {
            write_winner();
        }
    }
    return 0;
}

