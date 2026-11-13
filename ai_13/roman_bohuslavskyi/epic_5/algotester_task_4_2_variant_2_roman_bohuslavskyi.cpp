/*
Задача:  Алготестер Lab4v2
Автор:   Roman Bohuslavskyi
Група:   ШІ-13
*/

#include <iostream>

using namespace std;

void sortNumbers(int numbers[], int buffer[], int left, int right);
int removeDuplicates(int numbers[], int n);

int main() {
    int n, k;
    int numbers[1000];
    int buffer[1000];
    cin >> n >> k;

    for (int i = 0; i < n; i++) cin >> numbers[i];

    sortNumbers(numbers, buffer, 0, n - 1);
    n = removeDuplicates(numbers, n);

    cout << n << endl;
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ' ';
        cout << numbers[(i + k) % n];
    }
    cout << endl;
    return 0;
}

void sortNumbers(int numbers[], int buffer[], int left, int right) {
    if (left >= right) {
        return;
    }

    int middle = (left + right) / 2;
    sortNumbers(numbers, buffer, left, middle);
    sortNumbers(numbers, buffer, middle + 1, right);

    int i = left;
    int j = middle + 1;
    int position = left;

    while (i <= middle && j <= right) {
        if (numbers[i] <= numbers[j]) {
            buffer[position] = numbers[i];
            i++;
        }
        else {
            buffer[position] = numbers[j];
            j++;
        }
        position++;
    }
    while (i <= middle) {
        buffer[position] = numbers[i];
        i++;
        position++;
    }
    while (j <= right) {
        buffer[position] = numbers[j];
        j++;
        position++;
    }
    for (int index = left; index <= right; index++) {
        numbers[index] = buffer[index];
    }
}

int removeDuplicates(int numbers[], int n) {
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (numbers[i] != numbers[count - 1]) {
            numbers[count] = numbers[i];
            count++;
        }
    }
    return count;
}
