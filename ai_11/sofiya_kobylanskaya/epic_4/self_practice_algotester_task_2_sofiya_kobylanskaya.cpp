// "Цікавий масив"
#include <iostream>
using namespace std;
int sumArray(int *p, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum = sum + *(p + i);
    }
    return sum;
}
int main()
{
    int n;
    if (!(cin >> n) || n < 2 || n > 100)
    {
        return 0;
    }
    int a[100];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] < 1 || a[i] > 1000)
        {
            return 0;
        }
    }
    bool answer = false;
    for (int k = 1; k < n; k++)
    {
        int sumK = sumArray(a, k);
        int sumOther = sumArray(a + k, n - k);
        if (sumK == sumOther)
        {
            answer = true;
            break;
        }
    }
    if (answer == true) {
        cout << "TAK" << endl;
    }
    else {
        cout << "NI" << endl;
    }
        return 0;
}