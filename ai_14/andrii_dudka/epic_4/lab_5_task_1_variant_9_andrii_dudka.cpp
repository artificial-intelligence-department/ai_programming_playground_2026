// variant 9

#include <iostream>

using namespace std;

const int MAX_SIZE = 100;

long long findSum(const int arr[][MAX_SIZE], int size) {
    long long sum = 0;

    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < i; ++k) {
            sum += arr[i][k];
        }
    }

    return sum;
}

int main() {
    int n;

    cout << "Введіть кількість матриць: ";
    if (!(cin >> n) || n < 1) {
        cout << "Некоректна кількість матриць!" << endl;
        return 1;
    }

    int arr[MAX_SIZE][MAX_SIZE];
    long long maxSum = 0;

    for (int matrix = 0; matrix < n; ++matrix) {
        int size;

        cout << "Введіть розмір матриці №"
             << matrix + 1 << " (1–100): ";

        if (!(cin >> size) || size < 1 || size > MAX_SIZE) {
            cout << "Некоректний розмір!" << endl;
            return 1;
        }

        cout << "Введіть елементи матриці по рядках:" << endl;

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (!(cin >> arr[i][j])) {
                    cout << "Некоректний елемент!" << endl;
                    return 1;
                }
            }
        }

        long long sum = findSum(arr, size);

        cout << "Сума нижче головної діагоналі: "
             << sum << endl;

        if (matrix == 0 || sum > maxSum) {
            maxSum = sum;
        }
    }

    cout << "Максимальна сума: " << maxSum << endl;

    return 0;
}