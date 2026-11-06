/*
Епік 5. Завдання з Алготестера. Лабораторна робота №4. Завдання №2. Варіант №3
Автор: Кучер Дмитро
Група: ШІ-11
*/

#include<iostream>
using namespace std;

void quicksort(int* r1, int length, bool ascending);
void quicksort_recursion(int* r1, int low, int high, bool ascending);
int partition(int* r1, int low, int high, bool ascending);

int main () {

    int N;
    cin >> N;
    if (N<1 || N>1000) return 0;

    int arr[1000];
    for (int i = 0; i<N; i++) {
        cin >> arr[i];
        if (arr[i]<0 || arr[i]>1000) return 0;
    }

    int r[1000];
    int r1[1000];
    int r2[1000];
    int r3[1000];
    int k1 = 0;
    int k2 = 0;
    int k3 = 0;
    
    for (int i = 0; i<N; i++) {
        if (arr[i] %3 == 0) r1[k1++] = arr[i];
    }
    for (int i = 0; i<N; i++) {
        if (arr[i] %3 == 1) r2[k2++] = arr[i];
    }
    for (int i = 0; i<N; i++) {
        if (arr[i] %3 == 2) r3[k3++] = arr[i];
    }

    quicksort(r1, k1, true);
    quicksort(r2, k2, false);
    quicksort(r3, k3, true);

    int k = 0;

    for (int i = 0; i<k1; i++) {
        r[k++] = r1[i];
    }

    for (int i = 0; i<k2; i++) {
        r[k++] = r2[i];
    }

    for (int i = 0; i<k3; i++) {
        r[k++] = r3[i];
    }

    int M = 0;

    for (int i = 0; i<k; i++) {
        if (M == 0 || r[i] != r[M - 1]) r[M++] = r[i];
    }

    cout << M << "\n";
    for (int i = 0; i<M; i++) {
        cout << r[i] << " ";
    }

    return 0;
}

void quicksort(int* r1, int length, bool ascending) {
    quicksort_recursion(r1, 0, length - 1, ascending);
}

void quicksort_recursion(int* r1, int low, int high, bool ascending) {
    if (low < high) {
        int pivot_index = partition(r1, low, high, ascending);

        quicksort_recursion(r1, low, pivot_index - 1, ascending);
        quicksort_recursion(r1, pivot_index + 1, high, ascending);
    }
}

int partition(int* r1, int low, int high, bool ascending) {
    int pivot_value = r1[high];
    int i = low;

    for (int j = low; j<high; j++) {
        if ((ascending && r1[j] <= pivot_value) || (!ascending && r1[j] >= pivot_value)) {

            int t = r1[i];
            r1[i] = r1[j];
            r1[j] = t;
            i++;
        }
    }

    int t = r1[i];
    r1[i] = r1[high];
    r1[high] = t;

    return i;
}
