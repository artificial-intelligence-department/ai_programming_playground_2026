//Проскурня Дмитро ШІ-13

#include <iostream>
#include <iomanip>

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            std::cout << std::setw(3) << matrix[i][j] << " ";

        std::cout << std::endl;
    }
}

int main() {
    std::cout << "Введіть ваше n: ";
    int n{};
    std::cin >> n;

    std::cout << "Введіть елементи вашого масиву: ";
    int* array = new int[n];
    for (int i = 0; i < n; i++)
        std::cin >> array[i];

    int** matrix = new int* [n];
    for (int i = 0; i < n; i++)
        matrix[i] = new int[n];


    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n - 1; i++)
            matrix[i][j] = 67 * (i % 2 == 0 ? 1 : -1);

        if (n % 2 == 1)
            matrix[n - 1][j] = array[j];
        else
            matrix[n - 1][j] = -(67 - array[j]);
    }

    printMatrix(matrix, n);

    delete[] array;
    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}
