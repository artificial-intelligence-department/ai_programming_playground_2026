#include <iostream>
#include <algorithm>

using namespace std;

void printSet(int* arr, int size) {
    cout << size << "\n";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << (i + 1 < size ? " " : "");
    }
    cout << "\n";
}

int main() {
    int N;
    cin >> N;
    int* arr1 = new int[N];
    for (int i = 0; i < N; ++i) cin >> arr1[i];

    int M;
    cin >> M;
    int* arr2 = new int[M];
    for (int i = 0; i < M; ++i) cin >> arr2[i];

    // сортування
    sort(arr1, arr1 + N);
    sort(arr2, arr2 + M);

    int* res = new int[N + M];
    int res_size = 0;

    // 1 різниця N - M 
    res_size = set_difference(arr1, arr1 + N, arr2, arr2 + M, res) - res; //елементи arr1, arr1 + N яких немає в arr2, arr2 + M
    printSet(res, res_size);

    // 2 різниця M - N
    res_size = set_difference(arr2, arr2 + M, arr1, arr1 + N, res) - res;// кінцевий вказівник - початковий вказівник
    printSet(res, res_size);

    // 3 перетин
    res_size = set_intersection(arr1, arr1 + N, arr2, arr2 + M, res) - res;
    printSet(res, res_size);

    // 4 об'єднання
    res_size = set_union(arr1, arr1 + N, arr2, arr2 + M, res) - res;
    printSet(res, res_size);

    // 5 симетрична різниця
    res_size = set_symmetric_difference(arr1, arr1 + N, arr2, arr2 + M, res) - res;
    printSet(res, res_size);

    delete[] res;
    delete[] arr2;
    delete[] arr1;

    return 0;
} 