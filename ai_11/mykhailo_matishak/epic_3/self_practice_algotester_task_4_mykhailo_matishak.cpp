#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[100];
    long long total = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        total += a[i];
    }

    if (total % 2 != 0) {
        cout << "NI" << endl;
        return 0;
    }

    long long half = total / 2;
    long long cur = 0;
    bool found = false;
    for (int i = 0; i < n - 1; i++) {
        cur += a[i];
        if (cur == half) {
            found = true;
            break;
        }
    }

    cout << (found ? "TAK" : "NI") << endl;
    return 0;
}