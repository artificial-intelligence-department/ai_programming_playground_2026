/*
    Лабораторна робота Алготестер. Завдання 6. Варіант 2.
    Гончаренко Семен
    ШІ-11
*/
#include <cstdio>
using namespace std;

int fabs(int v) {
    if (v < 0) {
        return -v;
    }
    else {
        return v;
    }
}

bool attacks(char piece, int row, int col, int x, int y) {
    int diff_row = x - row;
    int diff_col = y - col;
    int abs_row = fabs(diff_row);
    int abs_col = fabs(diff_col);

    if (piece == 'P') {
        return (diff_row == 1 && abs_col == 1);
    }
    if (piece == 'R') {
        return (abs_row == 0 || abs_col == 0);
    }
    if (piece == 'B') {
        return (abs_row == abs_col);
    }
    if (piece == 'Q') {
        return (abs_row == 0 || abs_col == 0 || abs_row == abs_col);
    }
    if (piece == 'N') {
        return ((abs_row == 1 && abs_col == 2) || (abs_row == 2 && abs_col == 1));
    }
    if (piece == 'K') {
        return (abs_row <= 1 && abs_col <= 1);
    }
    return 0;
}

int main() {
    char board[8][8];
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            scanf(" %c", &board[i][j]);
        }
    }

    int q;
    scanf("%d", &q);

    for (int t = 0; t < q; t++) {
        int x, y;
        scanf("%d %d", &x, &y);

        if (board[x - 1][y - 1] != 'O') {
            printf("X\n");
            continue;
        }

        char res[65];
        int n = 0;
        for (int row = 1; row <= 8; row++) {
            for (int col = 1; col <= 8; col++) {
                char p = board[row - 1][col - 1];
                if (p != 'O' && attacks(p, row, col, x, y)) {
                    bool exists = 0;
                    for (int k = 0; k < n; k++) {
                        if (res[k] == p) {
                            exists = 1;
                        }
                    }
                    if (exists == 0) {
                        res[n] = p;
                        n++;
                    }
                }
            }
        }

        if (n == 0) {
            printf("O\n");
            continue;
        }

        for (int i = 1; i < n; i++) {
            char key = res[i];
            int j = i - 1;
            while (j >= 0 && res[j] > key) {
                res[j + 1] = res[j];
                j--;
            }
            res[j + 1] = key;
        }
        res[n] = '\0';
        printf("%s\n", res);
    }
    return 0;
}