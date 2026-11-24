/*
    Algotester Lab 2v3, Момоток Артем, ШІ-13
*/
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[1001];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int l = 1, r = n;
    while (true) {
        if (l == r) {
            cout << l << " " << r << "\nCollision\n";
            break;
        }
        if (l > r) {
            cout << l << " " << r << "\nMiss\n";
            break;
        }
        if (r - l == 1) {
            cout << l << " " << r << "\nStopped\n";
            break;
        }
        int newL = l + a[l];
        int newR = r - a[r];
        l = newL;
        r = newR;
    }
    return 0;
}
