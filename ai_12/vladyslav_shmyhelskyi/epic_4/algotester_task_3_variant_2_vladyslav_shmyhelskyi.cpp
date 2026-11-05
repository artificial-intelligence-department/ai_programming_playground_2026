#include <iostream>
using namespace std;

int main()
{
    int N;
    cin >> N;
    int arrN[N];
    for (int i = 0; i < N; i++)
    {
        cin >> arrN[i];
    }
    int M;
    cin >> M;

    int arrM[M];
    for (int i = 0; i < M; i++)
    {
        cin >> arrM[i];
    }

    int cntCommon = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (arrN[i] == arrM[j])
            {
                cntCommon++;
            }
        }
    }
    int unic = (N + M) - cntCommon;
    cout << cntCommon << endl;
    cout << unic;
}