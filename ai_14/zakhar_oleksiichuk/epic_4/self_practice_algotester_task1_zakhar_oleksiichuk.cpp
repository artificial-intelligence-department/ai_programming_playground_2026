/*
Олексійчук Захар ШІ-14
*/

#include <iostream>

using namespace std;

void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N-i-1; j++) {
            if (*(arr+j) > *(arr+j+1)) Swap((arr+j), (arr+j+1));
        }
    }
}

int main() {
    int N;
    cin >> N;

    int* arr = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> *(arr+i);
    }

    bubbleSort(arr, N);

    int success = 1;
    for (int i = 1; i < N; i++) {
        if (*(arr+i) != *(arr+i-1)) success++;
    }

    cout << success << endl;
}