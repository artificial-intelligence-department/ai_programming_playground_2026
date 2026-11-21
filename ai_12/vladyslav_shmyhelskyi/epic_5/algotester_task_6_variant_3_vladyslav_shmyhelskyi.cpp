
#include <stdio.h>
using namespace std;

void sort(int x, int y, int N, int **arr)
{

    if (arr[x][y] != 0)
    {
        printf("1\n");
        printf("%d\n", arr[x][y]);
        return;
    }

    int number[10]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < N; i++)
    {
        int numberRow = arr[x][i];
        number[numberRow] = 1;

        int numberCol = arr[i][y];
        number[numberCol] = 1;
    }

    int count = 0;
    for (int j = 1; j < N + 1; j++)
    {
        if (number[j] == 0)
        {
            count++;
        }
    }

    if (count == 0)
    {
        printf("0\n");
        return;
    }

    printf("%d\n", count);

    for (int j = 1; j < N + 1; j++)
    {
        if (number[j] == 0)
        {
            printf("%d ", j);
        }
    }

    printf("\n");
}

int main()
{
    int N;
    scanf("%d", &N);

    int **arr = new int *[N];

    for (int i = 0; i < N; i++)
    {
        arr[i] = new int[N];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            char c;
            scanf(" %c", &c);
            arr[i][j] = c - '0';
        }
    }

    int Q;
    scanf("%d", &Q);

    int (*cord)[2] = new int[Q][2];

    for (int i = 0; i < Q; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            scanf("%d", &cord[i][j]);
        }
    }

    for (int i = 0; i < Q; i++)
    {
        sort(cord[i][0] - 1, cord[i][1] - 1, N, arr);
    }

    for (int i = 0; i < N; i++)
    {
        delete[] arr[i];
    }

    delete[] arr;
    delete[] cord;

    return 0;
}
