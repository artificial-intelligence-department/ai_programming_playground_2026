/*
Цікавий масив, Момоток Артем, ШІ-13
*/
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int a[100];
    int total = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        total += a[i];
    }

    int prefix = 0;
    bool ok = false;
    for (int k = 1; k < n; k++) {   // k від 1 до n-1
        prefix += a[k - 1];
        if (prefix * 2 == total) {
            ok = true;
            break;
        }
    }

    if (ok) {
        cout << "TAK" << endl;
    } else {
        cout << "NI" << endl;
    }
    return 0;
}