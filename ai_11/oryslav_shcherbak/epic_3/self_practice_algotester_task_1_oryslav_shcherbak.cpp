#include <iostream>
using namespace std;

/*
 * Задача: Надлишкове число
 * Щербак Орислав
 * Група ШІ-11
 */

int main() {
    int n;
    cin >> n;
    int* s = new int[n + 1]();
    // s[x] — сума власних дільників числа x
    for (int d = 1; d <= n; ++d) {
        for (int m = 2 * d; m <= n; m += d) {
            s[m] += d;
        }
    }
    int cnt = 0;
    for (int x = 1; x <= n; ++x) {
        if (s[x] > x) {
            ++cnt;
        }
    }
    cout << cnt << '\n';
    delete[] s;
    return 0;
}