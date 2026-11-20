/* 
Алготестер 4, варіант 2
Зубак Тетяна
ШІ-12
*/
#include <cstdio>

int main() {
    int N = 0, K = 0;
    scanf("%i %i", &N, &K);

    int arr0[N];
    for (int i = 0; i < N; i++) {
        scanf("%i", &arr0[i]);
    }

    for (int i = 0; i < N - 1; i++) {
        for (int k = 0; k < N - 1 - i; k++) {
            if (arr0[k] > arr0[k + 1]) {
                int tmp = arr0[k];
                arr0[k] = arr0[k + 1];
                arr0[k + 1] = tmp;
            }
        }
    }

    int arr[N];
    int j = 0;
    for (int i = 0; i < N; i++) {
        if (i == N - 1 || arr0[i] != arr0[i + 1]) arr[j++] = arr0[i];
    }
    int M = j;

    K %= M;

    printf("%i\n", M);
    for (int i = 0; i < M; i++) {
        printf("%i", arr[(K + i) % M]);
        if (i < M - 1) printf(" ");
    }
    printf("\n");

    return 0;
}