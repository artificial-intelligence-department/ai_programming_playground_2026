#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    long long MOD = 1000000007;
    long long f1 = 1;
    long long f2 = 2;
    long long fn = 1;

    if (n == 1) fn = f1;
    else if (n == 2) fn = f2;
    else {
        for (int i = 3; i <= n; ++i) {
            fn = (f1 + f2) % MOD;
            f1 = f2;
            f2 = fn;
        }
    }

    long long fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact = (fact * i) % MOD;
    }

    long long result = (fact * fn) % MOD;

    cout << result;

    return 0;
}
