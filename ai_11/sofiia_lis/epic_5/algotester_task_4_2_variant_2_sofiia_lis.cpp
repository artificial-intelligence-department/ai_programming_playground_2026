/* 
Епік 5. algotester_task_4_2_variant_2
Авторка: Софія Ліс
Група: ші-11
*/

#include <iostream>

using namespace std;

bool find(int * arr, int n, int m) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == m){
        return true;
        }
    }
    return false;
}

int * unique(int * arr, int &n) {
    int * brr = new int[n];
    int size = 0;
    for(int i = 0; i < n; i++) {
        if(find(brr, size, arr[i])) {
            continue;
        }
        brr[size] = arr[i];
        size++;
    }
    int * crr = new int[size];
    for(int i = 0; i < size; i++) {
        crr[i] = brr[i];
    }
    n = size;
    delete[] arr;
    delete[] brr;
    return crr;
}

void merge(int * arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }   

    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) 
            arr[k++] = L[i++];
        else              
            arr[k++] = R[j++];
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

void mergeSort(int * arr, int left, int right) {
    if (left >= right) 
    return; 

    int mid = (right + left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int * swap(int * arr, int n, int k) {
    k %= n;
    int * drr = new int[n];
    for(int i = 0; i < n-k; i++) {
        drr[i] = arr[i+k];
    }
    for(int i = 0; i < k; i++) {
        drr[n-k+i] = arr[i]; 
    }
    delete[] arr;
    return drr;
}

int main() {
    int N, K;
    cin >> N >> K;

    int * arr = new int[N];
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    arr = unique(arr, N);

    mergeSort(arr, 0, N-1);

    arr = swap(arr, N, K);

    cout << N << endl;

    for(int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }

    delete[] arr;

    arr = nullptr;

    return 0;
}