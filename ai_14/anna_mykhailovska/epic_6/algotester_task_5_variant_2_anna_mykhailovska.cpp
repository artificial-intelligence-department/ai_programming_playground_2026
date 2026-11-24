/*
    Задача: Algotester Lab 5
    Варіант: 5
    Михайловська Анна
    ШІ-14
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    string a[1000];

    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int j = 0; j < m; j++) {
        int pos = n - 1;

        for (int i = n - 1; i >= 0; i--) {
            if (a[i][j] == 'X') {
                pos = i - 1;
            }
            else if (a[i][j] == 'S') {
                a[i][j] = 'O';
                a[pos][j] = 'S';
                pos--;
            }
        }
    }

    cout << '\n';
    for (int i = 0; i < n; i++)
        cout << a[i] << '\n';

    return 0;
}

