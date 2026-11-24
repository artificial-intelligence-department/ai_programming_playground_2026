#include <iostream>
using namespace std;

bool compare(int x, int y) {
    int rx = x % 3;
    int ry = y % 3;

    if (rx != ry) {
        return rx < ry;
    }
    if (rx == 1) {
        return x > y;
    }
    return x < y;
}

void merge(int a[], int temp[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (compare(a[j], a[i])) {
            temp[k++] = a[j++];
        } else {
            temp[k++] = a[i++];
        }
    }

    while (i <= mid) {
        temp[k++] = a[i++];
    }
    while (j <= right) {
        temp[k++] = a[j++];
    }
    for (int p = left; p <= right; p++) {
        a[p] = temp[p];
    }
}

void mergeSort(int a[], int temp[], int left, int right) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(a, temp, left, mid);
    mergeSort(a, temp, mid + 1, right);
    merge(a, temp, left, mid, right);
}

int main() {
    int n;
    cin >> n;
    int* a = new int[n];
    int* temp = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    mergeSort(a, temp, 0, n - 1);

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
    delete[] temp;

    return 0;
}