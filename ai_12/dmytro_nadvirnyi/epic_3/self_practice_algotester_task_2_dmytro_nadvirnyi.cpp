/* Коля, Вася і Теніс
        0031       */

#include <iostream>
#include <string>
using namespace std;

void countGames(int n, string s) {
    int k = 0, v = 0;
    int winK = 0, winV = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'K') {
            k++;
        } else if (s[i] == 'V') {
            v++;
        }

        if (k >= 11 && k - v >= 2) {
            winK++;
            k = 0;
            v = 0;
        } else if (v >= 11 && v - k >= 2) {
            winV++;
            k = 0;
            v = 0;
        }
    }

    cout << winK << ":" << winV << endl;

    if (k > 0 || v > 0) {
        cout << k << ":" << v << endl;
    }
}

int main() {
    int n;
    string s;

    cin >> n >> s;

    countGames(n, s);

    return 0;
}
