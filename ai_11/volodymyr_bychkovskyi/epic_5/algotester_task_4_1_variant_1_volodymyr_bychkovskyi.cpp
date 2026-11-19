/*
Назва: Алготестер Лабораторна 4 варіант 1 STL
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
#include <algorithm> 

using namespace std;

void printResult(int* arr, int size) {
    cout << size << "\n";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << (i + 1 < size ? " " : "");
    }
    cout << "\n";
}

int main() {
    int n, m;

    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) cin >> a[i];

    cin >> m;
    int* b = new int[m];
    for (int i = 0; i < m; i++) cin >> b[i];

    sort(a, a + n);
    sort(b, b + m);

    int* res = new int[n + m];
    int* endPtr = nullptr;

    // Різниця N - M
    endPtr = set_difference(a, a + n, b, b + m, res);
    printResult(res, endPtr - res);

    // Різниця M - N
    endPtr = set_difference(b, b + m, a, a + n, res);
    printResult(res, endPtr - res);

    // Перетин
    endPtr = set_intersection(a, a + n, b, b + m, res);
    printResult(res, endPtr - res);

    // Об'єднання
    endPtr = set_union(a, a + n, b, b + m, res);
    printResult(res, endPtr - res);

    // Симетрична різниця
    endPtr = set_symmetric_difference(a, a + n, b, b + m, res);
    printResult(res, endPtr - res);

    delete[] a;
    delete[] b;
    delete[] res;

    return 0;
}