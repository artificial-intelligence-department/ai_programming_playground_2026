/*Алготестер lab4v3 (з використанням засобів STL)
ШІ-14
Кравець Аліна*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool sortByDescending(int x, int y)
{
    return x > y;
}

int main()
{
    int n = 0;
    vector<int> a0, a1, a2;
    vector<int> a;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int t = 0;
        cin >> t;
        if (t%3 == 0) a0.push_back(t);
        else if (t%3 == 1) a1.push_back(t);
        else a2.push_back(t);
    }

    sort(a0.begin(), a0.end());
    sort(a1.begin(), a1.end(), sortByDescending);
    sort(a2.begin(), a2.end());

    a.insert(a.end(), a0.begin(), a0.end());
    a.insert(a.end(), a1.begin(), a1.end());
    a.insert(a.end(), a2.begin(), a2.end());

    a.erase(unique(a.begin(), a.end()), a.end());

    cout << a.size() << endl;
    for (int x : a)
    {
        cout << x << " ";
    }

    return 0;
}
