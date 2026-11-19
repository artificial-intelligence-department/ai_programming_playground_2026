#include <iostream>
#include <vector>
#include <algorithm>

using namespace  std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
    cin >> a[i];

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    int m = a.size();
    k = k % m;

    rotate(a.begin(), a.begin() + k, a.end());
    
    cout << m << endl;
    for(int i = 0; i < m; i++)
    cout << a[i] << " ";

    return 0;
}