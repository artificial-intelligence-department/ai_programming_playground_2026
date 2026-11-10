/*
Lab 4_1
Кузовніков В'ячеслав Євгенійович
ШІ - 13
Варіант 3
*/

#include <iostream>
using namespace std;


bool isLess(int a, int b) {
    int remA = a % 3;
    int remB = b % 3;


    if (remA != remB) {
        return remA < remB;
    }

    if (remA == 0 || remA == 2) {
        return a < b;
    }

    return a > b;
}


void quickSort(int arr[], int left, int right) {
    if (left >= right) return;

    int pivot = arr[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (isLess(arr[i], pivot)) i++;
        while (isLess(pivot, arr[j])) j--;

        if (i <= j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    quickSort(arr, left, j);
    quickSort(arr, i, right);
}

int main() {
    int n = 0;
    if (!(cin >> n)) return 0;

    int arr[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    quickSort(arr, 0, n - 1);

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] == arr[i + 1]) {
            for (int k = i + 1; k < n - 1; k++) {
                arr[k] = arr[k + 1];
            }
            n--;
            i--;
        }
    }

    cout << n << endl;

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }


    return 0;
}