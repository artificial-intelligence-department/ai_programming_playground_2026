/*
Algotester lab 4 2
variant 2
Лисюк Андріана
ШІ-13
*/

#include <iostream>

using namespace std;

void customSwap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}
void customSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            customSwap(arr[i], arr[minIdx]);
        }
    }
}
void customReverse(int arr[], int left, int right) {
    while (left < right) {
        customSwap(arr[left], arr[right]);
        left++;
        right--;
    }
}
void customRotate(int arr[], int size, int k) {
    if (size <= 1) return;
    k %= size;
    if (k == 0) return;

    customReverse(arr, 0, k - 1);
    customReverse(arr, k, size - 1);
    customReverse(arr, 0, size - 1);
}
int main() {
    int n, k;
    if (!(cin >> n >> k)) return 0;
    int a[1005];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    customSort(a, n);
    int m = 0;
    if (n > 0) {
        a[m++] = a[0];
        for (int i = 1; i < n; ++i) {
            if (a[i] != a[i - 1]) {
                a[m++] = a[i];
            }
        }
    }
    customRotate(a, m, k);
    cout << m << "\n";
    for (int i = 0; i < m; ++i) {
        cout << a[i] << (i + 1 == m ? "" : " ");
    }
    cout << "\n";

    return 0;
}