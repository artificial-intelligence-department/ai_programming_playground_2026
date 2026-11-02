#include <iostream>
using namespace std;

int main()
{
    int N, M;

    cin >> N;
    int *arr = new int[N];
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    cin >> M;
    int *arr2 = new int[M];
    for (int i = 0; i < M; i++)
    {
        cin >> arr2[i];
    }

    int simCounter = 0;
    

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (arr[i] == arr2[j])
            {
                simCounter++;
            }
        }
    }

    int uniqueCounter = M+N-simCounter;

    cout << simCounter << endl;
    cout << uniqueCounter << endl;

    delete[] arr;
    delete[] arr2;

    return 0;
}