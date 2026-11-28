/* 
Алготестер 6, варіант 1
Зубак Тетяна
ШІ-12
*/
#include <cstdio>
#include <string>

using namespace std;

string words[100001], tmp[100001];
bool used[26];

void mergeSort(int l, int r){
    if(r - l < 2) return;
    int m = (l + r) / 2;
    mergeSort(l, m);
    mergeSort(m, r);

    int i = l, j = m, k = l;
    while(i < m && j < r){
        if(words[i] <= words[j]) tmp[k++] = words[i++];
        else tmp[k++] = words[j++];
    }
    while(i < m) tmp[k++] = words[i++];
    while(j < r) tmp[k++] = words[j++];
    for(k = l; k < r; k++) words[k] = tmp[k];
}

int main(){
    int N = 0, K = 0, n = 0;
    scanf("%i %i", &N, &K);

    char buf[11];
    for(int i = 0; i < N; i++){
        scanf("%10s", buf);
        words[i] = buf;
        for(int j = 0; j < words[i].size(); j++){
            if(words[i][j] >= 'A' && words[i][j] <= 'Z') words[i][j] += 32;
        }
    }

    mergeSort(0, N);

    for(int i = 0; i < N; ){
        int k = 0;
        while(i + k < N && words[i + k] == words[i]) k++;
        if(k >= K){
            for(int j = 0; j < words[i].size(); j++){
                int c = words[i][j] - 'a';
                if(!used[c]){ used[c] = true; n++; }
            }
        }
        i += k;
    }

    if(n == 0) printf("Empty!");
    else{
        printf("%i\n", n);
        for(int c = 25; c >= 0; c--){
            if(used[c]){
                printf("%c", 'a' + c);
                if(--n > 0) printf(" ");
            }
        }
    }

    return 0;
}