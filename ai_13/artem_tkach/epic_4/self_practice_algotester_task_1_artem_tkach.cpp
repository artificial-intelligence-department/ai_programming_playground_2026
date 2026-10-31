/*
 * Self practice (Algotester-стиль) - "Рядок з максимальною сумою"
 * Ткач Артем
 * ШІ-13
 *
 * Умова: задано матрицю з N рядків та M стовпців цілих чисел. Знайти рядок,
 * у якому сума елементів максимальна. Якщо таких рядків кілька, вивести
 * перший із них.
 *
 * Input: у першому рядку N і M (1 <= N, M <= 1000), далі N рядків по M цілих чисел.
 * Output: номер рядка (з 1) і сума його елементів через пробіл.
 *
 * Приклад:  3 3        ->  3 24
 *           1 2 3
 *           4 5 6
 *           7 8 9
 *
 * Тема епіку: двовимірні динамічні масиви (int **), вказівники, new / delete[].
 */

#include <iostream>

// Зчитує матрицю n x m у динамічний двовимірний масив
int **readMatrix(int n, int m) {
    int **a = new int *[n];
    for (int i = 0; i < n; i++) {
        a[i] = new int[m];
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    return a;
}

// Сума елементів одного рядка (рядок передається вказівником)
int rowSum(const int *row, int m) {
    int sum = 0;
    for (int j = 0; j < m; j++) {
        sum += row[j];
    }
    return sum;
}

// Звільняє кожен рядок, потім масив вказівників
void freeMatrix(int **a, int n) {
    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    int **a = readMatrix(n, m);

    int bestRow = 0;
    int bestSum = rowSum(a[0], m);
    for (int i = 1; i < n; i++) {
        int sum = rowSum(a[i], m);
        if (sum > bestSum) {
            bestSum = sum;
            bestRow = i;
        }
    }

    std::cout << bestRow + 1 << " " << bestSum << "\n";

    freeMatrix(a, n);
    return 0;
}
