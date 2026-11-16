#include <iostream>
using namespace std;

const int MAX_N = 1001;
int temp[MAX_N];

int partition(int arr[], int first, int last, int remainder) {
    int border = first;
    for (int i = first; i < last; i++) {
        if (arr[i] % 3 == remainder) {
            int t = arr[i];
            arr[i] = arr[border];
            arr[border] = t;
            border++;
        }
    }
    return border;
}

int unique(int arr[], int first, int last) {
    if (first >= last) return last;
    int result = first;
    for (int i = first + 1; i < last; i++) {
        if (arr[i] != arr[result]) {
            result++;
            arr[result] = arr[i];
        }
    }
    return result + 1;
}

void erase(int arr[], int &n, int from, int to) {
    int count = to - from;
    for (int i = to; i < n; i++) {
        arr[i - count] = arr[i];
    }
    n -= count;
}

void merge(int arr[], int left, int mid, int right, bool ascending) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        bool takeLeft = ascending ? (arr[i] <= arr[j]) : (arr[i] >= arr[j]);
        if (takeLeft){
            temp[k++] = arr[i++];
        }
        else{
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid){
        temp[k++] = arr[i++];
    }
    while (j <= right){
        temp[k++] = arr[j++];
    }
    for (int p = left; p <= right; p++){
        arr[p] = temp[p];
    }
}

void mergeSort(int arr[], int left, int right, bool ascending) {
    if(left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid, ascending);
    mergeSort(arr, mid + 1, right, ascending);
    merge(arr, left, mid, right, ascending);
}

int main(){
    int n;
    cin >> n;
    int a[MAX_N];

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    int remainder1Start = partition(a, 0, n, 0);
    int remainder2Start = partition(a, remainder1Start, n, 1);

    mergeSort(a, 0, remainder1Start - 1, true);
    mergeSort(a, remainder1Start, remainder2Start - 1, false);
    mergeSort(a, remainder2Start, n - 1, true);

    erase(a, n, unique(a, 0, n), n);

    cout << n << endl;

    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }

    return 0;
}