
// Гра в боулінг
#include <iostream>
using namespace std;

void merge(long long a[], long long temp[], int left, int right, int mid)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (a[i] <= a[j])
        {
            temp[k] = a[i];
            i++;
        }
        else
        {
            temp[k] = a[j];
            j++;
        }
        k++;
    }
    while (i <= mid)
    {
        temp[k] = a[i];
        i++;
        k++;
    }
    while (j <= right)
    {
        temp[k] = a[j];
        k++;
        j++;
    }
    for (int x = left; x <= right; x++)
    {
        a[x] = temp[x];
    }
}
void sort(long long a[], long long temp[], int left, int right)
{

    if (left >= right)
    {
        return;
    }
    int mid = (right + left) / 2;
    sort(a, temp, left, mid);
    sort(a, temp, mid + 1, right);
    merge(a, temp, left, right, mid);
}

int main()
{
    int n;
    cin >> n;
    long long a[n];
    long long temp[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, temp, 0, n - 1);
    long long count = 0;
    int k;

    for (int i = 2; i < n; i++)
    {
        k = i - 1;
        int j = 0;
        while (j < k)
        {
            long long sum = a[j] + a[k];

            if (sum < a[i])
            {
                j++;
            }
            else if (sum > a[i])
            {
                k--;
            }
            else
            {
                if (a[j] == a[k])
                {
                    long long m = k - j + 1;
                    count += m * (m - 1) / 2;
                    break;
                }
                else
                {
                    long long countLeft = 1;
                    long long countRight = 1;
                    while (j + 1 < k && a[j] == a[j + 1])
                    {
                        countLeft++;
                        j++;
                    }
                    while (k - 1 > j && a[k] == a[k - 1])
                    {
                        countRight++;
                        k--;
                    }
                    count += countLeft * countRight;

                    j++;
                    k--;
                }
            }
        }
    }
    cout << count;
    return 0;
}