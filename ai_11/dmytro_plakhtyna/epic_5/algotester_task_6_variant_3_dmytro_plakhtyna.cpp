//Шахова дошка
#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    string field[9];
    for (int i = 0; i < n; i ++) {
        cin >> field[i];
    }
    int q, x, y;
    cin >> q;
    for (int i = 0; i < q; i ++){
        cin >> x >> y;
        x--;
        y--;
        if (field[x][y] != '0') {
            cout << 1 << endl;
            cout << field[x][y] << endl;
            continue;
        }
        bool used[10] = {false};

        for (int j = 0; j < n; j++) {
        if (field[x][j] != '0') {
            used[field[x][j] - '0'] = true;
        }
    }

        for (int j = 0; j <n; j++) {
            if (field[j][y] != '0') {
                used[field[j][y] - '0'] = true;
        }
    }
    int count = 0;
    for (int d = 1; d <= n; d++) {
        if (!used[d]) {
            count++;
    }
}
    cout << count << endl;
    bool first = true;
    for (int d = 1; d <= n; d++) {
        if (!used[d]) {
            if (!first) cout << " ";
                cout << d;
                first = false;
    }
}
cout << endl;
}

    return 0;
}