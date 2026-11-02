#include <iostream>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    if (n < k || n > 3 * k)
    {
        cout << "Impossible";
        return 0;
    }
    int *arr = new int[k]();

    for (int i = 0; i < k; i++)
    {
        arr[i]++;
    }
    int remaining = n - k;

    for (int i = 0; i < k && remaining > 0; i++)
    {
        while (arr[i] < 3 && remaining > 0)
        {
            arr[i]++;
            remaining--;
        }
        if (i == k - 1)
        {
            i = -1;
        }
    }

    for (int i = 0; i < k; i++)
    {
        cout << arr[i] << " ";
    }
    delete[] arr;
    return 0;
}