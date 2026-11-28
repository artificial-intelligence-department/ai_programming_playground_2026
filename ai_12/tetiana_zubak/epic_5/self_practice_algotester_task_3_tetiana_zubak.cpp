#include <cstdio>
#include <cstring>

int main() {
    int n;
    char c;
    if (scanf("%d %c", &n, &c) != 2) return 0;

    static char s[100005];
    static char temp[100005];
    static char res[100005];

    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        int j = 0, k = 0;

        while (s[j] != '\0' && s[j] <= c) {
            temp[k++] = s[j++];
        }

        temp[k++] = c;

        while (s[j] != '\0') {
            temp[k++] = s[j++];
        }
        temp[k] = '\0';

        if (i == 0 || strcmp(temp, res) < 0) {
            strcpy(res, temp);
        }
    }

    printf("%s\n", res);
    return 0;
}