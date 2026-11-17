#include <iostream>

using namespace std;

int main() {
    // Ініціалізація та ввід даних
    int N, K;
    cin >> N >> K;
    int *a = new int[N];
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    } 
    // Сортування бульбашкою
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    // Переносимо унікальні елементи в новий масив
    int *b = new int[N];
    int count = 0;
    b[count] = a[0];

    for (int i = 1; i < N; i++) {
        if (a[i] != a[i - 1]) {
            count++;
            b[count] = a[i];
        }
    }
    count++;
    delete[] a;
    a = nullptr;

    // Виконуємо циклічний зсув елементів вліво на K
    K = K % count;
    for (int i = 0; i < K; i++) {
        int begin = b[0];
        for (int j = 0; j < count - 1; j++) {
            b[j] = b[j + 1];   
        }
        b[count - 1] = begin;
    }
    // Виведення результату
    cout << count << endl;
    for (int i = 0; i < count; i++) {
        cout << b[i] << " ";
    }
    delete[] b;
    b = nullptr;

    return 0;
}