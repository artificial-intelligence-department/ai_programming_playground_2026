/*
 * Задача: Тренер слонів(алготестер)
 * Поліщук Вероніка
 * Група 14
 */
#include <iostream>
#include <algorithm>

using namespace std;

long long a[100007];
long long n, i;

int main() {
    cin >> n;
    for (i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + 1 + n);
    cout << a[n] - a[1];
}
