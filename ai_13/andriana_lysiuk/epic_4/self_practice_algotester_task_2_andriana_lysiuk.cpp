/*
Сума двох
Лисюк Андріана
ШІ-13
*/

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int n, m;
    long long x;
    cin >> n >> m >> x;

    long long* a = new long long[n];
    long long* b = new long long[m];

    for (int i = 0; i < n; i++) cin >> a[i];
    for (int j = 0; j < m; j++) cin >> b[j];

    sort(a, a + n);
    sort(b, b + m, greater<long long>());

    int i = 0;
    int j = 0;
    long long min_diff = abs(a[0] + b[0] - x);

    while (i < n && j < m) {
        long long current_sum = a[i] + b[j];
        
        min_diff = min(min_diff, abs(current_sum - x));

        if (current_sum < x) {
            i++;
        } else if (current_sum > x) {
            j++;
        } else {
            min_diff = 0;
            break;
        }
    }

    cout << min_diff;

    delete[] a;
    delete[] b;

    return 0;
}