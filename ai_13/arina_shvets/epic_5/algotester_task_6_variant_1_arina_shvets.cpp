#include <cstdio>
#include <cstring>
#include <cctype>

using namespace std;

const int MAX_N = 100000;
char words[MAX_N][11];
char temporary[MAX_N][11];

void mergeSort(int left, int right){
    if (right - left <= 1){
        return;
    }
    const int middle = left + (right - left) / 2;
    mergeSort(left, middle);
    mergeSort(middle, right);

    int i = left, j = middle, k = left;
    while (i < middle && j < right){
        if (strcmp(words[i], words[j]) <= 0){
            strcpy(temporary[k++], words[i++]);
        } else{
            strcpy(temporary[k++], words[j++]);
        }
    }
    while (i < middle){
        strcpy(temporary[k++], words[i++]);
    }
    while (j < right){
        strcpy(temporary[k++], words[j++]);
    }
    for (int p = left; p < right; ++p){
        strcpy(words[p], temporary[p]);
    }
}

int main(){
    int n, k;
    if (scanf("%d %d", &n, &k) != 2){
        return 0;
    }

    for (int i = 0; i < n; ++i){
        scanf("%10s", words[i]);
        for (int j = 0; words[i][j] != '\0'; ++j){
            unsigned char c = static_cast<unsigned char>(words[i][j]);
            words[i][j] = static_cast<char>(tolower(c));
        }
    }

    mergeSort(0, n);

    bool used[26] = {false};
    for (int i = 0; i < n; ){
        int j = i + 1;
        while (j < n && strcmp(words[i], words[j]) == 0){
            ++j;
        }

        if (j - i >= k){
            for (int p = 0; words[i][p] != '\0'; ++p){
                used[words[i][p] - 'a'] = true;
            }
        }
        i = j;
    }

    int count = 0;
    for (int i = 0; i < 26; ++i){
        if (used[i]){
            ++count;
        }
    }

    if (count == 0){
        printf("Empty!\n");
        return 0;
    }

    printf("%d\n", count);
    bool first = true;
    for (int i = 25; i >= 0; --i){
        if (!used[i]){
            continue;
        }
        if (!first){
            printf(" ");
        }
        printf("%c", 'a' + i);
        first = false;
    }
    printf("\n");
    return 0;
}