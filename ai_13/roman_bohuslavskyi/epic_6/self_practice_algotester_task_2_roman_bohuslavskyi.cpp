/*
Задача:  Реплікація. Частина 1
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>

using namespace std;

int removeRoot(int heap[], int& size);

int main() {
    int n, root;
    cin >> n >> root;

    int* heap = new int[n + 2];
    int size = 1;
    heap[1] = root;

    for (int i = 0; i < n; i++) {
        char operation;
        cin >> operation;

        int swaps = 0;
        if (operation == '+') {
            size++;
            cin >> heap[size];
        }
        else {
            swaps = removeRoot(heap, size);
        }

        cout << swaps << ' ' << heap[1] << '\n';
    }

    delete[] heap;
    return 0;
}

int removeRoot(int heap[], int& size) {
    heap[1] = heap[size];
    size--;

    int position = 1;
    int swaps = 0;
    while (position * 2 <= size) {
        int child = position * 2;
        if (child + 1 <= size && heap[child + 1] > heap[child]) {
            child++;
        }
        if (heap[position] >= heap[child]) {
            break;
        }

        int value = heap[position];
        heap[position] = heap[child];
        heap[child] = value;
        position = child;
        swaps++;
    }

    return swaps;
}
