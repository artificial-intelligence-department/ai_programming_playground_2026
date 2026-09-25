/*
    Задача: Хелловін
    Михайловська Анна
    ШІ-14
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    int m;
    cin >> n;
    cin >> m;

    int a[100];
    int b[100];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int k = 0; k < m; k++) {
        cin >> b[k];
    }

    int min_a = a[0];
    for (int j = 1; j < n; j++) {
        if (a[j] < min_a)
        min_a = a[j];
    }
    int min_b = b[0];
     for (int q = 1; q < m; q++) {
        if (b[q] < min_b)
        min_b = b[q];
    }

    cout << min_a + min_b;

    return 0;
}