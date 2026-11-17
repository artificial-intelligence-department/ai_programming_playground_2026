/*
    Algotester lab 6
    Михайловська Анна
    ШІ-14
    Варіант 3
*/
#include <iostream>

using namespace std;

int main() {

    int n;
    cin >> n;

    char a[10][10];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];

    int q;
    cin >> q;

    while (q--) {
        int x, y;
        cin >> x >> y;

        if (a[x][y] != '0') {
            cout << 1 << '\n' << a[x][y] << '\n';
            continue;
        }

        bool used[10] = {};

        for (int i = 1; i <= n; i++) {
            used[a[x][i] - '0'] = true;
            used[a[i][y] - '0'] = true;
        }

        int m = 0;

        for (int digit = 1; digit <= n; digit++)
            if (!used[digit])
                m++;

        cout << m << '\n';

        if (m > 0) {
            for (int digit = 1; digit <= n; digit++)
                if (!used[digit])
                    cout << digit << ' ';

            cout << '\n';
        }
    }

    return 0;
}