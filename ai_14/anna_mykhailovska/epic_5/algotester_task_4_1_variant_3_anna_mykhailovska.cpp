/*
    Algotester lab 4 (1)
    Михайловська Анна
    ШІ-14
    Варіант 3
*/

#include <iostream>
#include <algorithm>

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

    sort(a, a + n, cmp);

    int m = unique(a, a + n) - a;

    cout << m << '\n';

    for (int i = 0; i < m; i++)
        cout << a[i] << ' ';   
    cout << '\n';

    return 0;
}
