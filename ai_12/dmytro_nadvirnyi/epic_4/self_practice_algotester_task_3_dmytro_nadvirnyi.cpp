//algotester self practice task 3 2044
#include <iostream>
using namespace std;

void quickSort(int* a, int left, int right) {
    int i = left, j = right;
    int pivot = a[left + (right - left) / 2];

    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;

        if (i <= j) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) quickSort(a, left, j);
    if (i < right) quickSort(a, i, right);
}

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;

    int size = n * m;
    int* a = new int[size];

    for (int i = 0; i < size; i++) {
        cin >> a[i];
    }

    quickSort(a, 0, size - 1);

    // 1. Рахуємо кількість унікальних чисел, що повторюються
    int k = 0;
    for (int i = 0; i < size - 1; i++) {
        // Якщо поточне дорівнює наступному
        if (a[i] == a[i + 1]) {
            // І воно не дорівнює попередньому (щоб не рахувати одне й те саме тричі)
            if (i == 0 || a[i] != a[i - 1]) {
                k++;
            }
        }
    }

    cout << k << '\n';

    // 2. Виводимо їх
    for (int i = 0; i < size - 1; i++) {
        if (a[i] == a[i + 1]) {
            if (i == 0 || a[i] != a[i - 1]) {
                cout << a[i] << " ";
            }
        }
    }
    cout << '\n';

    delete[] a;
    return 0;
}