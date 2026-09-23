#include <iostream>

using namespace std;

int main() {
    long long a[5];
    for (int i = 0; i < 5; i++) cin >> a[i];

    long long top = 0;

    for (int i = 0; i < 5; i++) {
        if (a[i] <= 0) {
            cout << "ERROR" << endl;
            return 0;
        }

        if (i > 0 && a[i] > top) {
            cout << "LOSS" << endl;
            return 0;
        }

        top = a[i];
    }

    cout << "WIN" << endl;
    return 0;
}
