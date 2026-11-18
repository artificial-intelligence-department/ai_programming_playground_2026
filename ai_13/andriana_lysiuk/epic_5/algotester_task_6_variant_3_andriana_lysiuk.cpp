/*
Algotester Lab 6
variant 3
Лисюк Андріана
ШІ-13
*/

#include <iostream>
#include <string>
using namespace std;
int main() {
    int n;
    cin >> n;
    string grid[9];
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    int queries;
    cin >> queries;
    while (queries--) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        if (grid[x][y] != '0') {
            cout << 1 << "\n" << grid[x][y] << "\n\n";
            continue;
        }
        bool used[10] = {false};
        for (int i = 0; i < n; i++) {
            used[grid[x][i] - '0'] = true;
            used[grid[i][y] - '0'] = true;
        }
        int allowed[9];
        int count = 0;
        for (int d = 1; d <= n; d++) {
            if (!used[d]) {
                allowed[count] = d;
                count++;
            }
        }
        cout << count << "\n";
        if (count > 0) {
            for (int i = 0; i < count; i++) {
                if (i > 0) cout << " ";
                cout << allowed[i];
            }
            cout << "\n";
        }
        cout << "\n";
    }
    return 0;
}