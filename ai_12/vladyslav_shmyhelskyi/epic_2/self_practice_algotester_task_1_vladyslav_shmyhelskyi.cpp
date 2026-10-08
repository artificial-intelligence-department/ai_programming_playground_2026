// "Солодкі цукерки"

#include <iostream>
using namespace std;

int t[100001];
int cnt[100001];
int main()
{


    int n, k;

    cin >> n >> k;

    for (int i = 0; i < n; i++)
    {
        cin >> t[i];
        cnt[t[i]]++;
    }
    int target = -1;

    for (int i = 0; i < n; i++)
    {
        if (cnt[t[i]] >= k)
        {
            target = t[i];
            break;
        }
    }
    if (target == -1)
    {
        cout << "Oh sh*t";
        return 0;
    }

    for (int i = 0; i < cnt[target]; i++)
    {
        cout << target << " ";
    }
    for (int i = 0; i < n; i++)
    {
        if (t[i] != target)
        {
            cout << t[i] << " ";
        }
    }
}