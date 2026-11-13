/*
Задача:  Алготестер Lab6v3
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>
#include <string>

using namespace std;

void showPossibleDigits(const string field[], int n, int row, int column);

int main() {
    int n;
    cin >> n;
    string field[9];

    for (int i = 0; i < n; i++) cin >> field[i];

    int queries;
    cin >> queries;
    for (int i = 0; i < queries; i++) {
        int x, y;
        cin >> x >> y;
        showPossibleDigits(field, n, x - 1, y - 1);
    }

    return 0;
}

void showPossibleDigits(const string field[], int n, int row, int column) {
    if (field[row][column] != '0') {
        cout << 1 << endl;
        cout << field[row][column] << endl;
        return;
    }

    bool used[10] = {};
    for (int i = 0; i < n; i++) {
        if (i != column) {
            used[field[row][i] - '0'] = true;
        }
        if (i != row) {
            used[field[i][column] - '0'] = true;
        }
    }

    int count = 0;
    for (int digit = 1; digit <= n; digit++) {
        if (!used[digit]) count++;
    }
    cout << count << endl;
    if (count == 0) return;

    bool first = true;
    for (int digit = 1; digit <= n; digit++) {
        if (!used[digit]) {
            if (!first) cout << ' ';
            cout << digit;
            first = false;
        }
    }
    cout << endl;
}
