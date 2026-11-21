#include <cstdio>

int total[50000];
int goldSilver[50000];
int golds[50000];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int gold, silver, bronze;
        scanf("%d %d %d", &gold, &silver, &bronze);

        total[i] = gold + silver + bronze;
        goldSilver[i] = gold + silver;
        golds[i] = gold;
    }

    int best = 0;
    for (int i = 1; i < n; i++) {
        if (total[i] > total[best]) {
            best = i;
        } else if (total[i] == total[best] && goldSilver[i] > goldSilver[best]) {
            best = i;
        } else if (total[i] == total[best] && goldSilver[i] == goldSilver[best] && golds[i] > golds[best]) {
            best = i;
        }
    }

    bool ok = true;
    for (int i = 0; i < n; i++) {
        if (i == best) continue;

        if (total[best] < total[i] ||
            goldSilver[best] < goldSilver[i] ||
            golds[best] < golds[i]) {
            ok = false;
        }

        if (total[best] == total[i] &&
            goldSilver[best] == goldSilver[i] &&
            golds[best] == golds[i]) {
            ok = false;
        }
    }

    if (ok) {
        printf("%d\n", best + 1); 
    } else {
        printf("-1\n");
    }
    return 0;
}