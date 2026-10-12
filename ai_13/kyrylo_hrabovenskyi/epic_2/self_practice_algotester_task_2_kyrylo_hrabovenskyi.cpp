/*

Self practice work Algotester Найбільша зростаюча підпослідовність
Грабовенський Кирило
СШІ-13

*/
#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    if (1 > n || n > 100)
    {

        return 1;

    }

    int A[100];
    int DP[100];

    for (int i = 0; i < n; i++)
    {
        cin >> A[i];
        DP[i] = 1;
    }

    int max_lis = 1;

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (A[j] < A[i])
            {
                if (DP[j] + 1 > DP[i])
                {
                    DP[i] = DP[j] + 1;
                }
            }
        }

        if (DP[i] > max_lis)
        {
            max_lis = DP[i];
        }
    }

    cout << max_lis << "\n";

    return 0;
}
