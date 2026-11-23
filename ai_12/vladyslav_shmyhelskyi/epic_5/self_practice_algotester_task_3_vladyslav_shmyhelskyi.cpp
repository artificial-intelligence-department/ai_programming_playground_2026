// Дороги та міста
#include <iostream>
using namespace std;

int findway(int x, int startedWay[])
{
    if (startedWay[x] == x)
    {
        return x;
    }
    return findway(startedWay[x], startedWay);
}

int main()
{
    int n, m;
    cin >> n;
    cin >> m;
    int com = n;
    int startedWay[100001];
    int component[100001];
    for (int i = 1; i < n; i++)
    {
        startedWay[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a;
        cin >> b;
        if (findway(a, startedWay) != findway(b, startedWay))
        {
            com--;
            startedWay[findway(a, startedWay)] = findway(b, startedWay);
                }
        component[i] = com;
    }
    for (int i = 0; i < m; i++)
    {
        cout << component[i] << endl;
    }
    return 0;
}
