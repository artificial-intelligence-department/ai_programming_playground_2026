#include <iostream>
using namespace std;

int main() {
    long long n;
    cin >> n;

    long long number = 0;

    for (long long i = 0; i < n; i++) {
        long long a;
        cin >> a;
        number += a - 1;
    }

    cout << number << endl;

    return 0;
}