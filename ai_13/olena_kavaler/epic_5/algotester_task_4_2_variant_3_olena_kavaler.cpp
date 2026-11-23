
/*
Автор: Олена Кавалер
Група: ШІ-13
*/

#include <iostream>
using namespace std;

bool cmp(int a, int b) {
    int ra = a % 3;
    int rb = b % 3;

    if (ra != rb) {
        return ra < rb;
    }
    if (ra == 1) {
        return a > b;
    }
    return a < b;
}

void mergeSort(int a[], int l, int r) {
    if (l >= r) {
        return;
    }

    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);

    int tmp[1000];
    int i = l;
    int j = m + 1;
    int k = 0;

    while (i <= m && j <= r) {
        if (cmp(a[j], a[i])) {
            tmp[k] = a[j];
            j++;
        } else {
            tmp[k] = a[i];
            i++;
        }
        k++;
    }
    while (i <= m) {
        tmp[k] = a[i];
        i++;
        k++;
    }
    while (j <= r) {
        tmp[k] = a[j];
        j++;
        k++;
    }

    for (int t = 0; t < k; t++) {
        a[l + t] = tmp[t];
    }
}

int removeDuplicates(int a[], int n) {
    if (n == 0) {
        return 0;
    }

    int k = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[k - 1]) {
            a[k] = a[i];
            k++;
        }
    }
    return k;
}

int main() {
    int n;
    cin >> n;

    int a[1000];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    mergeSort(a, 0, n - 1);
    n = removeDuplicates(a, n);

    cout << n << endl;
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}