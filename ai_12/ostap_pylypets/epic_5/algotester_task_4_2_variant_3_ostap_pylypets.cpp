#include <iostream>
using namespace std;
//умова
bool comesBefore(int a, int b) {
    if (a % 3 != b % 3) {
        return a % 3 < b % 3;
    }
    if (a % 3 == 1) {
        return a > b;
    }
    return a < b;
}

void mergeSort(int* arr, int* temp, int left, int right) {
    //перевірка на закінчення сортування
    if (right - left <= 1) {
        return;
    }
    //алгоритм який ділить на 2 та сортує
    int mid = left + (right - left) / 2;
    mergeSort(arr, temp, left, mid);
    mergeSort(arr, temp, mid, right);

    int i = left;
    int q = mid;
    int k = left;
    //порівнюємо поки є елементи
    while (i < mid && q < right) {
        //якщо правий маж стояти раніше то->
        if (comesBefore(arr[q], arr[i])) {
            temp[k++] = arr[q++];
        } else {
            temp[k++] = arr[i++];
        }
    }
    //залишок лівої
    while (i < mid) {
        temp[k++] = arr[i++];
    }
    //залишок правої
    while (q < right) {
        temp[k++] = arr[q++];
    }
    //записуємо значення у масив
    for (i = left; i < right; i++) {
        arr[i] = temp[i];
    }
}

void sortToThree(int* arr, int& n) {
    int* temp = new int[n];
    mergeSort(arr, temp, 0, n);
    delete[] temp;

    int k = 0;
    for (int i = 0; i < n; i++) {
        if (k == 0 || arr[i] != arr[k - 1]) {
            arr[k++] = arr[i];
        }
    }
    n = k;
}
int main() {
    int n;
    cin >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    sortToThree(arr, n);

    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << arr[i];
    }
    cout << '\n';

    delete[] arr;
    arr = nullptr;
    return 0;
}