/*
Задача:  Алготестер Lab5v2
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>

using namespace std;

const int MAX_SIZE = 1000;

void dropSand(char field[][MAX_SIZE + 1], int rows, int columns);

int main() {
    static char cave[MAX_SIZE][MAX_SIZE + 1];
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> cave[i];
    }

    dropSand(cave, n, m);

    for (int i = 0; i < n; i++) {
        cout << cave[i] << '\n';
    }

    return 0;
}

void dropSand(char field[][MAX_SIZE + 1], int rows, int columns) {
    for (int column = 0; column < columns; column++) {
        int bottom = rows - 1;

        for (int row = rows - 1; row >= 0; row--) {
            if (field[row][column] == 'X') {
                bottom = row - 1;
            }
            else if (field[row][column] == 'S') {
                field[row][column] = 'O';
                field[bottom][column] = 'S';
                bottom--;
            }
        }
    }
}
