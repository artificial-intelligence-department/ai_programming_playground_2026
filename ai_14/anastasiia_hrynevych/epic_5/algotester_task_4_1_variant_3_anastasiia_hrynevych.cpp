#include <iostream>
using namespace std;

void swap (int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void heapifyup(int arr[], int n, int i) {
    int largest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapifyup(arr, n, largest);
    }
}

void heapifydown(int arr[], int n, int i) {
    int smallest = i; 
    int left = 2 * i + 1; 
    int right = 2 * i + 2; 

    if (left < n && arr[left] < arr[smallest])
        smallest = left;

    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        heapifydown(arr, n, smallest);
    }
}

void heapsortup(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyup(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapifyup(arr, i, 0);
    }
}

void heapsortdown(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifydown(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapifydown(arr, i, 0);
    }
}

void removeduplicates(int arr[], int n, int &newsizenum) {
    if (n == 0 || n == 1)
        return;

    int j = 0; 
    for (int i = 0; i < n - 1; i++)
        if (arr[i] != arr[i + 1])
            arr[j++] = arr[i];

    arr[j++] = arr[n - 1];

    newsizenum = j;
    
}

int main() {
    int n; cin >> n;
    int a[n], a0[n], a1[n], a2[n];
    int zero = 0, one = 0, two = 0, newsize1 = 0, newsize2 = 0, newsize0 = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] % 3 == 0) {
            a0[zero] = a[i];
            zero++;
        } else if (a[i] % 3 == 1) {
            a1[one] = a[i];
            one++;
        } else {
            a2[two] = a[i];
            two++;
        }
    }
    heapsortup(a0, zero);
    heapsortdown(a1, one);
    heapsortup(a2, two);
    removeduplicates(a0, zero,  newsize0);
    removeduplicates(a1, one, newsize1);
    removeduplicates(a2, two, newsize2);
    cout << newsize1 + newsize2 + newsize0 << endl;
    for (int i = 0; i < newsize0; i++) {
        cout << a0[i] << " ";
    }
    for (int i = 0; i < newsize1; i++) {
        cout << a1[i] << " ";
    }
    for (int i = 0; i < newsize2; i++) {
        cout << a2[i] << " ";
    }
    return 0;
}