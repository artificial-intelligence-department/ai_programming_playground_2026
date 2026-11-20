#include <cstdio>
#include <cstring>

int main() {
    int pre[5001];
    int Min[5001];
    char s[5001];
    scanf("%s", s);
    int n = strlen(s);

    pre[0] = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i - 1] == '(') pre[i] = pre[i - 1] + 1;
        else pre[i] = pre[i - 1] - 1;
    }

    int ok = (pre[n] == 0);
    for (int i = 0; i <= n; i++)
        if (pre[i] < 0) ok = 0;
    if (ok) {
        printf("possible\n");
        return 0;
    }

    Min[n] = pre[n];
    for (int i = n - 1; i >= 0; i--) {
        if (pre[i] < Min[i + 1]) Min[i] = pre[i];
        else Min[i] = Min[i + 1];
    }

    int possible = 0;

    for (int l = 1; l <= n && !possible; l++) {
        if (pre[l - 1] < 0) break;

        int minInside = 2 * pre[l - 1] - pre[l];
        for (int r = l; r <= n; r++) {
            int newh = 2 * pre[l - 1] - pre[r];
            if (newh < minInside) minInside = newh;
            if (minInside < 0) break;

            int delta = 2 * (pre[r] - pre[l - 1]);
            if (pre[n] - delta != 0) continue;
            if (r < n && Min[r + 1] - delta < 0) continue;
            possible = 1;
            break;
        }
    }

    if (possible) printf("possible\n");
    else printf("impossible\n");
    return 0;
}