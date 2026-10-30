#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    if (n < 1 || n > 100000) {
        cout << "Error: n out of range " << endl;
        return 1;
    }

    long long sum = 0;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;

        if (a < 0 || a > 1000000000) {
            cout << "Error: a_i out of range " << endl;
            return 1;
        }

        if (a > 0) sum += a - 1;
    }

    cout << sum << endl;
    return 0;
}

