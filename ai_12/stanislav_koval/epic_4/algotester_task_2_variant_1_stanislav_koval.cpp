/*
Алготестер, Завдання 2, Варіант 1
Станіслав Коваль
ШІ-12
*/

#include <iostream>
#include <algorithm>
using namespace std;

int main () {
    int N;
    cin >> N;
    int* arr = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    if (N <= 2) {
        cout << 0 << endl;
        return 0;
    }

    sort(arr, arr + N);
    int* newArr = new int[N - 1];

    if (arr[N - 1] - arr[1] <= arr[N - 2] - arr[0]) {
        for (int i = 1; i < N; i++) {
            newArr[i - 1] = arr[i];
        }
    }
    else {
        for (int i = 0; i < N - 1; i++) {
            newArr[i] = arr[i];
        }
    }
    N--;
    cout << newArr[N - 1] - newArr[0] << endl;

    delete[] arr;
    delete[] newArr;
}