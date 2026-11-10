/*
Поле чудес
Кузовніков В'ячеслав Євгеніойвич
ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    int n = 0;
    if (!(cin >> n)) return 0;

    int* a = new int[n];

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int k = 1; k <= n; ++k) {
        bool ok = true;
        for (int i = 0; i < n - k; ++i) {
            if (a[i] != a[i + k]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << k;
            break;
        }
    }

    delete[] a; 
    return 0;
}