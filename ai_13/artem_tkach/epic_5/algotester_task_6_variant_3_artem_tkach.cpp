#include <cstdio>

int main() {
    int n;
    std::scanf("%d", &n);

    char board[9][10];
    for (int i = 0; i < n; ++i) {
        std::scanf("%9s", board[i]);
    }

    int q;
    std::scanf("%d", &q);
    while (q--) {
        int x, y;
        std::scanf("%d %d", &x, &y);
        --x;
        --y;

        if (board[x][y] != '0') {
            std::printf("1\n%c\n", board[x][y]);
            continue;
        }

        bool used[10] = {};
        for (int i = 0; i < n; ++i) {
            used[board[x][i] - '0'] = true;
            used[board[i][y] - '0'] = true;
        }

        int digits[9];
        int count = 0;
        for (int digit = 1; digit <= n; ++digit) {
            if (!used[digit]) {
                digits[count++] = digit;
            }
        }

        std::printf("%d\n", count);
        for (int i = 0; i < count; ++i) {
            std::printf("%d%c", digits[i], i + 1 == count ? '\n' : ' ');
        }
    }

    return 0;
}
