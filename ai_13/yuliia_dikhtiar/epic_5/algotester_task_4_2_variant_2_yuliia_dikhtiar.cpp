/*
Назва задачі: Lab 4v2
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>

using namespace std;

void mergeSort(long long *arr, long long *temp, int left, int right) {
    if (left >= right) {
        return;
    }

    int middle = (left + right) / 2;
    mergeSort(arr, temp, left, middle);
    mergeSort(arr, temp, middle + 1, right);

    int i = left;
    int j = middle + 1;
    int position = left;
    while (i <= middle && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[position] = arr[i];
            position++;
            i++;
        } else {
            temp[position] = arr[j];
            position++;
            j++;
        }
    }
    while (i <= middle) {
        temp[position] = arr[i];
        position++;
        i++;
    }
    while (j <= right) {
        temp[position] = arr[j];
        position++;
        j++;
    }
    for (int index = left; index <= right; index++) {
        arr[index] = temp[index];
    }
}

int main() {
    int n;
    long long k;
    cin >> n >> k;

    long long *arr = new long long[n];
    long long *temp = new long long[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    mergeSort(arr, temp, 0, n - 1);

    int size = 0;
    for (int i = 0; i < n; i++) {
        if (size == 0 || arr[i] != arr[size - 1]) {
            arr[size] = arr[i];
            size++;
        }
    }

    if (size > 0) {
        int shift = k % size;
        for (int i = 0; i < size; i++) {
            temp[i] = arr[(i + shift) % size];
        }
    }

    cout << size << '\n';
    for (int i = 0; i < size; i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << temp[i];
    }
    cout << '\n';

    delete[] arr;
    delete[] temp;
    return 0;
}