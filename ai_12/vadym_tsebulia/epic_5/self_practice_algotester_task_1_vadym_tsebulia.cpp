#include <iostream>

using namespace std;

int main() {
    long long n, a0, a1;
    cin >> n >> a0 >> a1;

    if (a0 == 0 && a1 == 0){
        cout << "0" << endl;
        return 0; 
    }

    if (n == 0) {
        if (a0 > 0) cout << "+" << endl;
        else if (a0 < 0) cout << "-" << endl;
        else cout << "0" << endl;
        return 0;
    }

    if (n == 1) {
        if (a1 > 0) cout << "+" << endl;
        else if (a1 < 0) cout << "-" << endl;
        else cout << "0" << endl;
        return 0;
    }

    long long prev2 = a0;
    long long prev1 = a1;
    long long cur = 0;

    for (long long i = 2; i <= n; ++i) {
        if (prev1 > 0 && prev2 > 0) {
            cout << "+" << endl;
            return 0;
        }
        if (prev1 < 0 && prev2 < 0) {
            cout << "-" << endl;
            return 0;
        }
        cur = prev1 + prev2;
        prev2 = prev1;
        prev1 = cur;
    }

    if (cur > 0) cout << "+" << endl;
    else if (cur < 0) cout << "-" << endl;
    else cout << "0" << endl;

    return 0;
}