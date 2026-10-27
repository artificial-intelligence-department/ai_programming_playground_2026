/*
Олексійчук Захар ШІ-14
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void PrintArray(const int* array, int size);

int main() {
    srand(time(0));
    const int MAX_SIZE = 100;
    int arr[MAX_SIZE];

    cout << "Enter array size: ";
    int size;
    while (!(cin >> size) || size < 0 || size > MAX_SIZE) {
        cout << "Wrong input. Enter array size: ";
    }

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    cout << "Original array:\n";
    PrintArray(arr, size);

    cout << "Enter element-to-delete's index (0 - " << size-1 << "):";
    int k;
    while (!(cin >> k) || k < 0 || k > size-1) {
        cout << "Wrong input. Enter element's index: ";
    }

    for (int i = k; i < size-1; i++) {
        arr[i] = arr[i+1];
    }
    size--;
    cout << "Array after deleting arr[" << k << "]: \n";
    PrintArray(arr, size);

    for (int i = size-1; i >= 0; i--) {
        if (arr[i] % 2 == 0) {
            if (size < MAX_SIZE) {
                for (int j = size; j > i+1; j--) {
                    arr[j] = arr[j-1];
                }
                arr[i+1] = 0;
                size++;
            }
            else {
                cout << "Array overfilled\n";
                break;
            }
        }
    }

    cout << "Array after inserting '0' after every even number: \n";
    PrintArray(arr, size);

}

void PrintArray(const int* array, int size) {
    if (size == 0) {
        cout << "Array is empty\n";
        return;
    }
    for (int i = 0; i < size; i++) {
        cout << *(array+i) << " ";
    }
    cout << "\n";
}