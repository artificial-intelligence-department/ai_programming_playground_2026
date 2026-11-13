#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    int best = 1;
    int cur = 1;

    for (int i = 1; i < n; i++) {
        if (s[i] > s[i - 1]) {
            cur++;
        } else {
            cur = 1; 
        }

        if (cur > best) {
            best = cur;
        }
    }

    cout << best << endl;
    return 0;
}