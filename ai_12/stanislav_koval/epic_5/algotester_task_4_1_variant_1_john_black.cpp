#include <iostream>
#include <algorithm>
using namespace std;

void printArr(const int *r, int result) {
    cout << result << "\n";
    for (int i = 0; i < result; ++i) {
        if (i > 0) cout << ' ';
        cout << r[i];
    }
    cout << "\n";
}

int main() {
    int a[100], b[100], r[200];
    int n, m, result;

    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];

    cin >> m;
    for (int i = 0; i < m; ++i) cin >> b[i];

    sort(a, a + n);

    sort(b, b + m);

    result = set_difference(a, a + n, b, b + m, r) - r;
    printArr(r, result);
    cout << "\n";

    result = set_difference(b, b + m, a, a + n, r) - r;
    printArr(r, result);
    cout << "\n";

    result = set_intersection(a, a + n, b, b + m, r) - r;
    printArr(r, result);
    cout << "\n";

    result = set_union(a, a + n, b, b + m, r) - r;
    printArr(r, result);
    cout << "\n";

    result = set_symmetric_difference(a, a + n, b, b + m, r) - r;
    printArr(r, result);

    return 0;
}