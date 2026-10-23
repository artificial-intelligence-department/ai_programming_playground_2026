/*
Алготестер задача 3 Зуби
Станіслав Коваль
ШІ-12
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;

    int cur = 0, best = 0;

    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;

        if (a >= k) {
            cur++;
            if (cur > best) best = cur;
        } else {
            cur = 0;
        }
    }

    cout << best << endl;
    return 0;
}