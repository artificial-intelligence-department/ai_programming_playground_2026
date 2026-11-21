 #include <iostream>

using namespace std;

void print_answer(const char field[9][9], int n, int row, int column) {
    if (field[row][column] != '0') {
        cout << 1 << '\n' << field[row][column] << '\n';
        return;
    }

    bool used[10] = {};
    for (int i = 0; i < n; ++i) {
        used[field[row][i] - '0'] = true;
        used[field[i][column] - '0'] = true;
    }

    int possible[9];
    int count = 0;

    for (int digit = 1; digit <= n; ++digit) {
        if (!used[digit]) {
            possible[count] = digit;
            ++count;
        }
    }

    cout << count << '\n';
    for (int i = 0; i < count; ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << possible[i];
    }
    cout << '\n';
}

int main() {
    int n;
    cin >> n;

    char field[9][9];
    for (int row = 0; row < n; ++row) {
        for (int column = 0; column < n; ++column) {
            cin >> field[row][column];
        }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;

        if (i > 0) {
            cout << '\n';
        }
        print_answer(field, n, x - 1, y - 1);
    }
}
