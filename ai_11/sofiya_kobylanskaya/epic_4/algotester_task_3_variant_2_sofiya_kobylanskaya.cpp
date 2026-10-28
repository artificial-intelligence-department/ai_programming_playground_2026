#include <iostream>
using namespace std;

int N;
int M;
int a[100];
int b[100];
int sameCount = 0;
int unicCount = 0;

int main()
{
    cin >> N;
    if (N < 0 || N > 100)
    {
        return 0;
    }
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }
    cin >> M;
    if (M < 0 || M > 100)
    {
        return 0;
    }
    for (int i = 0; i < M; i++)
    {
        cin >> b[i];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (a[i] == b[j])
            {
                sameCount++;
            }
        }
    }
    unicCount = N + M - sameCount;
    cout << sameCount << endl;
    cout << unicCount << endl;
    return 0;
}