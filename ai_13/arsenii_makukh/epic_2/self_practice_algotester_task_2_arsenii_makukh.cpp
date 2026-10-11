/*
    Назва: Борщ, картопля і салат
    Автор: Макух Арсеній
    Група: ШІ-13
*/

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

int main () {
    int n; 
    cin >> n;

    int a[n], b[n], c[n];

    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }

    int a_sum = 0, b_sum = 0, c_sum = 0;
    for (int i = 0; i < n; i++) {
        a_sum += a[i];
        b_sum += b[i];
        c_sum += c[i];
    }

    sort(a, a + n);
    sort(b, b + n);
    sort(c, c + n);

    int distrust = 0;
    for (int i = 0; i < n; i++) {
        distrust += abs(a[i] - a[n/2]) + abs(b[i] - b[n/2]) + abs(c[i] - c[n/2]);
    }

    cout << distrust << endl;

    return 0;
}