// Задача №0182 - Зуби
#include <iostream>
using namespace std;

int main() {
    long long n, k;
    cin >> n >> k;

    long long current = 0;
    long long max = 0;

    for (long long i = 0; i < n; i++) {
        long long a;
        cin >> a;

        if (a >= k) {
            current++;

            if (current > max) {
                max = current;
            }
        } else {
            current = 0;
        }
    }

    cout << max << endl;
    return 0;
}
