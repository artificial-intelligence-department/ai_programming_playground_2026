#include <cstdio>

const int MAXN = 100001;

int n, q;
char s[MAXN];

int main() {
    scanf("%d %d", &n, &q);
    scanf("%s", s + 1);

    while (q-- > 0) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            int p;
            char c;
            scanf("%d %c", &p, &c);
            s[p] = c;
        } else {
            int l, r;
            scanf("%d %d", &l, &r);
            int w = r - l + 2;
            if (w > 33) w = 33;
            int v[33];
            v[0] = 0;
            for (int k = 1; k < w; k++)
                v[k] = v[k - 1] ^ (s[l + k - 1] - 'a' + 1);

            int best = 1000, bi = 0, bj = 1;
            for (int i = 0; i < w && best != 0; i++) {
                for (int j = i + 1; j < w; j++) {
                    int x = v[i] ^ v[j];
                    if (x < best) {
                        best = x;
                        bi = i;
                        bj = j;
                        if (best == 0) break;
                    }
                }
            }
            printf("%d %d\n", l + bi, l - 1 + bj);
        }
    }
    return 0;
}