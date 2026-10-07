#include <iostream>
using namespace std;
//задача 1802
int main() {
    long long a, b;
    cin >> a >> b;

    if ((b - a) % 12 == 0) {
        long long c = (a + b) / 2 * 13;
        cout << c;
    } else {
        cout << "-1";
    }

    return 0;
}