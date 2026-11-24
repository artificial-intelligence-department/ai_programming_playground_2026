#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    int n, i, j; char c;
    scanf("%d", &n);
    scanf(" %c", &c);

    char *t = new char[100002];  
    char *cand = new char[100003];  
    char *best = new char[100003];   

    for (i = 0; i < n; i++) {
        scanf("%s", t);
        int len = strlen(t);

        int pos = len;
        for (j = 0; j < len; j++) {
            if (t[j] > c) {
                pos = j;
                break;
            }
        }

        for (j = 0; j < pos; j++) cand[j] = t[j];
        cand[pos] = c;
        for (j = pos; j < len; j++) cand[j + 1] = t[j];
        cand[len + 1] = '\0';

        if (i == 0 || strcmp(cand, best) < 0) {
            strcpy(best, cand);
        }
    }

    printf("%s\n", best);

    delete[] t;
    delete[] cand;
    delete[] best;
    return 0;
}