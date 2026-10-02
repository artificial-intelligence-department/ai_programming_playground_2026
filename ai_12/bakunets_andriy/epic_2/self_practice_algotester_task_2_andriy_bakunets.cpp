#include <iostream>

using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;

    if ((b - a) % 12 == 0) {
        long long sum = (a + b) * 13 / 2;
        cout << sum << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}