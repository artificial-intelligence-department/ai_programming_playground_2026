#include <iostream>
#include <algorithm>
using namespace std;

void printArr(const int *r, int result) {
    cout << result << "\n";
    for (int i = 0; i < result; i++) {
        if (i > 0) cout << " ";
        cout << r[i];
    }
    cout << "\n";
}

int main() {
    int a[100], b[100], r[200];
    int n, m, result;
    int i, j;

    cin >> n;
    for (int k = 0; k < n; k++) cin >> a[k];

    cin >> m;
    for (int k = 0; k < m; k++) cin >> b[k];

    sort(a, a + n);
    sort(b, b + m);

    i = 0;
    j = 0;
    result = 0;

    while (i < n && j < m) {
        if (a[i] < b[j]) {
            r[result++] = a[i++];
        } else if (a[i] > b[j]) {
            j++;
        } else {
            i++;
            j++;
        }
    }
    while (i < n) r[result++] = a[i++];
    printArr(r, result);
    cout << "\n";

    i = 0;
    j = 0;
    result = 0;

    while (i < m && j < n) {
        if (b[i] < a[j]) {
            r[result++] = b[i++];
        } else if (b[i] > a[j]) {
            j++;
        } else {
            i++;
            j++;
        }
    }
    while (i < m) r[result++] = b[i++];
    printArr(r, result);
    cout << "\n";

    i = 0;
    j = 0;
    result = 0;

    while (i < n && j < m) {
        if (a[i] < b[j]) {
            i++;
        } else if (a[i] > b[j]) {
            j++;
        } else {
            r[result++] = a[i];
            i++;
            j++;
        }
    }
    printArr(r, result);
    cout << "\n";

    i = 0;
    j = 0;
    result = 0;

    while (i < n && j < m) {
        if (a[i] < b[j]) {
            r[result++] = a[i++];
        } else if (a[i] > b[j]) {
            r[result++] = b[j++];
        } else {
            r[result++] = a[i];
            i++;
            j++;
        }
    }
    while (i < n) r[result++] = a[i++];
    while (j < m) r[result++] = b[j++];
    printArr(r, result);
    cout << "\n";

    i = 0;
    j = 0;
    result = 0;

    while (i < n && j < m) {
        if (a[i] < b[j]) {
            r[result++] = a[i++];
        } else if (a[i] > b[j]) {
            r[result++] = b[j++];
        } else {
            i++;
            j++;
        }
    }
    while (i < n) r[result++] = a[i++];
    while (j < m) r[result++] = b[j++];
    printArr(r, result);

    return 0;
}