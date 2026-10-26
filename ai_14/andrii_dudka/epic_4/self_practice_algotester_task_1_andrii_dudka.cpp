#include <iostream>
using namespace std;

bool canSplit(const long long* a, int n) {
    long long total = 0;

    for (int i = 0; i < n; ++i) {
        total += a[i];
    }

    long long left = 0;

    for (int i = 0; i < n - 1; ++i) {
        left += a[i];

        if (left == total - left) {
            return true;
        }
    }

    return false;
}

int main() {
    int n;
    cin >> n;

    long long* a = new long long[n];

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if (canSplit(a, n)) {
        cout << "TAK\n";
    } else {
        cout << "NI\n";
    }

    delete[] a;

    return 0;
}