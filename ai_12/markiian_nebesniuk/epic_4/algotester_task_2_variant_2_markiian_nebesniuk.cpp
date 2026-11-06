#include <iostream>
using namespace std;

int main() {
    int r[100000];
    int N;
    
    // Зчитуємо розмір та сам масив
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> r[i];
    }

    // Зчитуємо 3 числа для видалення
    int a, b, c;
    cin >> a >> b >> c;

    int rNew[100000];
    int rNew_count = 0; // Це наш N_new з умови

    // Фільтрація масиву
    for (int i = 0; i < N; i++) {
        if (r[i] != a && r[i] != b && r[i] != c) {
            rNew[rNew_count] = r[i];
            rNew_count++;
        }
    }

    int Sum[100000];
    int k = 0;

    // Формуємо масив сум сусідніх елементів
    for (int i = 0; i < rNew_count - 1; i++) {
        Sum[i] = rNew[i] + rNew[i + 1];
        k++;
    }

    // Виводимо кількість чисел у новому масиві
    cout << k << endl;

    // Виводимо масив сум
    for (int i = 0; i < k; i++) {
        cout << Sum[i] << " ";
    }
    return 0;
}