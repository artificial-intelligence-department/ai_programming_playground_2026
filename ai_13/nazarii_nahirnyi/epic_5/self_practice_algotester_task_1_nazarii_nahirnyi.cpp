#include <cstdio>
#include <cstring>

char t[100005], s[100005];
long long cnt[26];

int main() {
    scanf("%s %s", t, s);

    int n = strlen(t);
    int m = strlen(s);

    if (n < m) {
        printf("0\n");
        return 0;
    }

    for (int i = 0; i <= n - m; i++) {
        int index = t[i] - 'a';
        cnt[index]++;
    }

    long long ans = 0;
    for (int i = 0; i < m; i++) {
        int index = s[i] - 'a';
        ans += (i + 1) * cnt[index];

        cnt[t[i] - 'a']--;

        if (i + 1 < m) {
            cnt[t[n - m + i + 1] - 'a']++;
        }
    }

    printf("%lld\n", ans);
    return 0;
}