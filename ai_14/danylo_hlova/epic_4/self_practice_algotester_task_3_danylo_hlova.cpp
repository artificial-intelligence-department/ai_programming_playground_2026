#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    // Динамічне виділення пам'яті
    long long* arr = new long long[n];

    // Введення елементів
    for (int i = 0; i < n; i++) {
        cin >> *(arr + i);
    }

    long long sum = 0;

    // Обчислення суми
    for (int i = 0; i < n; i++) {
        if (*(arr + i) > 0) {
            sum += *(arr + i) - 1;
        }
    }

    cout << sum;

    //звільнення пам'яті
    delete[] arr;

    return 0;
}