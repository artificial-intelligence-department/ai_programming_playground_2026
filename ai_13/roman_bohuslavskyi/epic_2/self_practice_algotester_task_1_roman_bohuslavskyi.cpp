//Balls
#include <iostream>
using namespace std;

int main() {
    long long R, r;

    cin >> R >> r;

    long long result = R * R - 4 * R * r + r * r;

    if (result < 0) {
        cout << "rumpled" << endl;
    }
    else {
        cout << "safe" << endl;
    }

    return 0;
}