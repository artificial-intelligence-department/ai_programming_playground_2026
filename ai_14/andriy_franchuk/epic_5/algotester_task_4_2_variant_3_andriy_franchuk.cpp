#include <iostream>

using namespace std;

void quicksort(int a[], int left, int right);
void swap(int *a, int *b);

int main() {
    int n;
    cin >> n;

    int* a = new int[n];
    int* a1 = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int t = 0;

    for (int r = 0; r < 3; r++) {

        int start = t;

        for (int j = 0; j < n; j++) {
            if (a[j] % 3 == r) {
                a1[t] = a[j];
                t++;
            }
        }

        quicksort(a1, start, t - 1);

        if (r == 1) {
            for (int k = 0; k < (t - start) / 2; k++) {
                swap(a1[start + k], a1[t - 1 - k]);
            }
        }
    }

    int m = 0;

    for (int i = 0; i < t; i++) {
        if (m == 0 || a1[i] != a1[m - 1]) {
            a1[m] = a1[i];
            m++;
        }
    }

    cout << m << endl;

    for (int i = 0; i < m; i++) {
        cout << a1[i] << " ";
    }

    delete[] a;
    delete[] a1;

    return 0;
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void quicksort(int a[], int left, int right) {
    if (left >= right) {
        return;
    }

    int i = left;
    int j = right;

    int pivot = a[left + (right - left) / 2];

    while (i <= j) {
        while (a[i] < pivot) {
            i++;
        }

        while (a[j] > pivot) {
            j--;
        }

        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (left < j) {
        quicksort(a, left, j);
    }

    if (i < right) {
        quicksort(a, i, right);
    }
}