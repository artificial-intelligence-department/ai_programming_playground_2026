
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char words[100000][11];
int idx[100000];
int tmp[100000];

void mergeSort(int l, int r) {
    if (l >= r) {
        return;
    }

    int m = (l + r) / 2;
    mergeSort(l, m);
    mergeSort(m + 1, r);

    int i = l;
    int j = m + 1;
    int k = l;

    while (i <= m && j <= r) {
        if (strcmp(words[idx[j]], words[idx[i]]) < 0) {
            tmp[k] = idx[j];
            j++;
        } else {
            tmp[k] = idx[i];
            i++;
        }
        k++;
    }
    while (i <= m) {
        tmp[k] = idx[i];
        i++;
        k++;
    }
    while (j <= r) {
        tmp[k] = idx[j];
        j++;
        k++;
    }

    for (int p = l; p <= r; p++) {
        idx[p] = tmp[p];
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; i++) {
        scanf("%10s", words[i]);
        for (int j = 0; words[i][j] != '\0'; j++) {
            words[i][j] = tolower(words[i][j]);
        }
        idx[i] = i;
    }

    mergeSort(0, n - 1);

    int used[26] = {0};

    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && strcmp(words[idx[j]], words[idx[i]]) == 0) {
            j++;
        }
        int cnt = j - i;
        if (cnt >= k) {
            char *w = words[idx[i]];
            for (int p = 0; w[p] != '\0'; p++) {
                used[w[p] - 'a'] = 1;
            }
        }
        i = j;
    }

    int total = 0;
    for (int c = 0; c < 26; c++) {
        total += used[c];
    }

    if (total == 0) {
        printf("Empty!\n");
    } else {
        printf("%d\n", total);
        int first = 1;
        for (int c = 25; c >= 0; c--) {
            if (used[c]) {
                if (!first) {
                    printf(" ");
                }
                printf("%c", 'a' + c);
                first = 0;
            }
        }
        printf("\n");
    }
    return 0;
}