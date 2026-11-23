#include <stdio.h>

int main()
{
    int N;
    scanf("%d", &N);

    char a[10][11];

    for (int i = 0; i < N; i++)
    {
        scanf("%9s", a[i]);
    }

    int Q;
    scanf("%d", &Q);

    for (int q = 0; q < Q; q++)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        x--;
        y--;

        if (a[x][y] != '0')
        {
            printf("1\n");
            printf("%c\n", a[x][y]);
            continue;
        }

        int possible[9];
        int count = 0;

        for (int digit = 1; digit <= N; digit++)
        {
            char c = '0' + digit;
            bool ok = true;

            for (int i = 0; i < N; i++)
            {
                if (a[x][i] == c || a[i][y] == c)
                {
                    ok = false;
                    break;
                }
            }

            if (ok)
            {
                possible[count] = digit;
                count++;
            }
        }

        printf("%d\n", count);

        if (count > 0)
        {
            for (int i = 0; i < count; i++)
            {
                if (i > 0)
                {
                    printf(" ");
                }

                printf("%d", possible[i]);
            }

            printf("\n");
        }
    }

    return 0;
}