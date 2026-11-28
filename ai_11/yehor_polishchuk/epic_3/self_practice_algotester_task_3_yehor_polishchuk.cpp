#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int a[1000], b[1000];
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    int bad = 0;
    for (int i = 0; i < n; i++) {
        if (b[i] != a[n - 1 - i]) {
            bad++;
            break;
        }
    }

    if (bad == 0) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
        for (int i = 0; i < n; i++) {
            cout << a[n - 1 - i] << (i + 1 < n ? ' ' : '\n');
        }
    }

    return 0;
}