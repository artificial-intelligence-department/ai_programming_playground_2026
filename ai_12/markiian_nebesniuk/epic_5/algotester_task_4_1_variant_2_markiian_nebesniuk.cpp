/*
Алготестер лабораторна №6 варіант 1 (З STL)
Небеснюк Маркіян
ШІ-12
*/
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int a[1005];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // 1. Сортуємо масив (обов'язково перед unique, бо unique видаляє лише сусідні дублікати)
    sort(a, a + n);

    // 2. Видаляємо повтори та отримуємо нову кількість унікальних елементів m
    int m = unique(a, a + n) - a;

    // 3. Обертаємо посортований масив без дублікатів на k позицій вліво
    k = k % m;
    rotate(a, a + k, a + m);

    // Вивід результату
    cout << m << "\n";
    for (int i = 0; i < m; i++) {
        cout << a[i] << (i + 1 < m ? " " : "\n");
    }

    return 0;
}