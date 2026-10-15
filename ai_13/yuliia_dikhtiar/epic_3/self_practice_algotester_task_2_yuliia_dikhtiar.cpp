/*
Назва задачі: Найбільша пара
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    int numbers[200000];

    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (numbers[j] > numbers[j + 1]) {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }

    int maxSum = numbers[0] + numbers[n - 1];

    for (int i = 1; i < n / 2; i++) {
        int currentSum = numbers[i] + numbers[n - 1 - i];

        if (currentSum > maxSum) {
            maxSum = currentSum;
        }
    }

    cout << maxSum << endl;

    return 0;
}