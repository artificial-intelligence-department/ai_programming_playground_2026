/*
Задача: Lab 4v2 (no stl)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>

using namespace std;

void bubbleSort(int* arr, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

int main()
{
    int N, K;
    cin >> N >> K;

    int *a = new int[N];

    for(int i = 0; i < N; i++)
    {
        cin >> a[i];
    }

    bubbleSort(a, N);

    int new_N = 1;
    for(int i = 1; i < N; i++)
    {
        if(a[i] != a[new_N - 1])
        {
            a[new_N] = a[i];
            new_N++;
        }
    }

    N = new_N;

    int *new_a = new int[N];

    for(int i = 0; i < N; i++)
    {
        new_a[i] = a[i];
    }

    delete[] a;
    a = new_a;

    K = K % N;

    new_a = new int[N];

    int k = 0;
    for(int i = K; i < N; i++)
    {
        new_a[k] = a[i];
        k++;
    }
    for(int i = 0; i < K; i++)
    {
        new_a[k] = a[i];
        k++;
    }

    delete[] a;
    a = new_a;

    cout << N << '\n';

    for(int i = 0; i < N; i++)
    {
        cout << a[i] << " ";
    }

    cout << '\n';

    delete[] a;

    return 0;
}
