/*
Назва задачі: Lab 4 Task 1
Варіант: 13
Автор: Діхтяр Юлія
Група: ai-13
*/

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cmath>

using namespace std;

const int nMax = 100;

int findMin (int a[], int n) {
    int min = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
        }
    }
    return min;
}

int findAverage (int a[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
       sum = sum + a[i];
    }

    return round((double)sum / n);
}

int main () {

    srand(time(nullptr));

    // Створюємо масив та заповнюємо випадковими числами
    int n = rand() % 98 + 1;
    int a[nMax];

    for (int i = 0; i < n; i++) {
        int j = rand() % 100 + 1;
        a[i] = j;
        cout << a[i] << " ";
    }
    cout << endl;

    int min = findMin(a, n);

    // Видаляємо всі мінімальні елементи
    int newSize = 0;
    for (int i = 0; i < n; i++) {
        if(a[i] != min) {
            a[newSize] = a[i];
            newSize++;
        }
    }

    n = newSize;

    if (n == 0) {
        cout << "Масив порожній, середнє обчислити неможливо.";
        return 0;
    }

    int average = findAverage(a, n);

    // Зсуваємо елементи та додаємо три нові на початок
    for (int i = n - 1; i >= 0; i--) {
        a[i + 3] = a[i];
    }

    a[0] = a[1] = a[2] = average;
    n = n + 3;

    for (int i = 0; i < n; i++) {
       cout << a[i] << " ";
    }

    cout << endl;

    return 0;
}