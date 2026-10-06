#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main () {
    int n;
    cin >> n;
    vector<int> a(n), b(n), c(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());

    int A = a[n / 2 ];
    int B = b[n / 2 ];
    int C = c[n / 2 ];
    
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += abs(a[i] - A) + abs(b[i] - B) + abs(c[i] - C);
    }
   
    cout << total << endl;
    return 0;
}