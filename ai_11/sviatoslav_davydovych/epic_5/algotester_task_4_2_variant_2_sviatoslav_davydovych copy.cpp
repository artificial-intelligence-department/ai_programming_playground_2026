#include <iostream>

using namespace std;

void countingSort(int* arr, int size) {
    if (size <= 1) return;

    int min_val = arr[0];
    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
    }

    int range = max_val - min_val + 1;

    int* count = new int[range]();

    for (int i = 0; i < size; i++) {
        count[arr[i] - min_val]++;
    }

    int index = 0;
    for (int i = 0; i < range; i++) {
        while (count[i] > 0) {
            arr[index++] = i + min_val;
            count[i]--;
        }
    }
    delete[] count;
}

int unique(int* arr, int size) {
    if (size <= 1) return size;

    int write_index = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] != arr[write_index]) {
            write_index++;
            arr[write_index] = arr[i];
        }
    }

    return write_index + 1;
}

void rotate(int *arr, int size, int shift){
    int *copy = new int[size];

    for (int i = 0; i<size; i++){
        copy[i]=arr[i];
    }

    for (int i = 0; i<size; i++){
        int shifted_i = (i+shift) % size;
        arr[i]=copy[shifted_i];
    }

    delete[] copy;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;
    int numbers[N];

    for (int i = 0; i<N; i++){
        cin >> numbers[i];
    }
    countingSort(numbers, N);

    int newSize = unique(numbers, N);
    K = K % newSize;

    rotate(numbers, newSize, K);
    
    cout << newSize << "\n";
    for (int i = 0; i<newSize; i++){
        cout << numbers[i] << " ";
    }
}
