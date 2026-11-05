/*
Назва: Лабораторна робота 4 Варіант 19
Автор: Бичковський Володимир
Група: ШІ-11
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));

    int n;
    int K;

    cout << "Введіть розмір масиву: ";
    cin >> n;
    cout << "Введіть K: ";
    cin >> K;
    int arr[n];

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 50;
    }

    cout << "Початкове кільце: ";
    int idx = K % n;
    for (int i = 0; i < n; i++) {
        cout << arr[idx] << " ";
        idx = (idx - 1 + n) % n;
    }
    cout << endl;

    int first = arr[0];
    int last = arr[n - 1];

    for (int i = n; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = first;
    n++;

    arr[n] = last;
    n++;

    int a = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            arr[a] = arr[i];
            a++;
        }
    }
    n = a;

    cout << "Підсумкове кільце: ";
    idx = K % n;
    for (int i = 0; i < n; i++) {
        cout << arr[idx] << " ";
        idx = (idx - 1 + n) % n;
    }
    cout << endl;

    return 0;
}