
#include <cstdio>
#include <cstring>

int main() {
    int n;
    char c;
    scanf("%d %c", &n, &);

    char s[100001];
    char temp[100001];
    char res[100001];

    for (int i = 0; i < n; i++) {
        scanf("%s", s);
        int j = 0;
        int k = 0;

        while (s[j] != '\0' && s[j] <= c) {
            temp[k] = s[j];
            j++;
            k++;
        }

        temp[k] = c;
        k++;
        while (s[j] != '\0') {
            temp[k] = s[j];
            j++;
            k++;
        }

        temp[k] = '\0';
        if (strcmp(temp, res) < 0) {
            strcpy(res, temp);
        }
    }
    printf("%s\n", res);

    return 0;
}