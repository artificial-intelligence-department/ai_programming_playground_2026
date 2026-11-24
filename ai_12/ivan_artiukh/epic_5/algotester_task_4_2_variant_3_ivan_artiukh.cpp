#include <iostream>

using namespace std;

void mergeSort(int *a, int *tmp, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(a, tmp, left, mid);
    mergeSort(a, tmp, mid + 1, right);

    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
        }
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= right) tmp[k++] = a[j++];

    for (int p = left; p <= right; p++) {
        a[p] = tmp[p];
    }
}

void del_dups(int *a, int &size) {
    if (size <= 1) return;
    int write = 1;
    for (int i = 1; i < size; i++) {
        if (a[i] != a[write - 1]) {
            a[write++] = a[i];
        }
    }
    size = write;
}

void invert(int *a, int size) {
    for (int i = 0; i < size / 2; i++) {
        int tmp = a[i];
        a[i] = a[size - i - 1];
        a[size - i - 1] = tmp;
    }
}

void print_arr(int *a, int size, bool &first) {
    for (int i = 0; i < size; i++) {
        if (!first) cout << " ";
        cout << a[i];
        first = false;
    }
}

int main() {
    int n = 0;
    cin >> n;

    int *zero = new int[n];
    int *one = new int[n];
    int *two = new int[n];
    int *tmp = new int[n];

    int zero_len = 0, one_len = 0, two_len = 0;

    for (int i = 0; i < n; i++) {
        int x = 0;
        cin >> x;
        switch (x % 3) {
            case 0: zero[zero_len++] = x; break;
            case 1: one[one_len++] = x; break;
            case 2: two[two_len++] = x; break;
        }
    }

    mergeSort(zero, tmp, 0, zero_len - 1);
    mergeSort(one, tmp, 0, one_len - 1);
    mergeSort(two, tmp, 0, two_len - 1);

    del_dups(zero, zero_len);
    del_dups(one, one_len);
    del_dups(two, two_len);

    invert(one, one_len);

    int m = zero_len + one_len + two_len;
    cout << m << "\n";

    bool first = true;
    print_arr(zero, zero_len, first);
    print_arr(one, one_len, first);
    print_arr(two, two_len, first);
    cout << "\n";

    delete[] zero;
    delete[] one;
    delete[] two;
    delete[] tmp;

    return 0;
}