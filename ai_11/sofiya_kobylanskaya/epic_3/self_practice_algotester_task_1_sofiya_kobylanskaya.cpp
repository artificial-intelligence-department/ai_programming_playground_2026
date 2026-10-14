/*
Epic 3
Self Practice Task Кобилянська Софія ШІ-11
"Найбільша зростаюча підпослідовність"
*/

#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    int a[100];
    int dp[100];

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        dp[i] = 1;
    }

    int maximum = 1;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j] < a[i])
            {
                if (dp[j] + 1 > dp[i])
                {
                    dp[i] = dp[j] + 1;
                }
            }
        }

        if (dp[i] > maximum)
        {
            maximum = dp[i];
        }
    }

    cout << maximum;

    return 0;
}
