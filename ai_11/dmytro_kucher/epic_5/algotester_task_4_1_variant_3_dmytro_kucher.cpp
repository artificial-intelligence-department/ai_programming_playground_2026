/*
Епік 5. Завдання з Алготестера. Лабораторна робота №4. Завдання №1. Варіант №3
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include <iostream>
#include <algorithm>
using namespace std;

bool compare (int a, int b) {
    return a > b;
}

bool condition1 (int a) {
    return a % 3 == 0;
}

bool condition2 (int a) {
    return a % 3 == 1;
}

int main () {

    int N;
    cin >> N;
    if (N<1 || N>1000) return 0;

    int arr[1000];
    for (int i = 0; i<N; i++) {
        cin >> arr[i];
        if (arr[i]<0 || arr[i]>1000) return 0;
    }
    
    int* p1 = partition(arr, arr + N, condition1);

    int* p2 = partition(p1, arr + N, condition2);

    sort(arr, p1);
    sort(p1, p2, compare);
    sort(p2, arr + N);
    
    int* r1 = unique(arr, p1);
    int* r2 = unique(p1, p2);
    int* r3 = unique(p2, arr + N);

    int k1 = r1 - arr;
    int k2 = r2 - p1;
    int k3 = r3 - p2;

    int K = k1 + k2 + k3;

    cout << K << "\n";

    for (int* p = arr; p<r1; p++) {
        cout << *p << " ";
    }

    for (int* p = p1; p<r2; p++) {
        cout << *p << " ";
    }

    for (int* p = p2; p<r3; p++) {
        cout << *p << " ";
    }

    cout << "\n";

    return 0;
}