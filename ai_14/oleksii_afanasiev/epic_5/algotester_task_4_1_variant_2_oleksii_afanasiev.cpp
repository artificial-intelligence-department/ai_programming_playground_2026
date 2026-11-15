/*
Задача: Lab 4v2 (stl)
Виконав: Афанасьєв Олексій (ШІ-14)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N, K;
    cin >> N >> K;

    int *a = new int[N];

    for(int i = 0; i < N; i++)
    {
        cin >> a[i];
    }

    sort(a, a + N);

    int* new_end = unique(a, a + N);
    int new_N = new_end - a;

    int *new_a = new int[new_N];
    for(int i = 0; i < new_N; i++)
    {
        new_a[i] = a[i];
    }

    delete[] a;
    a = new_a;
    N = new_N;

    K = K % N;
    rotate(a, a + K, a + N);

    cout << N << endl;

    for(int i = 0; i < N; i++)
    {
        cout << a[i] << " ";
    }

    return 0;
}
