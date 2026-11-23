/*
Задача: Алготестер. Лабораторна робота №4. Рішення без STL
Варіант: 1
Автор: Ольга Дрогомирецька
Група: Ші-13
*/
#include <iostream>
using namespace std;

void quickSort(int numbers[], int left, int right);
void show(int result[], int size);

int main() {
    int first[100];
    int second[100];

    int n, m;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> first[i];
    }
    cin >> m;

    for (int i = 0; i < m; i++) {
        cin >> second[i];
    }
    // Сортуємо масиви.
    if (n > 1) {
        quickSort(first, 0, n - 1);
    }

    if (m > 1) {
        quickSort(second, 0, m - 1);
    }

    // Масиви для результатів.
    int differenceFirst[100];
    int differenceSecond[100];
    int intersection[100];
    int unionResult[200];
    int symmetricDifference[200];

    // Кількість елементів у результатах.
    int countFirst = 0;
    int countSecond = 0;
    int countIntersection = 0;
    int countUnion = 0;
    int countSymmetric = 0;

    int i = 0;
    int j = 0;

    // Переглядаємо обидва відсортовані масиви.
    while (i < n && j < m) {
        if (first[i] < second[j]) {
            // Число є тільки в першому масиві.
            differenceFirst[countFirst++] = first[i];
            unionResult[countUnion++] = first[i];
            symmetricDifference[countSymmetric++] = first[i];

            i++;
        } else if (first[i] > second[j]) {
            // Число є тільки в другому масиві.
            differenceSecond[countSecond++] = second[j];
            unionResult[countUnion++] = second[j];
            symmetricDifference[countSymmetric++] = second[j];

            j++;
        } else {
            // Однакові числа додаємо в перетин та об'єднання.
            intersection[countIntersection++] = first[i];
            unionResult[countUnion++] = first[i];

            i++;
            j++;
        }
    }
    // Додаємо залишок першого масиву.
    while (i < n) {
        differenceFirst[countFirst++] = first[i];
        unionResult[countUnion++] = first[i];
        symmetricDifference[countSymmetric++] = first[i];

        i++;
    }
    // Додаємо залишок другого масиву.
    while (j < m) {
        differenceSecond[countSecond++] = second[j];
        unionResult[countUnion++] = second[j];
        symmetricDifference[countSymmetric++] = second[j];
        j++;
    }
    // Виводимо результати.
    show(differenceFirst, countFirst);
    show(differenceSecond, countSecond);
    show(intersection, countIntersection);
    show(unionResult, countUnion);
    show(symmetricDifference, countSymmetric);

    return 0;
}
// Швидке сортування.
void quickSort(int numbers[], int left, int right) {
    int i = left;
    int j = right;
    int pivot = numbers[(left + right) / 2];

    while (i <= j) {
        while (numbers[i] < pivot) {
            i++;
        }

        while (numbers[j] > pivot) {
            j--;
        }

        if (i <= j) {
            int temp = numbers[i];
            numbers[i] = numbers[j];
            numbers[j] = temp;

            i++;
            j--;
        }
    }
    if (left < j) {
        quickSort(numbers, left, j);
    }
    if (i < right) {
        quickSort(numbers, i, right);
    }
}
// Виводимо кількість елементів та самі елементи.
void show(int result[], int size) {
    cout << size << "\n";

    for (int i = 0; i < size; i++) {
        if (i > 0) {
            cout << " ";
        }

        cout << result[i];
    }
    cout << "\n\n";
}