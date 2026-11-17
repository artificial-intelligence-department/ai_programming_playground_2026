#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    int* a = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int* p1 = partition(a, a + n, [](int x) {
        return x % 3 == 0;
    });

    int* p2 = partition(p1, a + n, [](int x) {
        return x % 3 == 1;
    });

    sort(a, p1);
    sort(p1, p2, greater<int>());
    sort(p2, a + n);

    int* last = unique(a, a + n);
    int k = last - a;

    cout << k << endl;

    for (int i = 0; i < k; i++) {
        cout << a[i] << " ";
    }

    delete[] a;

    return 0;
}