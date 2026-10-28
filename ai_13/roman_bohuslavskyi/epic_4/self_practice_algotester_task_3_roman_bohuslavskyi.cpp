/*
Задача:  Коні ходять по шахівниці
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    char a[8][8];

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            a[i][j] = '.';
        }
    }

    int dx[8] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dy[8] = {1, -1, 1, -1, 2, -2, 2, -2};

    for (int i = 0; i < n; i++) {
        char col;
        int row;
        cin >> col >> row;

        int y = col - 'a';
        int x = row - 1;

        for (int j = 0; j < 8; j++) {
            int nextX = x + dx[j];
            int nextY = y + dy[j];

            if (nextX >= 0 && nextX < 8 && nextY >= 0 && nextY < 8) {
                a[nextX][nextY] = 'K';
            }
        }
    }

    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            cout << a[i][j];
        }
        cout << endl;
    }

    return 0;
}