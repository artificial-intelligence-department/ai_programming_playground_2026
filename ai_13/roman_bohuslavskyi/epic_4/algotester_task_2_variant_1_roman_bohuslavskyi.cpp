/*
Задача:  Алготестер Lab2v1
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>

using namespace std;

int findDifference(int numbers[], int n, int skipIndex);

int main() {
    const int MAX = 100000;
    int numbers[MAX];
    int n;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    if (n <= 2) {
        cout << 0 << endl;
        return 0;
    }

    int minIndex = 0;
    int maxIndex = 0;

    // Знаходимо позиції найменшого та найбільшого числа
    for (int i = 1; i < n; i++) {
        if (numbers[i] < numbers[minIndex])
            minIndex = i;
        if (numbers[i] > numbers[maxIndex])
            maxIndex = i;
    }

    int removeMin = findDifference(numbers, n, minIndex);
    int removeMax = findDifference(numbers, n, maxIndex);

    if (removeMin < removeMax) {
        cout << removeMin << endl;
    }
    else {
        cout << removeMax << endl;
    }

    return 0;
}

int findDifference(int numbers[], int n, int skipIndex) {
    // Беремо перший елемент, який не пропускаємо
    int start = 0;
    if (skipIndex == 0)
        start = 1;

    int minValue = numbers[start];
    int maxValue = numbers[start];

    for (int i = 0; i < n; i++) {
        if (i == skipIndex) {
            continue;
        }

        if (numbers[i] < minValue) {
            minValue = numbers[i];
        }
        if (numbers[i] > maxValue) {
            maxValue = numbers[i];
        }
    }

    return maxValue - minValue;
}