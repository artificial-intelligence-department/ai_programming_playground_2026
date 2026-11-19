// Алготестер, лабораторна 4 варіант 1, без stl


#include <iostream>
#include <algorithm>

using namespace std;

void print(int arr[], int k) {
    cout << k << "\n";
    for (int x = 0; x < k; x++) cout << arr[x] << " ";
    cout << "\n\n";
}

int diff(int a[], int n, int b[], int m, int res[]) {
    int k = 0;
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            res[k] = a[i];
            k++;
            i++;
        } else if (a[i] > b[j]) {
            j++;
        } else {
            i++;
            j++;
        }
    }
    while (i < n) {
        res[k] = a[i];
        k++;
        i++;
    }
    return k;
}

int intersect(int a[], int n, int b[], int m, int res[]) {
    int k = 0;
    int i = 0, j = 0;
    while (i < n && j < m){
        if (a[i] == b[j]){
            res[k] = a[i];
            k++;
            i++;
            j++;
        } else if (a[i] < b[j]){
            i++;
        } else j++;
    }
    return k;
}

int unite(int a[], int n, int b[], int m, int res[]) {
    int k = 0;
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            res[k] = a[i];
            k++;
            i++;
        } else if (a[i] > b[j]) {
            res[k] = b[j];
            k++;
            j++;
        } else {
            res[k] = a[i];
            k++;
            i++;
            j++;
        }
    }
    while (i < n) {
        res[k] = a[i];
        k++;
        i++;
    }
    while (j < m) {
        res[k] = b[j];
        k++;
        j++;
    }
    return k;

}
int symDiff(int a[], int n, int b[], int m, int res[]) {
    int k = 0;
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (a[i] < b[j]) {
            res[k] = a[i];
            i++;
            k++;
        } else if (a[i] > b[j]) {
            res[k] = b[j];
            k++;
            j++;
        } else {
            i++;
            j++;
        }
    }
    while (i < n) {
        res[k] = a[i];
        k++;
        i++;
    }
    while (j < m) {
        res[k] = b[j];
        k++;
        j++;
    }
    return k;
}

int main(){
    int a[100], b[100];
    int n, m;

    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; i++) cin >> b[i];

    sort(a, a + n);
    sort(b, b + m);

    int res1[200];
    int k1 = diff(a, n, b, m, res1);
    print(res1, k1);

    int res2[200];
    int k2 = diff(b, m, a, n, res2);
    print(res2, k2);

    int res3[200];
    int k3 = intersect(a, n, b, m, res3);
    print(res3, k3);

    int res4[200];
    int k4 = unite(a, n, b, m, res4);
    print(res4, k4);

    int res5[200];
    int k5 = symDiff(a, n, b, m, res5);
    print(res5, k5);
    return 0;
}