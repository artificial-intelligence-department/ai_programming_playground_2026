//Буквозабирання

#include <cstdio>
#include <cstring>

char s[500005], t[500005];

int L, M, d;

bool check(int p) {
    if (p < 0 || p > d) {
        return false;
    }

    for (int i = 0; i < M; ++i) {
        if (s[p + i] != t[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int tests;
    scanf("%d", &tests);
    while (tests--) {
        scanf("%s %s", s, t);
        L = strlen(s);
        M = strlen(t);
        d = L - M;

        bool sergei;
        if (d == 0) {
            sergei = check(0);
        } else if (d % 2 == 1) {
            int j = (d - 1) / 2;
            sergei = check(j) && check(j + 1);
        } else {
            int c = d / 2;
            sergei = check(c) || (check(c - 1) && check(c + 1));
        }

        if (sergei)
            printf("Sergei\n");
        else
            printf("Larry\n");
    }
    return 0;
}