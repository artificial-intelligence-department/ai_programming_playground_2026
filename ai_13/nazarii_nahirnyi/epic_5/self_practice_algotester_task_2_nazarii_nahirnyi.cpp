#include <cstdio>
#include <cstring>

char s[500005], t[500005];

bool ok(int pos, int m) {
    return strncmp(s + pos, t, m) == 0;
}

int main() {
    int tests;
    scanf("%d", &tests);

    while (tests--) {
        scanf("%s %s", s, t);

        int n = strlen(s);
        int m = strlen(t);
        int k = n - m;
        int mid = k / 2;
        bool win = false;

        if (k == 0) {
            win = ok(0, m);
        } else if (k % 2 == 1) {
            win = ok(mid, m) && ok(mid + 1, m);
        } else if (k > 0) {
            win = ok(mid, m) || (ok(mid - 1, m) && ok(mid + 1, m));
        }

        if (win) {
            printf("Sergei\n");
        } else {
            printf("Larry\n");
        }
    }

    return 0;
}