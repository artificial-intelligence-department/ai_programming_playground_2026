/*
* Задача: Лабораторна робота 5, варіант 6
* Поліщук Вероніка
* Група 14
*/

#include <iostream>

using namespace std;

// Функція для пошуку та виведення сідлових точок матриці
void findSaddlePoints(int matrix[100][100], int rows, int cols){
    // Прапорець для відстеження того, чи була знайдена хоча б одна сідлова точка
    bool found = false;
    
    // Зовнішні цикли для послідовного перебору кожного елемента матриці
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int current = matrix[i][j]; // Збереження поточного елемента для порівняння

            // Перевірка, чи є поточний елемент мінімальним у своєму рядку
            bool MinInRow = true;
            for (int k = 0; k < cols; k++) {
                if (matrix[i][k] < current) {
                    MinInRow = false;
                    break;
                }
            }

            // Перевірка, чи є поточний елемент максимальним у своєму стовпці
            bool MaxInCol = true;
            for (int k = 0; k < rows; k++){
                if (matrix[k][j] > current) {
                    MaxInCol = false;
                    break;
                }
            }

            // Перевірка додаткової умови для альтернативної комбінації сідлової точки
            bool MinInCol = true;
            for (int k = 0; k < rows; k++){
                if (matrix[i][k] < current){
                    MinInCol = false;
                    break;
                }
            }

            // Перевірка ще однієї комбінації для пошуку екстремумів
            bool MaxInRow = true;
            for (int k = 0; k < cols; k++){
                if (matrix[k][j] > current) {
                    MaxInRow = false;
                    break;
                }
            }
            
            // Якщо виконується одна з умов сідлової точки, виводимо її координати та значення
            if ((MinInRow && MaxInCol) || (MinInCol && MaxInRow)){
                cout << "Сідлова точка: " << current << " (рядок " << i + 1 << ", стовпець " << j + 1 << ")" << endl;
                found = true;
            }
        }
    }

    // Якщо за результатами перевірки сідлових точок не виявлено, виводимо повідомлення
    if (!found) {
        cout << "У заданій матриці немає сідлових точок." << endl;
    }
}


int main(){
    const int N = 100;
    int rows, cols;
    
    cout << "Введіть кількість рядків матриці: ";
    cin >> rows;
    cout << "Введіть кількість стовпців матриці: ";
    cin >> cols;
    
    int matrix[N][N];
    
    cout << "Введіть елементи матриці:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }
    
    // Виклик функції
    findSaddlePoints(matrix, rows, cols);

    return 0;
}