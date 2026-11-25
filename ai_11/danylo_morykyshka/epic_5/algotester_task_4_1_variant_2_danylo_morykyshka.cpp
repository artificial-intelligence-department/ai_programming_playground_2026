#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    int n;
    int k;
    cin >> n >> k;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    auto it = unique(v.begin(), v.end());
    v.erase(it, v.end());
    while (k > 0)
    {
        rotate(v.begin(), v.begin() + 1, v.end());
        k--;
    }
    cout << v.size() << endl;
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    
}