#include <iostream>
using namespace std;

int main() {
    long long n;
    cin >> n;

    bool ok = false;
    for (int b = 0; b <= 3 && !ok; b++) {
        long long rest = n - 7LL * b;
        if (rest >= 0 && rest % 4 == 0) {
            ok = true;
        }
    }

    cout << (ok ? "Yes" : "No") << endl;
    return 0;
}