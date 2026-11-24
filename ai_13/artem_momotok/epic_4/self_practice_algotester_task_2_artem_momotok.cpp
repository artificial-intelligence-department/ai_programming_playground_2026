/*
Симетрична матриця, Момоток Артем, ШІ-13
*/
#include <iostream>
using namespace std;

char a[1000][1001];   // 1000 рядків по 1000 символів + '\0'

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    bool ok = true;
    for (int i = 0; i < n && ok; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i][j] != a[j][i]) {
                ok = false;
                break;
            }
        }
    }

    if (ok) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}