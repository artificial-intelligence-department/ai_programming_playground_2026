#include <iostream>
#include <string.h>
using namespace std;

int main()
{

    int N, K;
    scanf("%d", &N);
    scanf("%d", &K);
    int a[N];
    int copya[N];

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
    }
    memcpy(copya, a, N * sizeof(int));

    int flag = -1000;
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {

        for (int j = 0; j < i; j++)
        {
            if (a[i] == copya[j] && j != i)
            {
                a[i] = flag;
                cnt++;
                break;
            }
        }
    }
    int j = 0;
    for (int i = 0; i < N; i++)
    {
        if (a[i] != flag)
        {
            a[j] = a[i];
            j++;
        }
    }
    for (int i = 0; i < j; i++)
    {
        for (int k = i + 1; k < j; k++)
        {
            if (a[i] > a[k])
            {
                int temp = a[i];
                a[i] = a[k];
                a[k] = temp;
            }
        }
    }
    K = K % j;
    memcpy(copya, a, j * sizeof(int));
    for (int i = 0; i < K; i++)
    {
        a[j - K + i] = copya[i];
    }
    for (int i = 0; i < j - K; i++)
    {
        a[i] = copya[i + K];
    }
    printf("%d \n", j);

    for (int i = 0; i < j; i++)
    {
        printf("%d ", a[i]);
    }
}