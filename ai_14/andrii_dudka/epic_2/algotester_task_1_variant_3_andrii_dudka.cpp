#include <iostream>

using namespace std;

int main() {
    long long prev = 0;

    for (int i = 0; i < 5; ++i) {
        long long current;
        cin >> current;

        if (current <= 0) {
            cout << "ERROR\n";
            return 0;
        }

        if (i > 0 && current > prev) {
            cout << "LOSS\n";
            return 0;
        }

        prev = current;
    }

    cout << "WIN\n";
    return 0;
}