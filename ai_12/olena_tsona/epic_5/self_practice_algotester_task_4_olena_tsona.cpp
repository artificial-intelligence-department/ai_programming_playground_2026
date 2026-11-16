#include <cstdio>
#include <cstring>

char s[100005];

int main() {
    int k;
    scanf("%d %100000s", &k, s);

    int count = 0;
    char *p = strstr(s, "TOILET");

    while (p != NULL) {
        count++;
        p = strstr(p + 6, "TOILET");
    }

    if (count >= k) printf("YES\n");
    else printf("NO\n");

    return 0;
}