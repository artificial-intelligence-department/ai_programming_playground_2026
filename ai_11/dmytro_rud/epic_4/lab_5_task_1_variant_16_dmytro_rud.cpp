#include <iostream>
#include <limits>

using namespace std;

const int MAX_SIZE = 100;

void readInt(int& x) {
    while (!(cin >> x)) {
        cout << "Помилка. Введіть ціле число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void printMatrix(const int arr[][MAX_SIZE], int n) {
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            cout << arr[a][b] << "\t";
        }

        cout << "\n";
    }
}

bool makeIncreasingSideDiagonal(int arr[][MAX_SIZE], int n) {
    int previousValue = 0;

    for (int a = 0; a < n; a++) {
        int b = n - 1 - a;
        int bestA = -1;

        // Пошук найменшого числа в поточному стовпці,
        // яке більше за попередній елемент бічної діагоналі.
        for (int currentA = 0; currentA < n; currentA++) {
            bool fitsCondition =
                (a == 0 || arr[currentA][b] > previousValue);

            if (fitsCondition) {
                if (bestA == -1 ||
                    arr[currentA][b] < arr[bestA][b]) {
                    bestA = currentA;
                }
            }
        }

        // Якщо відповідного числа в поточному стовпці немає.
        if (bestA == -1) {
            return false;
        }

        // Переставляємо знайдений елемент на бічну діагональ.
        int temp = arr[a][b];
        arr[a][b] = arr[bestA][b];
        arr[bestA][b] = temp;

        previousValue = arr[a][b];
    }

    return true;
}

int main() {
    int n;
    int array[MAX_SIZE][MAX_SIZE];

    cout << "Введіть розмір квадратної матриці N: ";
    readInt(n);

    while (n <= 0 || n > MAX_SIZE) {
        cout << "N повинно бути від 1 до " << MAX_SIZE << ".\n";
        cout << "Введіть N ще раз: ";
        readInt(n);
    }

    for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
            cout << "array[" << a << "][" << b << "] = ";
            readInt(array[a][b]);
        }
    }

    cout << "\nПочаткова матриця:\n";
    printMatrix(array, n);

    if (makeIncreasingSideDiagonal(array, n)) {
        cout << "\nРезультат: можливо.\n";
        cout << "Матриця після перестановок у стовпцях:\n";
        printMatrix(array, n);

        cout << "\nБічна діагональ: ";

        for (int a = 0; a < n; a++) {
            cout << array[a][n - 1 - a] << " ";
        }

        cout << "\n";
    }
    else {
        cout << "\nРезультат: неможливо розташувати елементи ";
        cout << "на бічній діагоналі за зростанням.\n";
    }

    return 0;
}