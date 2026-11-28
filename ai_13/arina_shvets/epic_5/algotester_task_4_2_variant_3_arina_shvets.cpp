#include <cstdio>

using namespace std;

const int MAX_N = 1000;
int groups[3][MAX_N];
int sizes[3] = {0, 0, 0};
int buffer[MAX_N];
int result[MAX_N];

void mergeSort(int a[], int left, int right, bool ascending){
    if (right - left <= 1){
        return;
    }
    int middle = left + (right - left) / 2;
    mergeSort(a, left, middle, ascending);
    mergeSort(a, middle, right, ascending);

    int i = left, j = middle, k = left;
    while (i < middle && j < right){
        if (ascending ? a[i] <= a[j] : a[i] >= a[j]){
            buffer[k++] = a[i++];
        } else{
            buffer[k++] = a[j++];
        }
    }
    while (i < middle){
        buffer[k++] = a[i++];
    }
    while (j < right){
        buffer[k++] = a[j++];
    }
    for (int p = left; p < right; ++p){
        a[p] = buffer[p];
    }
}

int main(){
    int n;
    if (scanf("%d", &n) != 1){
        return 0;
    }

    for (int i = 0; i < n; ++i){
        int x;
        scanf("%d", &x);
        int remainder = x % 3;
        groups[remainder][sizes[remainder]++] = x;
    }

    mergeSort(groups[0], 0, sizes[0], true);
    mergeSort(groups[1], 0, sizes[1], false);
    mergeSort(groups[2], 0, sizes[2], true);

    int count = 0;
    for (int r = 0; r < 3; ++r){
        for (int i = 0; i < sizes[r]; ++i){
            int value = groups[r][i];
            if (count == 0 || value != result[count - 1]){
                result[count++] = value;
            }
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; ++i){
        if (i > 0){
            printf(" ");
        }
        printf("%d", result[i]);
    }
    printf("\n");
    return 0;
}