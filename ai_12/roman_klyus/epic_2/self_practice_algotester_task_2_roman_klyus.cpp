#include <iostream>

using namespace std;

int main() {
    long long a, b;
    cin >> a >> b;

    if ((b - a) % 12 != 0) cout << -1;
    else cout << (a + b) * 13/2;
}