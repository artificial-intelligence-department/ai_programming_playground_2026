#include <iostream>
using namespace std;

int main() {
    long long previous, current;

    cin >> previous;

    if (previous <= 0) {
        cout << "ERROR";
        return 0;
    }

    for (int i = 1; i < 5; i++) {
        cin >> current;

        if (current <= 0) {
            cout << "ERROR";
            return 0;
        }

        if (current > previous) {
            cout << "LOSS";
            return 0;
        }

        previous = current;
    }

    cout << "WIN";

    return 0;
}