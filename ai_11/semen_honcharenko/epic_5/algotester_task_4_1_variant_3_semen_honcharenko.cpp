/*
    Лабораторна робота Алготестер. Завдання 4_1. Варіант 3.
    Гончаренко Семен
    ШІ-11
*/
#include <cstdio>
#include <algorithm>
using namespace std;

bool isRemain_1(int x) {
    return x % 3 == 0;
}

bool isRemain_2(int x) {
    return x % 3 == 1;
}

int main() {
    int N = 0;
    int a[1000];
    int M = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    auto end1 = partition(a, a + N, isRemain_1);
    auto end2 = partition(end1, a + N, isRemain_2);

    sort(a, end1);
    sort(end1, end2);
    reverse(end1, end2);
    sort(end2, a + N);

    M = unique(a, a + N) - a;

    printf("%d\n", M);
    for (int i = 0; i < M; i++) {
        printf("%d", a[i]);
        if (i < M - 1) {
            printf(" ");
        }
    }
    printf("\n");
    return 0;
}