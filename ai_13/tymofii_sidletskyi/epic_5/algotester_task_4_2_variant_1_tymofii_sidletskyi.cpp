#include <iostream>
using namespace std;
/* Алготестер лаб 4.2 варіант 1
   Сідлецький Тимофій ШІ-13*/
void sortArr(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

void printRes(int res[], int cnt) {
    cout << cnt << "\n";
    for (int i = 0; i < cnt; i++) {
        cout << res[i] << " ";
    }
    cout << "\n\n";
}

void difference(int a[], int n, int b[], int m, int res[], int &cnt) {
    int i = 0, j = 0;
    cnt = 0;
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            res[cnt++] = a[i++];
        } else if (b[j] < a[i]) {
            j++;
        } else {
            i++;
            j++;
        }
    }
    while (i < n) {
        res[cnt++] = a[i++];
    }
}

void intersection(int a[], int n, int b[], int m, int res[], int &cnt) {
    int i = 0, j = 0;
    cnt = 0;
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            i++;
        } else if (b[j] < a[i]) {
            j++;
        } else {
            res[cnt++] = a[i];
            i++;
            j++;
        }
    }
}

void unite(int a[], int n, int b[], int m, int res[], int &cnt) {
    int i = 0, j = 0;
    cnt = 0;
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            res[cnt++] = a[i++];
        } else if (b[j] < a[i]) {
            res[cnt++] = b[j++];
        } else {
            res[cnt++] = a[i];
            i++;
            j++;
        }
    }
    while (i < n) {
        res[cnt++] = a[i++];
    }
    while (j < m) {
        res[cnt++] = b[j++];
    }
}

void symDifference(int a[], int n, int b[], int m, int res[], int &cnt) {
    int i = 0, j = 0;
    cnt = 0;
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            res[cnt++] = a[i++];
        } else if (b[j] < a[i]) {
            res[cnt++] = b[j++];
        } else {
            i++;
            j++;
        }
    }
    while (i < n) {
        res[cnt++] = a[i++];
    }
    while (j < m) {
        res[cnt++] = b[j++];
    }
}

int main() {
    int a[100], b[100], res[200];
    int n, m, cnt;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    sortArr(a, n);
    sortArr(b, m);

    difference(a, n, b, m, res, cnt);
    printRes(res, cnt);

    difference(b, m, a, n, res, cnt);
    printRes(res, cnt);

    intersection(a, n, b, m, res, cnt);
    printRes(res, cnt);

    unite(a, n, b, m, res, cnt);
    printRes(res, cnt);

    symDifference(a, n, b, m, res, cnt);
    printRes(res, cnt);

    return 0;
}