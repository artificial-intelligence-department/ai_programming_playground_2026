#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int a[1000];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    sort(a, a + n);

    int m = unique(a, a + n) - a; // видаляємо повтори, юнік повертає адресу, тому віднімаємо a, щоб отримати кількість унікальних елементів

    k %= m; // якщо к більше м

    rotate(a, a + k, a + m); // початок, новий початок, кінець

    cout << m << endl;
    for (int i = 0; i < m; ++i) {
        cout << a[i] << " ";
    }
    return 0;
}