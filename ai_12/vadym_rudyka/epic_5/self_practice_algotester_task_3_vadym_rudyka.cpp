#include <cstdio>

char s[100005];
char t[100005];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    scanf("%s", s);
    scanf("%s", t);

    long long s4 = 0, s7 = 0, t4 = 0, t7 = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '4') s4++;
        else s7++;
    }

    for (int i = 0; i < m; i++) {
        if (t[i] == '4') t4++;
        else t7++;
    }

    long long total = (long long)(n + 1) * (m + 1);
    long long dup = s4 * t4 + s7 * t7;

    printf("%lld\n", total - dup - 1);

    return 0;
}