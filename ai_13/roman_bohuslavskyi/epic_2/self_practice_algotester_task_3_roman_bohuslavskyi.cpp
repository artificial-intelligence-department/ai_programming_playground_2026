//How much to pay?
#include <iostream>
using namespace std;

int main() {
    long long a, b;

    cin >> a >> b;

    if (a < b) {
        if (a + 1 < b) {
            cout << a + 1 << endl;
        }
        else {
            cout << -1 << endl;
        }
    }
    else {
        if (b + 1 < a) {
            cout << b + 1 << endl;
        }
        else {
            cout << -1 << endl;
        }
    }

    return 0;
}