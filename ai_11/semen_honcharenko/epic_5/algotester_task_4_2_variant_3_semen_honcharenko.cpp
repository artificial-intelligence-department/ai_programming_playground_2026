/*
    Лабораторна робота Алготестер. Завдання 4_2. Варіант 3.
    Гончаренко Семен
    ШІ-11
*/
#include <cstdio>
using namespace std;

bool compare(int x, int y) {
    int x_remain = x % 3;
    int y_remain = y % 3;

    if (x_remain != y_remain) {
        return x_remain < y_remain;
    }
    if (x_remain == 1) {
        return x > y;
    }
    return x < y;
}

int a[1000];
int temp[1000];

void mergeSort(int left, int right) {
    if (right - left < 2) {
        return;
    }
    int mid = (left + right) / 2;
    mergeSort(left, mid);
    mergeSort(mid, right);

    int i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (compare(a[j], a[i])) {
            temp[k] = a[j];
            k++;
            j++;
        }
        else {
            temp[k] = a[i];
            k++;
            i++;
        }
    }
    while (i < mid) {
        temp[k] = a[i];
        k++;
        i++;
    }
    while (j < right) {
        temp[k] = a[j];
        k++;
        j++;
    }
    for (int t = left; t < right; t++) {
        a[t] = temp[t];
    }
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    mergeSort(0, N);

    int M = 1;
    for (int i = 1; i < N; i++) {
        if (a[i] != a[M - 1]) {
            a[M] = a[i];
            M++;
        }
    }

    printf("%d\n", M);
    for (int i = 0; i < M; i++) {
        printf("%d", a[i]);
        if (i < M - 1) printf(" ");
    }
    printf("\n");
    return 0;
}