/*
Епік 5. Algotester Lab 4 (Варіант 3, частина 2 — без STL, власна реалізація Merge Sort)
Автор: Туревич Олександр
Група: ШІ-12
*/

#include <iostream>

using namespace std;

void Swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}


int myPartition(int arr[], int left, int right, int target) {
    int pos = left;
    for (int i = left; i < right; ++i) {
        if (arr[i] % 3 == target) {
            Swap(arr[i], arr[pos]);
            pos++;
        }
    }
    return pos;
}


void merge(int arr[], int left, int mid, int right, bool desc) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (desc) {
            if (L[i] >= R[j]) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        } else {
            if (L[i] <= R[j]) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }

    delete[] L;
    delete[] R;
}


void mergeSort(int arr[], int left, int right, bool desc) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, desc);
    mergeSort(arr, mid + 1, right, desc);
    merge(arr, left, mid, right, desc);
}


int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;
    int w = 1;
    for (int i = 1; i < n; ++i) {
        if (arr[i] != arr[w - 1]) {
            arr[w++] = arr[i];
        }
    }
    return w;
}

int main() {
    int n;
    cin >> n;

    int *a = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }


    int idx1 = myPartition(a, 0, n, 0);
    int idx2 = myPartition(a, idx1, n, 1);


    mergeSort(a, 0, idx1 - 1, false);      
    mergeSort(a, idx1, idx2 - 1, true);   
    mergeSort(a, idx2, n - 1, false);     


    int m = removeDuplicates(a, n);

    cout << m << endl;
    for (int i = 0; i < m; ++i) {
        if (i > 0) cout << " ";
        cout << a[i];
    }
    cout << endl;

    delete[] a;
    return 0;
}
