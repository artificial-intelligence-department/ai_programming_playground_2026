#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);

    int r = n % 7;
    if ((r != 1 && r != 2 && r != 4) || n == 2 || n == 9) {
        printf("-1\n");
        return 0;
    }

    int steps = 0;
    while (n > 1) {
        if (n % 4 == 0 && n != 8 && n != 36) {
            n /= 4;
        } else {
            n -= 7;
        }
        steps++;
    }

    printf("%d\n", steps);
    return 0;
}