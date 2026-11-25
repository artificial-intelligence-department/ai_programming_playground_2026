/*
Задача: Сет
*/
#include <cstdio>
int main(){
    int n;
    scanf("%d", &n);
    int count[81] = {0};
    char card[5];
    char types[81][5];
    char options[4][4] = {"123", "RGB", "FPE", "DSO"};
    for(int i = 0; i < n; i++){
        scanf("%4s", card);
        int id = 0;
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 3; k++){
                if(card[j] == options[j][k]){
                    id = id * 3 + k;
                    break;
                }
            }
        }
        count[id]++;
        for(int t = 0; t < 5; t++){
            types[id][t] = card[t];
        }
    }
    long long answer = 0;
    for(int a = 0; a < 81; a++){
        int m = count[a];
        if(m >= 3){
            answer += 1LL * m * (m - 1) * (m - 2) / 6;
        }
    }
    for(int a = 0; a < 81; a++){
        if(count[a] == 0) continue;
        for(int b = a + 1; b < 81; b++){
            if(count[b] == 0) continue;
            for(int c = b + 1; c < 81; c++){
                if(count[c] == 0) continue;
                bool ok = true;
                for(int p = 0; p < 4; p++){
                    bool same = types[a][p] == types[b][p] && types[b][p] == types[c][p];
                    bool difference = types[a][p] != types[b][p] && types[a][p] != types[c][p] && types[b][p] != types[c][p];
                    if(!same && !difference){
                        ok = false;
                        break;
                    }
                }
                if(ok){
                    answer += 1LL * count[a] * count[b] * count[c];
                }

            }
        }
    }
    printf("%lld\n", answer);
    return 0;
}