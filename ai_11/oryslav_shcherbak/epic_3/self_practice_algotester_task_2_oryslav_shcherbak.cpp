#include <iostream>
using namespace std;

/*
 * Задача: Зуби
 * Щербак Орислав
 * Група ШІ-11
 */

int main() {
    int n;
    long long k;
    cin >> n >> k;
    int best = 0, current = 0;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        if (a >= k) {
            current++;
            best = max(best, current);
        } else {
            current = 0;
        }
    }
    cout << best << '\n';
    return 0;
}