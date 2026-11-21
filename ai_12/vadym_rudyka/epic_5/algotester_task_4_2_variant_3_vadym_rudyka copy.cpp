#include <iostream>
using namespace std;

// перевірка, чи має x стояти перед y
bool compare(int x, int y) {
    int rx = x % 3;
    int ry = y % 3;

    // спочату буде йти остача 0, потім 1, потім 2
    if (rx != ry) {
        return rx < ry;
    }

    // для остачі 1 за спаданням
    if (rx == 1) {
        return x > y;
    }

    // а для остачі 0 і 2 за зростанням
    return x < y;
}

// швидке сортування, працює за опорною точкою
void quickSort(int a[], int left, int right) {
    int i = left;
    int j = right;

    int pivot = a[left + (right - left) / 2];

    while (i <= j) {
        while (compare(a[i], pivot)) {
            i++;
        }

        while (compare(pivot, a[j])) {
            j--;
        }

        if (i <= j) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;

            i++;
            j--;
        }
    }

    if (left < j) {
        quickSort(a, left, j);
    }

    if (i < right) {
        quickSort(a, i, right);
    }
}

int main() {
    int n;
    cin >> n;

    int* a = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    quickSort(a, 0, n - 1);

    int newSize = 0;

    for (int i = 0; i < n; i++) {
        if (newSize == 0 || a[i] != a[newSize - 1]) {
            a[newSize] = a[i];
            newSize++;
        }
    }

    cout << newSize << '\n';

    for (int i = 0; i < newSize; i++) {
        cout << a[i] << " ";
    }

    delete[] a;

    return 0;
}