#include <iostream>

using namespace std;

// Швидке сортування за зростанням
void quickSort(int a[], int left, int right){
    int i = left;
    int j = right;
    int pivot = a[(left + right) / 2];

    while (i <= j){
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;

        if (i <= j){
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;

            i++; j--;
        }
    }

    if (left < j) quickSort(a, left, j);
    if (i < right) quickSort(a, i, right);
}

// Розворот частини масиву
void reverse(int a[], int left, int right){
    while (left < right){
        int temp = a[left];
        a[left] = a[right];
        a[right] = temp;

        left++; right--;
    }
}

int main(){
    int N, K; cin >> N >> K;
    int* a = new int[N];

    for (int i = 0; i < N; i++) cin >> a[i];

    // Сортуємо масив
    quickSort(a, 0, N - 1);

    // Видаляємо повторювані елементи
    int M = 0;
    for (int i = 0; i < N; i++){
        if (M == 0 || a[i] != a[M - 1]){
            a[M] = a[i];
            M++;
        }
    }

    // Обертаємо вліво на k позицій (три розвороти)
    int k = K % M;
    if (k > 0){
        reverse(a, 0, k - 1);
        reverse(a, k, M - 1);
        reverse(a, 0, M - 1);
    }

    // Виводимо результат
    cout << M << "\n";
    for (int i = 0; i < M; i++) cout << a[i] << " ";
    
    delete[] a;

    return 0;
}