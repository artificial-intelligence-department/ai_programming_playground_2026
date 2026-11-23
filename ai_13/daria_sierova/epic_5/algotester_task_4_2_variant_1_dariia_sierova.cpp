#include <iostream>
#include <algorithm>
using namespace std;

void print(int res[], int res_size) {
    cout << res_size << endl;
    for (int i = 0; i < res_size; i++) {
        cout << res[i] << (i + 1 < res_size ? " " : "");
    }
    cout << endl;
}

int main() {
    int N;
    cin >> N;
    if(cin.fail() || N<0 || N > 100) return 0;
    int* arr1 = new int[N];
    for (int i = 0; i < N; ++i) cin >> arr1[i];

    int M;
    cin >> M;
    if(cin.fail() || M < 0 || M > 100) return 0;
    int* arr2 = new int[M];
    for (int i = 0; i < M; ++i) cin >> arr2[i];

    sort(arr1, arr1 + N);
    sort(arr2, arr2 + M);

    int* res = new int[N + M];
    int res_size = 0;
    bool* used = new bool[M]; // для вже використаних елементів

    // N - M
    res_size = 0;
    for (int j = 0; j < M; j++) used[j] = false; 

    for (int i = 0; i < N; i++) {
        bool found = false;
        for (int j = 0; j < M; j++) {
            if (!used[j] && arr1[i] == arr2[j]) { 
                found = true;
                used[j] = true; 
                break;
            }
        }
        if (!found) {
            res[res_size] = arr1[i];
            res_size++;
        }
    }
    print(res, res_size);

    // M - N
    res_size = 0;
    for (int j = 0; j < M; j++) used[j] = false;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!used[j] && arr1[i] == arr2[j]) {
                used[j] = true;
                break;
            }
        }
    }

    for (int j = 0; j < M; j++) {
        if (!used[j]) {
            res[res_size] = arr2[j];
            res_size++;
        }
    }
    print(res, res_size);

    // перетин
    res_size = 0;
    for (int j = 0; j < M; j++) used[j] = false;

    for (int i = 0; i < N; i++) {
        bool found = false;
        for (int j = 0; j < M; j++) {
            if (!used[j] && arr1[i] == arr2[j]) {
                found = true;
                used[j] = true; 
                break;
            }
        }
        if (found) {
            res[res_size] = arr1[i];
            res_size++;
        }
    }
    print(res, res_size);

    // об'єднання 
    res_size = 0;
    for (int j = 0; j < M; j++) used[j] = false;

    for (int i = 0; i < N; i++) {
        res[res_size] = arr1[i]; // додаємо все з arr1
        res_size++;
        for (int j = 0; j < M; j++) {
            if (!used[j] && arr1[i] == arr2[j]) {
                used[j] = true; 
                break;
            }
        }
    }
    for (int j = 0; j < M; j++) {
        if (!used[j]) { 
            res[res_size] = arr2[j];
            res_size++;
        }
    }
    sort(res, res + res_size);
    print(res, res_size);

    // симетрична різниця
    res_size = 0;
    for (int j = 0; j < M; j++) used[j] = false;

    for (int i = 0; i < N; i++) {
        bool found = false;
        for (int j = 0; j < M; j++) {
            if (!used[j] && arr1[i] == arr2[j]) {
                found = true;
                used[j] = true;
                break;
            }
        }
        if (!found) {
            res[res_size] = arr1[i]; // залишки з arr1
            res_size++;
        }
    }
    for (int j = 0; j < M; j++) {
        if (!used[j]) {
            res[res_size] = arr2[j]; // залишки з arr2
            res_size++;
        }
    }
    sort(res, res + res_size);
    print(res, res_size);

    delete[] used;
    delete[] arr1;
    delete[] arr2;
    delete[] res;
    return 0;
}