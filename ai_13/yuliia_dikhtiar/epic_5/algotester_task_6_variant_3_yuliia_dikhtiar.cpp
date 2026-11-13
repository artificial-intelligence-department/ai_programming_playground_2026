/*
Назва задачі: Lab 6v3
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    int n;
    cin >> n;

    int field[9][9];
    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < n; j++) {
            field[i][j] = row[j] - '0';
        }
    }

    int queries;
    cin >> queries;
    for (int query = 0; query < queries; query++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        if (field[x][y] != 0) {
            cout << 1 << '\n' << field[x][y] << '\n';
            continue;
        }

        bool used[10] = {};
        for (int i = 0; i < n; i++) {
            used[field[x][i]] = true;
            used[field[i][y]] = true;
        }

        int count = 0;
        for (int digit = 1; digit <= n; digit++) {
            if (!used[digit]) {
                count++;
            }
        }

        cout << count << '\n';
        if (count > 0) {
            bool first = true;
            for (int digit = 1; digit <= n; digit++) {
                if (!used[digit]) {
                    if (!first) {
                        cout << ' ';
                    }
                    cout << digit;
                    first = false;
                }
            }
            cout << '\n';
        }
    }

    return 0;
}