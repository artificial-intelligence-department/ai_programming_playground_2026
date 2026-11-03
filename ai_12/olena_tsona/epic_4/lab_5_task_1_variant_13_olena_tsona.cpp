#include <iostream>
#include <iomanip>
#include <cstdlib>   // rand, srand
#include <ctime>     // time

using namespace std;

const int N = 20;            // максимальна кількість рядків
const int M = 20;            // максимальна кількість стовпців
const int MIN_VALUE = -10;   // межі випадкових чисел
const int MAX_VALUE = 10;

bool inputArray(int a[][M], int rows, int cols);
void fillRandom(int a[][M], int rows, int cols);
void printArray(const int a[][M], int rows, int cols);
int sumColumns(const int a[][M], int rows, int from, int to);
int findSplitColumn(const int a[][M], int rows, int cols);

int main() {
    int a[N][M];          // статичний масив із запасом
    int rows, cols;       // реальні розміри: працюємо з a[0..rows-1][0..cols-1]

    cout << "Кількість рядків (від 1 до " << N << "): ";
    if (!(cin >> rows) || rows < 1 || rows > N) {
        cout << "Помилка! Потрібно ввести ціле число від 1 до " << N << "." << endl;
        return 1;
    }
    cout << "Кількість стовпців (від 1 до " << M << "): ";
    if (!(cin >> cols) || cols < 1 || cols > M) {
        cout << "Помилка! Потрібно ввести ціле число від 1 до " << M << "." << endl;
        return 1;
    }

    int mode;
    cout << "Заповнення масиву: 1 - вручну, 2 - випадково: ";
    if (!(cin >> mode) || (mode != 1 && mode != 2)) {
        cout << "Помилка! Потрібно ввести 1 або 2." << endl;
        return 1;
    }

    if (mode == 1) {
        cout << "Введіть елементи по рядках (рядків: " << rows
             << ", чисел у рядку: " << cols << "):" << endl;
        if (!inputArray(a, rows, cols)) {
            cout << "Помилка! Потрібно вводити цілі числа." << endl;
            return 1;
        }
    } else {
        srand((unsigned)time(nullptr));
        fillRandom(a, rows, cols);
    }

    cout << endl << "Масив " << rows << " x " << cols << ":" << endl;
    printArray(a, rows, cols);

    int k = findSplitColumn(a, rows, cols);
    cout << endl;
    if (k == -1) {
        cout << "Ні, такого стовпця немає." << endl;
    } else {
        cout << "Так, можна. Стовпець номер " << k + 1 << endl;
        cout << "Сума ліворуч: " << sumColumns(a, rows, 0, k - 1) << endl;
        cout << "Сума праворуч: " << sumColumns(a, rows, k + 1, cols - 1) << endl;
    }

    return 0;
}

// Вводить елементи з клавіатури. false, якщо введено не число
bool inputArray(int a[][M], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (!(cin >> a[i][j])) {
                return false;
            }
        }
    }
    return true;
}

// Заповнює масив випадковими числами з [MIN_VALUE, MAX_VALUE]
void fillRandom(int a[][M], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            a[i][j] = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
        }
    }
}

void printArray(const int a[][M], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(4) << a[i][j];
        }
        cout << endl;
    }
}

// Сума елементів у стовпцях від from до to включно (у всіх рядках).
// Якщо from > to, стовпців немає і сума дорівнює 0
int sumColumns(const int a[][M], int rows, int from, int to) {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = from; j <= to; j++) {
            sum += a[i][j];
        }
    }
    return sum;
}

// Шукає стовпець, у якого сума ліворуч більша за суму праворуч, повертає його індекс (з нуля) 
int findSplitColumn(const int a[][M], int rows, int cols) {
    for (int k = 1; k < cols - 1; k++) {
        int left = sumColumns(a, rows, 0, k - 1);
        int right = sumColumns(a, rows, k + 1, cols - 1);
        if (left > right) {
            return k;
        }
    }
    return -1;
}