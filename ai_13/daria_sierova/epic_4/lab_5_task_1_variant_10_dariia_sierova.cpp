#include <iostream>
#include <cstdlib>
#include <ctime> 
using namespace std;

bool hasNegative(const int* row, int cols){
    for (int j = 0; j < cols; j++){
        if (row[j] < 0){
            return true; // відємні числа є
        }
    }
    return false; // відємних чисел нема
}

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    srand(time(0));

    int rows; //рядки 
    cout << "Введіть кількість рядків: ";
    cin >> rows;

    int cols; //стовпці
    cout << "Введіть кількість стовпців: ";
    cin >> cols;

    //двовимірний динамічний масив
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++){
        matrix[i] = new int[cols]; // адреса масиву(рядок)
        for(int j = 0; j < cols; j++){
            matrix[i][j] = rand()%201 - 100; // -100; 100
        }
    }
    //початкова матриця
    cout << "Початкова матриця: " << endl;
    printMatrix(matrix, rows, cols);

    int lastRow  = rows - 1; // межа перевірки рядків

    for ( int i = 0; i <= lastRow;){
        if (hasNegative(matrix[i], cols)){ // пошук відємних в і рядку
            // 1. знищуємо рядок
            for(int j = 0; j < cols; j++){
                matrix[i][j] = 0;
            }
            // 2. зберігаємо адресу
            int* temp = matrix[i];
            
            // 3. зсуваємо вказівники
            for(int k = i; k < lastRow; k++){
                matrix[k] = matrix[k + 1];
            }

            // 4. записуєм збережену адресу в кінець
            matrix[lastRow] = temp;

            // 5.  зменшуєм останню межу перевірки (останній рядок вже оброблений)
            lastRow--;
        } else {
            // якщо відʼємних ел немає переходим на наступний рядок
            i++;
        }
    }
    cout << "Матриця після обробки:" << endl;
    printMatrix(matrix, rows, cols);

    for (int i = 0; i < rows; i++) {
        delete[] matrix[i]; // cпочатку видаляємо кожен рядок
    }
    delete[] matrix; // потім видаляємо масив вказівників

    return 0;
}