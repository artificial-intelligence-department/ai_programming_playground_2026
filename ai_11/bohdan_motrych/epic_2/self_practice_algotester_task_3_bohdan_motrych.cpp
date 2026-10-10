#include <iostream>
using namespace std;

int main() {
    long long a = 0, b = 0, k = 0;
    if (cin >> a >> b >> k) {
        long long total = a + b * k;
        cout << total << endl;
    }

    return 0;
}