/*
Епік 5. Algotester Lab 4 (Варіант 3, частина 1 — з використанням STL)
Автор: Туревич Олександр
Група: ШІ-12
*/

#include <iostream>
#include <algorithm>


using namespace std;

int main() {
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }


    int* it1 = partition(a, a + n, [](int x) {
        return x % 3 == 0;
    });

    int* it2 = partition(it1, a + n, [](int x) {
        return x % 3 == 1;
    });


    sort(a, it1);
    sort(it1, it2);
    reverse(it1, it2);
    sort(it2, a + n);

    // Видаляємо дублікати
    int *last = unique(a, a + n);
    int a_len = last - a;

    cout << a_len << endl;
    for (int i = 0; i < a_len; ++i) {
        if (i > 0) cout << " ";
        cout << a[i];
    }
    cout << endl;
    delete[] a;
    return 0;
}
