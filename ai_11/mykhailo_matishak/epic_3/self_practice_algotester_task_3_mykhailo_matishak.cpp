#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    int signal = 15;
    for (char c : s) {
        if (c == 'k') {
            signal = max(signal - 1, 0);
        } else if (c == 'p') {
            signal = (signal >= 1) ? 15 : 0;
        } else if (c == 'z') {
            signal = (signal >= 1) ? 0 : 15;
        }
    }

    cout << signal << endl;
    return 0;
}