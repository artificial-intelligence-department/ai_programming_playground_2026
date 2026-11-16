#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);

    int mas[9][9];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            scanf(" %c", &c);
            mas[i][j] = c - '0';
        }
    }

    int zapit;
    scanf("%d", &zapit);

    while (zapit != 0) {
        zapit--;
        int x, y;
        scanf("%d %d", &x, &y);
        x--;
        y--;

        if (mas[x][y] != 0) {
            printf("1\n%d\n", mas[x][y]);
            continue;
        }

        int nums[9];
        for (int b = 0; b < n; b++) {
            nums[b] = b + 1;
        }

        int count = 0;
        for (int b = 0; b < n; b++) {
            int a = mas[x][b];
            if (a != 0 && nums[a - 1] != 0) {
                nums[a - 1] = 0;
                count++;
            }

            a = mas[b][y];
            if (a != 0 && nums[a - 1] != 0) {
                nums[a - 1] = 0;
                count++;
            }
        }

        printf("%d\n", n - count);

        bool first = true;
        for (int b = 0; b < n; b++) {
            if (nums[b] != 0) {
                if (!first) {
                    printf(" ");
                }
                printf("%d", nums[b]);
                first = false;
            }
        }
        printf("\n");
    }

    return 0;
}