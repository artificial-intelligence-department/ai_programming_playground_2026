#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    int total = n * m;
    int* arr = new int[total];

    for (int i = 0; i < total; i++)
    {
        cin >> arr[i];
    }

    sort(arr, arr + total);

    int *dublicat = new int[total / 2];

    int totalCount = 0;

    for (int i = 0; i < total - 1; i++)
    {
        if (arr[i] == arr[i + 1])
        {
            dublicat[totalCount] = arr[i];
            totalCount++;
            i++;
        }
    }

    cout << totalCount << endl;
    for (int i = 0; i < totalCount; i++)
    {
        cout << dublicat[i] << " ";
    }

    delete[] arr;
    delete[] dublicat;
    return 0;
}