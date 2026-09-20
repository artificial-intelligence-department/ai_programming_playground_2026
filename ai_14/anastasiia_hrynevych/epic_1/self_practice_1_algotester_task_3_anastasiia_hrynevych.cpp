#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int main () {
    int n;  cin>> n;
    int v = 0,  k = 0; int v_wins = 0, k_wins = 0;
    for (int i = 0; i < n; i++) {
        char c; cin >> c;
        if (c == 'V') v++;
        else k++;
        if (v >= 11 && v - k == 2) {
            v_wins++;
            v = 0; k = 0;
        }
        if (k >= 11 && k - v == 2) {
            k_wins++;
            v = 0; k = 0;
        }
    }
    cout << k_wins << ":" << v_wins << endl;
    if ( v != 0 || k != 0) {
        cout << k << ":" << v << endl;
    }
}