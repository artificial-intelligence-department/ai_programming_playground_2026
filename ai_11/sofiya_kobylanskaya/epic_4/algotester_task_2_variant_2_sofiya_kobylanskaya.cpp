#include <iostream>
using namespace std;

int N;
int r[100000];
int R[100000];
int sum[100000];
int a, b, c;
int sumCount = 0;

int main()
{
    cin >> N;
    if (N < 1 || N > 100000)
    {
        return 0;
    }
    for (int i = 0; i < N; i++)
    {
        cin >> r[i];
        if (r[i] < 0 || r[i] > 100000)
        {
            return 0;
        }
    }
    cin >> a >> b >> c;
    if (a < 0 || a > 100000 || b < 0 || b > 100000 || c < 0 || c > 100000)
    {
        return 0;
    }
    int j = 0;
    for (int i = 0; i < N; i++)
    {
        if (r[i] != a && r[i] != b && r[i] != c)
        {
            R[j] = r[i];
            j++;
        }
    }
    for (int i = 0; i < j - 1; i++)
    {
        sum[i] = R[i] + R[i + 1];
        sumCount++;
    }
    cout << sumCount << endl;
    for (int i = 0; i < sumCount; i++)
    {
        cout << sum[i] << " ";
    }
    cout << endl;
    return 0;
}