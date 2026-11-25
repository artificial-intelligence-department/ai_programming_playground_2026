/*
Назва: Алготестер Лабораторна 4 варіант 1
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>

using namespace std;

void sortArray(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

bool findAndMark(int* arr, bool* used, int size, int val) {
    for (int j = 0; j < size; j++) {
        if (!used[j] && arr[j] == val) {
            used[j] = true;
            return true;
        }
    }
    return false;
}

void resetUsed(bool* used, int size) {
    for (int i = 0; i < size; i++) {
        used[i] = false;
    }
}

void printResult(int* arr, int size) {
    sortArray(arr, size);
    cout << size << "\n";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << (i + 1 < size ? " " : "");
    }
    cout << "\n";
}

int main() {
    int n, m;
    
    cin >> n;
    int* A = new int[n];
    for (int i = 0; i < n; i++) cin >> A[i];

    cin >> m;
    int* B = new int[m];
    for (int i = 0; i < m; i++) cin >> B[i];

    int* res = new int[n + m];
    int resSize = 0;
    
    bool* usedA = new bool[n];
    bool* usedB = new bool[m];

    // 1. Різниця N - M
    resSize = 0;
    resetUsed(usedB, m);
    for (int i = 0; i < n; i++) {
        if (!findAndMark(B, usedB, m, A[i])) {
            res[resSize++] = A[i];
        }
    }
    printResult(res, resSize);

    // 2. Різниця M - N
    resSize = 0;
    resetUsed(usedA, n);
    for (int j = 0; j < m; j++) {
        if (!findAndMark(A, usedA, n, B[j])) {
            res[resSize++] = B[j];
        }
    }
    printResult(res, resSize);

    // 3. Перетин
    resSize = 0;
    resetUsed(usedB, m);
    for (int i = 0; i < n; i++) {
        if (findAndMark(B, usedB, m, A[i])) {
            res[resSize++] = A[i];
        }
    }
    printResult(res, resSize);

    // 4. Об'єднання
    resSize = 0;
    resetUsed(usedB, m);
    for (int i = 0; i < n; i++) {
        res[resSize++] = A[i];
        findAndMark(B, usedB, m, A[i]);
    }
    for (int j = 0; j < m; j++) {
        if (!usedB[j]) {
            res[resSize++] = B[j];
        }
    }
    printResult(res, resSize);

    // 5. Симетрична різниця
    resSize = 0;
    resetUsed(usedB, m);
    for (int i = 0; i < n; i++) {
        if (!findAndMark(B, usedB, m, A[i])) {
            res[resSize++] = A[i];
        }
    }
    for (int j = 0; j < m; j++) {
        if (!usedB[j]) {
            res[resSize++] = B[j];
        }
    }
    printResult(res, resSize);

    delete[] A;
    delete[] B;
    delete[] res;
    delete[] usedA;
    delete[] usedB;

    return 0;
}