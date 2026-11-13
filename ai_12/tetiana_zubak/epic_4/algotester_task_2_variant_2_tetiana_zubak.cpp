/* 
Алготестер, варіант 2
Зубак Тетяна
ШІ-12
*/
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long  r[n];
    long long v[n];

    for (int i = 0; i < n; i++) cin >> r[i];

    long long a, b, c;
    cin >> a >> b >> c;

    int k = 0;
    for (int i = 0; i < n; i++) {
        if (r[i] != a && r[i] != b && r[i] != c) {
            v[k] = r[i];
            k++;
        }
    }

    int m = k >= 2 ? k - 1 : 0;
    cout << m << "\n";
    for (int i = 0; i < m; i++) {
        cout << v[i] + v[i + 1];
        if (i + 1 < m) cout << " ";
    }
    cout <<  endl;
    return 0;
}