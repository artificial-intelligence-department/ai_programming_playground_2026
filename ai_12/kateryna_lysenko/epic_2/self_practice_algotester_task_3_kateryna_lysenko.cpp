#include <iostream>
using namespace std;

int main() {
    long long n, m, k;
    cin >> n >> m >> k;

    if ((n * m) % k == 0) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
