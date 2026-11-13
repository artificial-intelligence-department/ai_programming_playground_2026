/*
Algotester lab 4 1
variant 2
Лисюк Андріана
ШІ-13
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    if (!(cin >> n >> k)) return 0;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    auto it = unique(a.begin(), a.end());
    a.erase(it, a.end());

    int m = a.size();

    if (m > 0) {
        k %= m;
        rotate(a.begin(), a.begin() + k, a.end());
    }

    cout << m << "\n";
    for (int i = 0; i < m; ++i) {
        cout << a[i] << (i + 1 == m ? "" : " ");
    }
    cout << "\n";

    return 0;
}