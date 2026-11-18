#include <iostream>
using namespace std;
int main()
{
    bool seen[101] = {false};
    int n;
    int k;
    cin >> n >> k;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        seen[a[i]] = true;
    }
    int newBLen = 0;
    int b[101];
    for (int v = 0; v <= 100; v++)
    if (seen[v]) {
        b[newBLen] = v;
        newBLen++;
    }
    int tempBLen = newBLen;
    cout << newBLen << endl;

    for (int i = k % newBLen; i < newBLen; i++)
    {
        cout << b[i] << " ";
    }
    for (int i = 0; i < k % newBLen; i++)
    {
        cout << b[i] << " ";
    }
}
    
