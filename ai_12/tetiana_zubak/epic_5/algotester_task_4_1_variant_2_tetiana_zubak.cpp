/* 
Алготестер 4, варіант 2
Зубак Тетяна
ШІ-12
*/
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    int N = 0, K = 0;
    scanf("%i %i", &N, &K);

    int arr0[N];
    for (int i = 0; i < N; i++) {
        scanf("%i", &arr0[i]);
    }

    sort(arr0, arr0 + N);

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

    return 0;
}