#include <iostream>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    int *a = new int[n];
    for(int i = 0; i < n; i++)
    cin >> a[i];
    int b[1000] = {-1};
    int q = 0;
    for(int i = 0; i < n; i++)
    {
        bool m = true;
        for(int j = 0; j < 1000; j++)
        {
            if(a[i] == b[j])
            m = false;
        }
        if(m)
        {
            b[q] = a[i];
            q++;
        }
    }
    delete[] a;
    for(int i = 0; i < q - 1; i++)
    {
        for(int j = 0; j < q - i - 1; j++)
        {
            if(b[j] > b[j + 1])
            {
                int t = b[j];
                b[j] = b[j + 1];
                b[j + 1] = t;
            }
        }
    }
    k = k % q;
    int *c = new int[k];
    for(int i = 0; i < k; i++)
    c[i] = b[i];
    for(int i = k; i < q; i++)
    b[i - k] = b[i];
    for(int i = q - k; i < q; i++)
    b[i] = c[i - q + k];
    delete[] c;
    cout << q << endl;
    for(int i = 0; i < q; i++)
    cout << b[i] << " ";
    return 0;
}