#include <iostream>
using namespace std;

int main() {

    long long a = 0;
    long long b = 0;
    long long c = 0;

    cin >> a >> b >> c;

    if (a + b > c) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}