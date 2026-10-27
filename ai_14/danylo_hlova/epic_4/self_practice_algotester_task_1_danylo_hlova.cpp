#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    // Створення динамічного масиву
    int* a = new int[n];

    // 2. Введення даних
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int max_len = 1;
    int current_len = 1;

 
    for (int i = 1; i < n; i++) {
        if (a[i] > a[i - 1]) {
            current_len++;
        } else {
            current_len = 1;
        }

        if (current_len > max_len) {
            max_len = current_len;
        }
    }

    cout << max_len << endl;

    //Очищення пам'яті
    delete[] a;

    return 0;
}
