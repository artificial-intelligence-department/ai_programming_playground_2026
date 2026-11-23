#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

int main()
{
    int N, K;
    scanf("%d", &N);
    scanf("%d", &K);
    vector<int> a(N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
    }
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end()); // спочатку сортуємо бо unique працює лише з сусідніми елементами
    N = a.size();
    if (N > 0)
    {
        K = K % N;
        rotate(a.begin(), a.begin() + K, a.end());
    }
    printf("%d \n", N);
    for (int i = 0; i < N; i++)
    {
        printf("%d ", a[i]);
    }
}