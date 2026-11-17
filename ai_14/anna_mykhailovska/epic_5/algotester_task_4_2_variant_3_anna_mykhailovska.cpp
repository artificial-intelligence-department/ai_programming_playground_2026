/*
    Algotester lab 4 (2)
    Михайловська Анна
    ШІ-14
    Варіант 3
*/

#include <iostream>

using namespace std;

bool cmp(int x, int y) {
    if (x % 3 != y % 3)
        return x % 3 < y % 3;

    if (x % 3 == 1)
        return x > y;

    return x < y;
}

int main() {
    int n;
    cin >> n;

    int a[1000];

    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n - 1; i++) {
        int best = i;

        for (int j = i + 1; j < n; j++) {
            if (cmp(a[j], a[best]))
                best = j;
        }
        int temp = a[i];
        a[i] = a[best];
        a[best] = temp;
    }

    int m = 1;

    for (int i = 1; i < n; i++) {
        if (a[i] != a[m - 1]) {
            a[m] = a[i];
            m++;
        }
    }

    cout << m << '\n';

    for (int i = 0; i < m; i++)
        cout << a[i] << ' ';

    cout << '\n';

    return 0;
}