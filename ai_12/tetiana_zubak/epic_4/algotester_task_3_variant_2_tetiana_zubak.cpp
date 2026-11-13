/* 
Алготестер, варіант 2
Зубак Тетяна
ШІ-12
*/
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, m, i = 0, j = 0, N = 0;
    cin >> n; 
    long long a[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> m;
    long long b[m];
    for (int i = 0; i < m; i++) cin >> b[i];

    sort(a, a + n);
    sort(b, b + m);
    while (i < n && j < m) {
        if (a[i] == b[j]) {
            N++;
            i++;
            j++;
        } 
        else if (a[i] < b[j]) {
            i++;
        } 
        else {
            j++;
        }
    }

    cout << N << endl;
    cout << n + m - N << endl;
    return 0;
}